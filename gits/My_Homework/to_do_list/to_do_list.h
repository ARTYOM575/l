namespace Art {

    #define RED(str) "\033[31m" << str << "\033[0m"
    #define DEEP_RED(str) "\033[31;2m" << str << "\033[0m"
    #define GREEN(str) "\033[32m" << str << "\033[0m"
    #define BLUE(value) "\033[34m" << value << "\033[0m"
    #define YELLOW(str) "\033[33m" << str << "\033[0m"
    bool push_fail_back;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    int year_ = localTime->tm_year + 1900;
    int month_ = localTime->tm_mon + 1;         
    int day_ = localTime->tm_mday;          
    int hour_ = localTime->tm_hour;             
    int minute_ = localTime->tm_min;
    const char task[] = ".task.txt";
    const char done_task[] = ".done.txt";

    void Shell_constructor() {
        std::string command;
        command.clear();
        std::ifstream file_read(task);
        if (!file_read.is_open()) {
            command = "touch ";
            command += task;
            system(command.c_str());
        }
        file_read.close();
        file_read.open(done_task);
        if (!file_read.is_open()) {
            command.clear();
            command = "touch ";
            command += done_task;
            system(command.c_str());
        }
        file_read.close();
    }

    void update_time(int second = 0) {
        sleep(second);
        currentTime = std::time(nullptr);
        localTime = std::localtime(&currentTime);
        year_ = localTime->tm_year + 1900;
        month_ = localTime->tm_mon + 1;
        day_ = localTime->tm_mday;
        hour_ = localTime->tm_hour;
        minute_ = localTime->tm_min;
    }   

    void is_number(std::string& num) {
        int i = 0;
        if (num == "") {
            num = "f";
            return;
        }
            
        if (num[0] == 48) {
            num += 'f';
            return;
        }
        while (num[i] != '\0') {
            if (num[i] < 48 && num[i] > 57) {
                num += 'f';
                return ;
            }
            ++i;
        }
        num += 't';
    }

    bool for_day(int temp_i) {
        if (temp_i > 31) 
            return false;
        switch (month) {
            case 2:
                if (!(year % 4)) {
                    if (temp_i > 29) {
                        return false;
                    }
                } else if (temp_i > 28) {
                    return false;
                }
            case 4:
                if (temp_i > 30)
                    return false;
            case 6:
                if (temp_i > 30)
                    return false;
            case 9:
                if (temp_i > 30)
                    return false;
            case 11:
                if (temp_i > 30)
                    return false;
            case 12:
            default:
                break;
        }
        return true;
    }

    bool correct_y (std::string num) {
        is_number (num); 
        if (num[num.length() - 2] == 'f') {
        return false; 
        }
        if (std::stoi(num) >= year_) {
            return true;
        } else {
            return false;
        }
    }

    bool correct_m (std::string num) {
        int temp_m;
        is_number(num);
        if (num[num.length() - 2] == 'f') {
            return false; 
        }
        temp_m = std::stoi(num);
        if (year == year_) {
            if (temp_m >= month_ && temp_m <= 12) {
                return true;
            }
            return false;
        }
        if (temp_m >= 1 && temp_m <= 12) {
            return true;
        } else {
            return false;
        } 
    }

    bool correct_d (std::string num) {
        int temp_d;
        is_number(num);
        if (num[num.length() - 2] == 'f') {
            return false; 
        }
        temp_d = std::stoi(num);
        if (year == year_) {
            if (month == month_) {
                if (temp_d >= day_) {
                    return for_day(temp_d);
                }
                else {
                    return false;
                }
            }
        } 
        return for_day(temp_d);
    }

    bool correct_h (std::string num) {
        int temp_h;
        is_number(num);
        if (num[num.length() - 2] == 'f') {
            return false; 
        }
        temp_h = std::stoi(num);
        if (year == year_) {
            if (month == month) {
                if(day == day_) {
                    if (temp_h >= hour_ && temp_h <= 24) {
                        return true;
                    }
                    return false;
                }
            }
        }
        if (temp_h >= 0 && temp_h <= 24) 
            return true;
        return false;
    }

    bool correct_h_m (std::string num) {
        int temp_m;
        is_number(num);
        if (num[num.length() - 2] == 'f') {
            return false; 
        }
        temp_m = std::stoi(num);
        if (year == year_) {
            if (month == month) {
                if(day == day_) {
                    if (hour == hour_) {
                        if (temp_m >= minute_ + 2 && temp_m <= 59) 
                            return true;
                        return false;
                    } 
                }
            }
        }
        if (temp_m >= 0 && temp_m <= 59) 
            return true;
        return false;
    }
    
    int find_position(const std::string& name) {
        push_fail_back = false;
        int temp_num;
        char* num;
        std::string line;
        std::ifstream file_read (name.c_str());
        if (!file_read) {
            std::cout << "System error\n";
            exit(1);
        }
        int i = 1;
        while (getline(file_read,line)) {
            if (line.empty()) {
                std::cout << DEEP_RED("Hackers hacked your file\n");
                file_read.close();
                return i;
            }
            num = &line[0];
            temp_num = std::stoi(num);
            if (year < temp_num) {
                file_read.close();
                return i;
            } else if (year == temp_num) {
                while (*num != ' ')
                    ++num;
                ++num;
                temp_num = std::stoi(num);
                if (month < temp_num) {
                    file_read.close();
                    return i;
                } else if (month == temp_num) {
                    while (*num != ' ')
                        ++num;
                    ++num;
                    temp_num = std::stoi(num);
                    if (day < temp_num) {
                        file_read.close();
                        return i;
                    }else if (day == temp_num) {
                        while (*num != ' ')
                            ++num;
                        ++num;
                        temp_num = std::stoi(num);
                        if (hour < temp_num) {
                            file_read.close();
                            return i;
                        } 
                        else if (hour == temp_num) {
                             while (*num != ' ')
                                ++num;
                            ++num;
                            temp_num = std::stoi(num);
                            if (minute <= temp_num) {
                                file_read.close();
                                return i;
                            }
                        }
                    }
                }
            }
            ++i;
        }
        push_fail_back = true;
        return i;
    }

    bool create_task() {
        std::string line;
        std::string content;
        std::string res;
        std::ofstream file_write;
        std::ifstream file_read;
        int position;
        res.clear();  
        std::cout << "input Yahr  ";
        std::cin >> content;
        if (correct_y(content)) {
            year = std::stoi(content);
            res += std::to_string(year) + " ";
        } else {
            std::cout << DEEP_RED("!!!!Invalid year!!!!\n");
            return false;
        }
        std::cout << "input month ";
        std::cin >> content;
        if (correct_m(content)) {
            month = std::stoi(content);
            res += std::to_string(month) + " ";
        } else {
            std::cout << DEEP_RED("!!!!Invalid month!!!!\n");
            return false;
        }
        std::cout << "input day ";
        std::cin >> content;
        if (correct_d(content)) {
            day = std::stoi(content);
            res += std::to_string(day) + " ";
        } else {
            std::cout << DEEP_RED("!!!!Invalid day!!!!\n");
            return false;
        }
        std::cout << "input hour ";
        std::cin >> content;
        if (correct_h(content)) {
            hour = std::stoi(content);
            res += std::to_string(hour) + " ";
        } else {
            std::cout << DEEP_RED("!!!!Invalid hour!!!!\n");
            return false;
        }
        std::cout << "input minute ";
        std::cin >> content;
        if (correct_h_m(content)) {
            minute = std::stoi(content);
            res += std::to_string(minute) + " ";
        } else {
            std::cout << DEEP_RED("!!!!Invalid minute!!!!\n");
            return false;
        }
        content.clear();
        std::cout << "input action ";
        std::cin >> std::ws;
        std::getline(std::cin, content);
        res += content;
        position = find_position(task);
        if (push_fail_back) {
            file_write.open(task,std::ios::app);
            if (!file_write) {
                std::cout << DEEP_RED("System error\n");
                exit(1);
            }
            file_write << res << '\n';
            file_write.close();
        } else {
            file_write.open(".temp.txt");
            file_read.open(task);
            if (!file_write || !file_read) {
                std::cout << DEEP_RED("System error\n");
                exit(1);
            }
            for (int i = 1;i < position; ++i) {
                getline(file_read,line);
                file_write << line << '\n';
            }
            file_write << res << '\n';
            while (getline(file_read,line)) {
                file_write << line << '\n';
            }
            file_read.close();
            file_write.close();
            std::string command;
            command.clear();
            command = "rm ";
            command += task;
            system (command.c_str());
            command.clear();
            command = "mv .temp.txt ";
            command += task;
            system (command.c_str());
        }
        return true;
    }

    void print_all_task(char ch, int& line_index) {
        std::ifstream file_read;
        std::string line;
        if (ch == 'U') {
            file_read.open(task);
        } else if (ch == 'F') {
            file_read.open(done_task);
        }
        if (!file_read) {
            std::cout << DEEP_RED("System error\n");
            exit(1);
        }
        while (getline(file_read,line)) {
            std::cout << "  " << BLUE(line_index) << '\t';
            if (ch == 'U')
                std::cout << RED(line) << '\n';
            else 
                std::cout << GREEN(line) << '\n';
            ++line_index;
        }
        file_read.close();
    }

    std::string clear(char ch, int index) {
        std::string ret;
        std::ifstream file_read;
        std::string line;
        std::ofstream file_write;
        std::string command;
        command.clear();
        if (ch == 't') {
            file_read.open(task);
        } else {
            file_read.open(done_task);
        }
        file_write.open(".tempclear.txt");
        if (!file_read || !file_write) {
            std::cout << DEEP_RED("System error\n");
            exit(1);
        }
        while (index > 1) {
            getline(file_read,line);
            file_write << line << '\n';
            --index;
        }
        getline(file_read,line);
        ret = line;
        while (getline(file_read,line))
            file_write << line << '\n';
        file_read.close();
        file_write.close();
        command = "rm ";
        if (ch == 't') 
            command += task; 
        else 
            command += done_task;
        system (command.c_str());
        command.clear();
        command = "mv .tempclear.txt ";
        if (ch == 't') 
            command += task;
        else 
            command += done_task;
        system (command.c_str());
        return ret;
    }

    bool delete_task() {
        std::cout << YELLOW("year/month/day/hour/minude/data\n");
        char ch;
        int del_ind;
        int ind_task;
        int all_ind = 1;
        std::cout << BLUE("index\n  | \n  V\n");
        std::cout << RED("\t\tUnfinished\n");
        print_all_task('U',all_ind);
        ind_task = all_ind - 1;
        if (ind_task == 0) 
            std::cout << RED("\t--------------------------\n");
        std::cout << GREEN("\t\t Finished\n");
        print_all_task('F',all_ind);
        --all_ind;
        if (all_ind - ind_task == 0) 
            std::cout << GREEN("\t--------------------------\n");
        while (true) {
            std::cout << "Are you sure you want to delete task?\n Y/yes   N/no\n";
            std::cin >> ch;
            if (ch == 'N')
                return false;
            if (ch == 'Y')
                break;
        }
        std::cout << "Inuput index which you want delete   ";
        std::cin >> del_ind;
        if (del_ind > all_ind || del_ind <= 0) {
            std::cout << DEEP_RED("Invalid index\n");
            return false;
        }
        if (del_ind <= ind_task) {
            clear ('t',del_ind);
            return true;
        }
        clear ('d',(del_ind - ind_task));
        return true;
    }

    bool done_task_f() {
        std::cout << YELLOW("year/month/day/hour/minude/data\n");
        std::string del_str;
        int position;
        int del_ind;
        int ind_task = 1;
        std::ifstream file_read;
        std::ofstream file_write;
        std::string line;
        std::cout <<BLUE("index\n  | \n  V\n") ;
        std::cout << RED("\t\tUnfinished\n");
        print_all_task('U',ind_task);
        --ind_task;
        if (ind_task == 0) {
            std::cout << RED("\t--------------------------\n");
            return false;
        }
        std::cout << "Enter the index you witch done   ";
        std::cin >> del_ind;
        if (del_ind > ind_task || del_ind <= 0) {
            std::cout<< DEEP_RED("Invalid index\n");
            return false;
        }
        del_str = clear ('t',del_ind);
        position = find_position(done_task);
        if (push_fail_back) {
            file_write.open(done_task,std::ios::app);
            if (!file_write) {
                std::cout << DEEP_RED("System error\n");
                exit(1);
            }
            file_write << del_str << '\n';
            file_write.close();
        } else {
            file_write.open(".temp_done_f.txt");
            file_read.open(done_task);
            if (!file_write || !file_read) {
                std::cout << DEEP_RED("System error\n");
                exit(1);
            }
            for (int i = 1;i < position; ++i) {
                getline(file_read,line);
                file_write << line << '\n';
            }
            file_write << del_str << '\n';
            while (getline(file_read,line)) {
                file_write << line << '\n';
            }
            file_read.close();
            file_write.close();
            std::string command;
            command.clear();
            command = "rm ";
            command += done_task;
            system (command.c_str());
            command.clear();
            command = "mv .temp_done_f.txt ";
            command += done_task;
            system (command.c_str());
        }
        return true;
    }

    std::string change_line(bool ch,int index) {
        std::cout << "\nwhat do you want change\n1 " << YELLOW("1 year\n2 month\n3 day\n4 hour\n5 minude\n6 data\n");
        int var;
        std::string new_;
        int count_space = 0;
        std::cin >> var;
        --var;
        std::cout << "Input new value  ";
        std::cin >> new_;
        std::string ret;
        std::ifstream file_read;
        std::string line;
        std::ofstream file_write;
        std::string command;
        command.clear();
        if (ch == 't') {
            file_read.open(task);
        } else {
            file_read.open(done_task);
        }
        file_write.open(".tempchange.txt");
        if (!(file_write.is_open()) || !(file_read.is_open())) {
            std::cout << DEEP_RED("System error\n");
            exit(1);
        }
        
        while (index > 1) {
            std::cout << "hello";
            getline(file_read,line);
            std::cout << "LINE  "  <<line << std::endl;
            file_write << line << '\n';
            --index;
        }
        
        getline(file_read,line);
        ret.clear();
        int i = 0;
        for (; count_space < var;++i) {
            ret[i] = line[i];
            if (line[i] == ' ') {
                ++count_space;
            }
        }
        std::cout << "AA" <<std::endl;
        char* beg;
        if (var == 5) {
            ret += new_;
        } else {
            beg = &line[i];
            while (*beg != ' ')
                ++beg;
            ++beg;
        }
        ret += beg;
        file_write << ret << '\n';
        
        while (getline(file_read,line))
            file_write << line << '\n';
        file_read.close();
        file_write.close();
        //command = "rm ";
        //if (ch == 't') 
        //    command += task; 
        //else 
        //    command += done_task;
        //system (command.c_str());
        //command.clear();
        //command = "mv .tempchange.txt ";
        //if (ch == 't') 
        //    command += task;
        //else 
        //    command += done_task;
        //system (command.c_str());
        return ret;
    }

    bool change_task() {
        char ch;
        int change_ind;
        int ind_task;
        int all_ind = 1;
        std::cout << BLUE("index\n  | \n  V\n");
        std::cout << RED("\t\tUnfinished\n");
        print_all_task('U',all_ind);
        ind_task = all_ind - 1;
        if (ind_task == 0) 
            std::cout << RED("\t--------------------------\n");
        std::cout << GREEN("\t\t Finished\n");
        print_all_task('F',all_ind);
        --all_ind;
        std::cout <<"all ind  " << all_ind <<"ind_task  "<< ind_task <<  std::endl;
        if (all_ind - ind_task == 0) 
            std::cout << GREEN("\t--------------------------\n");
        std::cout << YELLOW("Input -1 if you went return menu\n");
        std::cout << YELLOW("Input line  ");
        std::cin >> change_ind;
        if (change_ind == -1) {
            return true;
        }
        if (change_ind > all_ind || change_ind <= 0) {
            std::cout << DEEP_RED("Invalid index\n");
            return false;
        }
        if (change_ind <= ind_task) {
            std::cout << "AAAAAAA";
            change_line ('t',change_ind);
            return true;
        }
        std::cout << "DDDDDDDDD";
        change_line ('d',(change_ind - ind_task));
        return true;
    }

    void* Shell (void* arg) {
        Shell_constructor();      
        bool end = true;
        char key;
        int i;
        while (end) {
            std::cout << YELLOW("1  Create task\n2  Delete task \n3  Change task\n4  Done task\n")
            <<YELLOW("5  Print\n6  Delete all file\n7  Create default file\n8  Exit\n");
            std::cin >> key;
            switch (key) {
                case '1':
                    system("clear");
                    if (create_task()) {
                        std::cout << GREEN("You create task\n");
                    } else {
                        std::cout << RED("Sorry, you cannot create a task\n");
                    }
                    break;
                case '2':
                    system("clear");
                    if (delete_task()) {
                        std::cout << GREEN("You have successfully deleted it\n");
                    } else {
                        std::cout << RED("You have not deleted the task\n");
                    }
                    break;
                case '3':
                    system("clear");
                    if (change_task()) {
                        std::cout << GREEN("Is approved\n");
                    } else {
                        std::cout << RED("Not confirmed\n");
                    }
                    break;
                case '4':
                    system("clear");
                    if (done_task_f()) {
                        std::cout << GREEN("Is approved\n");
                    } else {
                        std::cout << RED("Not confirmed\n");
                    }
                    break;
                case '5':
                    system("clear");
                    i = 1;
                    print_all_task('U',i);
                    print_all_task('F',i);
                    break;
                case '6':
                    system("clear");
                    while (true) {
                        std::cout << YELLOW ("Are you sure you want to delete Dtata Base?\n Y/yes  N/no\n");
                        std::cin >> key;
                        if (key == 'Y') {
                            std::string command;
                            std::cout << "If you want use the program input 7\n";
                            command.clear();
                            command = "rm ";
                            command += done_task;
                            command += " ";
                            command += task;
                            system(command.c_str());
                            break;
                        } 
                        if (key == 'N') {
                            std::cout << "File don't deleted\n";
                            break;
                        }  
                    }
                    break;
                case '7':
                    system ("clear");
                    Shell_constructor();
                    break;
                default:                
                    end = false;
                    break;
            }
        }
        pthread_exit(nullptr);
    }
    
    void* Sys_(void* arg) { 
        pthread_exit(nullptr);
    }
}