#include <iostream>
#include <map>
#include <cstring>
#include <set>

using namespace std;

bool foo(map<char,int> my_string_, char* end) {
    while (*end != '\0' && !my_string_.empty()) {
        std::cout <<"end    " <<*end  <<std::endl;
        if (my_string_.find(*end) != my_string_.end()) {
            my_string_[*end] -= 1;
        }
        if (my_string_[*end] == 0)
            my_string_.erase(*end);
        ++end;
    }
    std::cout << std::endl;
    if (my_string_.empty())
        return true;
    return false;
}

int main() {
    set <char> word;
    string temp_result;
    char ch;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string result;
    map<char,int> my_string;
    
    char* begin = &t[0];
    char* end;
    char* temp_begin;
    while (*begin != '\0') {
        if (my_string.find(*begin)!= my_string.end()) {
            my_string[*begin] +=1;
        }
        else {
            my_string[*begin] = 1;
            word.insert(*begin);
        }   
        ++begin;
    }
    map<char,int> my_string_copy(my_string);
    begin = &s[0];
    end = begin;
    for (auto i:my_string_copy) {

        std::cout << i.first << "  "<<i.second << std::endl;
    }
    while (*end != '\0' && !my_string.empty()) {
        if (my_string.find(*end) != my_string.end()) {
            my_string[*end] -= 1;
        }
        if (my_string[*end] == 0)
            my_string.erase(*end);
        ++end;
    }
    result = s.substr(0,end - begin);
    //std::cout << result<< std::endl;
    while (*end != '\0' ) {
        ch = *begin;
        ++begin;
        if (word.count(ch)) {
            while (*end != '\0' && *end != ch) {
                ++end;
            }
            temp_begin = begin;
            while (*begin != '\0' && begin < end && foo (my_string_copy,temp_begin)) {
                temp_begin = begin;
                ++begin;
                //std::cout << *begin;
            }
            if (end - begin < result.length()) {
               result =  s.substr(begin - &s[0],end - begin);  
            }
            //std::cout << temp_result << std::endl;
            //if (temp_result.length() < result.length()) 
            //    result = temp_result; 
        }
        //std::cout << end - begin << std::endl;
    }
    //std::cout<<std::endl << result;
}