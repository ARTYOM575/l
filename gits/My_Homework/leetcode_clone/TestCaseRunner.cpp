#include "cplus.h"

std::string cut(char* str) {
    int i = 0;
    std::string ret = "";
    while (str[i] != '.') {
        ret += str[i++];
    }
    return ret;
}

void print(const std::string& str) {
    std::cout << str << std::endl;
}

char* extension (std::string arg) {
    char* extension_ = new char[10];
    int index_point = 0;
    int k = 0;
    while (arg[index_point] != '\0' && arg[index_point] != '.')
        index_point++;
    if (arg[index_point] != '.')
        return &arg[0];
    index_point++;
    while (arg[index_point] != '\0') {
        extension_[k] += arg[index_point];
        ++k;
        ++index_point;
    }
    extension_[k] = '\0';
    return extension_;
}

int send_argument (const std::string &temp_command,char* charter) {
    int i = 1;
    int * num;
    std::string line1;
    std::string line2;
    std::string command;
    line1.clear();
    line2.clear();
    std::ifstream file_read1(charter);
    std::ifstream file_read2;
    if (!file_read1) {
        print("file_read1 is'nt open");
        exit(1);
    }
    while (getline(file_read1, line1)) {
        num = get_testing(line1);
        command.clear();
        command += temp_command;
        command += std::to_string(num[0]) + " ";
        command += std::to_string(num[1]); 
        system(command.c_str());
        file_read2.open("result.txt");
        getline(file_read2,line2);
        if (!file_read2) {
            print("result.txt is'nt open"); 
            exit(1);
        }
        if (std::stoi(line2) != num[2]) {
            delete [] num;
            return i;
        }
        ++i;
        line1.clear();
        line2.clear();
        file_read2.close();
    }
    delete [] num;
    return -1;
}

void all_rigth(std::string temp_command,char * ch) {
    int i = send_argument(temp_command,ch);
    if (i != -1) {
        print("example   " + std::to_string(i));
    } else 
    print("Very nice");
}

int main(int argc, char* argv[]) {
    int i;
    std::string temp_command;
    std::string str;
    str.clear();
    temp_command.clear();
    str = extension(argv[1]);
    if (str == "out") {//C++
        temp_command += "./";
        temp_command += argv[1];
        temp_command += " ";
    } else if (str == "class") {//Java
        temp_command += "java ";
        str.clear();
        temp_command += cut(argv[1]);
        temp_command += " ";
        exit(1);
    } else if (str == "py") {//Python
        temp_command += "python3 ";
        temp_command += argv[1];
        temp_command += " ";
    
    } else if (str == "js"){//JavaScript
        temp_command += "node ";
        temp_command += argv[1];
        temp_command += " ";
    } else {
        print("format error");
        exit(1);
    }
    all_rigth (temp_command, argv[2]);
}