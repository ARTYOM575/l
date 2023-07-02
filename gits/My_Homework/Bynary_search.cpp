//#include <iostream> 
//#include <fstream>
#include "OtherFunc.h"


u_int32_t counts_bit (u_int32_t number) {
    u_int32_t count = 0;
    while (number) {
        if (number & 1)
            count++;
        number >>= 1;
    }
    return count;
}

void generate_numbers(u_int32_t uniq_tveri_qanak, u_int32_t around) {
    int k;
    const u_int32_t uinqs = uniq_tveri_qanak;
    const u_int32_t length_32 = 4294967295l;
    u_int32_t number = 0;
    std::ofstream file_write("BinNumbers.txt");
    srand((unsigned) time(NULL));
    number = rand();
    
    uniq_tveri_qanak -= counts_bit (number);
    around -= 32;
    if (!file_write) {
        std::cout << "file is'nt open" << std::endl;
        exit(1);
    }

    file_write << number;
    bool t = true;
    while (around > 0 && t) {
        k = 32;
        number = 0;
        while (k) {
            if(uniq_tveri_qanak != 0 && around > uniq_tveri_qanak) {
                number <<= 1;
                number += (rand() % 2);
                uniq_tveri_qanak -= (number & 1);
                around--;
            }
            else {
                t = false;
                break;
            }
            --k;
        }
        if (t) {
            file_write <<'\n' << std::to_string (number);                
        }
    }
    if (uniq_tveri_qanak != 0) {
        if (uniq_tveri_qanak % 32 != 0) {
            while (k) {
                number <<= 1;
                ++number;
                --k;
                --uniq_tveri_qanak;
                --around;
            }
            file_write << '\n' << std::to_string(number);
        }
        while (around > 0) {
            around -= 32;
            uniq_tveri_qanak -= 32;
            file_write << '\n' << std::to_string(length_32);
        }
    }
    
    if (around % 32 != 0) {
        while (k) {
            number <<= 1;
            --k;
            --around;
        }
        file_write << '\n' << std::to_string(number);
    }
    
    while (around) {
        file_write << '\n' << std::to_string(0);
        around -= 32;
    }
    file_write.close();
}
// cragir@ gorcum e erb around@ 2 i astichan e ev mec e kam havasar 64 
// 1 eri qanak@ bnakanabar poqr e kam havasar around - 32 ic; 
int main() {
    
    //const u_int32_t count = 4000000000;
    //const u_int32_t aroundInt = 4294967295;
    //const u_int32_t count = 315000;
    //const u_int32_t aroundInt = 320000;
    //generate_numbers (count,aroundInt);
    //count_bits_all_file();
    crete_finale_file();
    //print_file();
}