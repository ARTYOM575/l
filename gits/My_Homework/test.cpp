#include <iostream>
#include <fstream>

void rec(u_int32_t number) {
    if (number > 1) {
        rec(number >> 1);
    }
    std::cout << (number & 1);
    //10100010100011010110110000010000
}

u_int32_t counts_bit (u_int32_t number) {
    u_int32_t count = 0;
    while (number) {
        if (number & 1)
            count++;
        number >>= 1;
    }
    return count;
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

int main() {
    count_bits_all_file();
}