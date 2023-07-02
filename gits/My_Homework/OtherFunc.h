#include <iostream>
#include <fstream>

bool bynarySearch (u_int32_t number, std::string name_file, u_int32_t begin = 0,u_int32_t end = 315000) {
    std::ifstream file_read(name_file);
    while (begin <= end) {
        
    }
    
}

void crete_finale_file () {
    const int count_symbhols = 6;
    //count_symbhols = symvolneri qanak
    int counter = 0;
    u_int32_t temp_;
    u_int32_t number = 0;
    u_int32_t temp;
    std::string str;
    std::ifstream file_read("BinNumbers.txt");
    std::ofstream file_write ("final.txt");
    if (!file_read) {
        std::cout << "file_read is'nt open "<<std::endl;
        exit(1);
    }
    if (!file_write) {
        std::cout << "file_write is'nt open "<<std::endl;
        exit(1);
    }
    while (getline(file_read,str)) {
        
        temp = std::stol(str);
        while(temp) {
            if (temp & 1) {
                counter = 0;
                file_write << std::to_string(number);
                temp_ = number;
                while (temp_) {
                    counter++;
                    temp_ /= 10;
                }
                while (counter < count_symbhols) {
                    file_write << " ";
                    ++counter;
                }
                file_write << "\n";
            }
            temp >>= 1;
            ++number;
        }
        //std::cout << number << "  ";
        while (number % 32 != 0) {
            ++number;
        }
        //std::cout << number;
    }
    file_read.close();
    file_write.close();
}

void print_file() {
    std::string str;
    std::ifstream file ("final.txt");
    while (getline (file,str)) {
        std::cout << str <<std::endl;
    }
    file.close();
}

void foo (std::string name) {
    std::cout << name << std::endl;
}
void count_bits_all_file () {
    u_int32_t num;
    int count = 0;
    std::string str;
    std::ifstream file("BinNumbers.txt");
    if (!file) {
        std::cout << "file is'nt open";
        exit(1);
    }
    while (getline(file,str)){
        num = std::stol(str);
        while(num) {
            if (num & 1) {
                ++count;
            }
            num >>= 1;
        }
    }
    std::cout << count << std::endl;
}

void rec(u_int32_t number) {
    if (number > 1) {
        rec(number >> 1);
    }
    std::cout << (number & 1);
}