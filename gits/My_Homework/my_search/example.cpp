#include <iostream>
#include <cstring>
using namespace std;

string longestPalindrome(string s) {
    string res = "";
    bool t = true;
    short count = 0;
    short size = s.length() - 1;
    char* begin = &s[0];
    char* end = &s[0] + s.length() - 1;
    char* result_position_begin = begin;
    char* temp_begin = begin;
    char* temp_end = end;
    while (begin < end) {
        temp_end = end;
        while (temp_end > temp_begin) {
            t = true;
            temp_begin = begin;
            end = temp_end;
            while (end > temp_begin) {
                if (*end != *temp_begin) {
                    t = false;
                    break;
                }
                --end;
                ++temp_begin;
            }
            if (t && temp_end - begin > count) {
                result_position_begin = begin;
                count = temp_end - begin;
                break;
            }
            --temp_end;
        }
        end = &s[0] + size - 1;
        ++begin;
    }
    for (int i = 0; i <= count; ++ i) {
        res += result_position_begin[i];
    }
    return res;
}

int main() {
    std::cout << longestPalindrome( "abfbaaaaaaa") << std::endl;
}