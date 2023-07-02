#include <iostream>
#include <fstream>

int* get_testing (std::string line) {
    int* number = new int [3];
    std::string numbers[3];
    int size;
    int k = 0;
    numbers[0].clear();
    numbers[1].clear();
    numbers[2].clear();
    size = line.length();
    for (int i = 0 ; i < size; ++i) {
        while (line[i] != ',' && i < size) {
            numbers[k] += line[i];
            ++i;
        }
        numbers[k] += '\0';
        number[k] = std::stoi(numbers[k]);
        ++k;
    }
    
    return number;
}
