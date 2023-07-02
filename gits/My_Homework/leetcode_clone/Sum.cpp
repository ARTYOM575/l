#include <iostream>
#include <fstream>

int sum (int a, int b) {
    return a + b;
}

int main (int a, char* arg[]) {
    std::ofstream file_write("result.txt");
    file_write << sum(std::stoi(arg[1]),std::stoi(arg[2]));
    file_write.close();
    return 0;
}