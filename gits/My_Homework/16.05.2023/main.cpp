#include <iostream>
#include "my_list.h"
#include "my_vector.h"

#include <chrono>
#include <sstream>
#include <fstream>
//using namespace ART;
auto my_timer (int count,ART::vector<int>* vec,void ((ART::vector<int>::*func))(int)) {
    auto startTime = std::chrono::high_resolution_clock::now();
    while (count) {
        (vec->*func)(rand());
        --count;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return duration.count();
}

auto my_timer (int count,ART::vector<int>*vec,void(ART::vector<int>::*func)()) {
    auto startTime = std::chrono::high_resolution_clock::now();
    while (count) {
        (vec->*func) ();
        --count;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return duration.count();
}

auto my_timer (int position,ART::vector<int>*vec,void(ART::vector<int>::*func)(const int&,long)) {
    auto startTime = std::chrono::high_resolution_clock::now();
    (vec->*func) (rand(),position);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return duration.count();
}

auto my_timer (int count,ART::list<int>* list_,void ((ART::list<int>::*func))(int)) {
    auto startTime = std::chrono::high_resolution_clock::now();
    while (count)
    {
        (list_->*func)(rand());
        --count;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return duration.count();
}

auto my_timer (int count,ART::list<int>* list_,void ((ART::list<int>::*func))()) {
    auto startTime = std::chrono::high_resolution_clock::now();
    while (count)
    {
        (list_->*func)();
        --count;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return duration.count();
}

auto my_timer (int position,ART::list<int>*list_,void(ART::list<int>::*func)(const int&,long)) {
    auto startTime = std::chrono::high_resolution_clock::now();
    (list_->*func) (rand(),position);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return duration.count();
}

int main() {
    std::ofstream file_write ("my_file.txt");
    if (!file_write) {
        std::cout << "file is'nt open" << std::endl;
        return 1;
    }
    ART::list<int> list_(20);
    ART::vector<int> vector_;
    vector_.push_back(20);
    file_write << "vector  push_back  1000 element -   ";
    file_write << my_timer(1000,&vector_,&ART::vector<int>::push_back) << " ms" <<'\n';
    file_write << "vector  push_back  10000 element -   ";
    file_write << my_timer(10000,&vector_,&ART::vector<int>::push_back) << " ms" <<'\n';
    file_write << "vector  push_back  100000 element -   ";
    file_write << my_timer(100000,&vector_,&ART::vector<int>::push_back) << " ms" <<'\n';
    
    file_write << "list  push_back  1000 element -   ";
    file_write << my_timer(1000,&list_,&ART::list<int>::push_back) <<  " ms" << '\n';
    file_write << "list  push_back  10000 element -   ";
    file_write << my_timer(10000,&list_,&ART::list<int>::push_back) <<  " ms" << '\n';
    file_write << "list  push_back  100000 element -   ";
    file_write << my_timer(100000,&list_,&ART::list<int>::push_back) <<  " ms" << '\n';

    file_write << "111001 element vector  insert  0 position -   ";
    file_write << my_timer(0,&vector_,&ART::vector<int>::insert) << " ms" <<'\n';
    file_write << "111001 element vector  insert  medium position -   ";
    file_write << my_timer(55500,&vector_,&ART::vector<int>::insert) << " ms" <<'\n';
    file_write << "111001 element vector  insert  111001 position -   ";
    
    file_write << my_timer(vector_.get_size() - 1,&vector_,&ART::vector<int>::insert) << " ms" <<'\n';
    file_write << "111001 element list  insert  0 position -   ";
    file_write << my_timer(0,&list_,&ART::list<int>::insert) << " ms" <<'\n';
    file_write << "111001 element list  insert  medium position -   ";
    file_write << my_timer(55500,&list_,&ART::list<int>::insert) << " ms" <<'\n';
    file_write << "111001 element list  insert  111001 position -   ";
    file_write << my_timer(list_.get_size() - 1,&list_,&ART::list<int>::insert) << " ms" <<'\n';


    file_write << "vector pop_back 1000 elemet -   ";
    file_write << my_timer(1000,&vector_,&ART::vector<int>::pop_back) << " ms" <<'\n';
    file_write << "vector pop_back 10000 elemet -   ";
    file_write << my_timer(10000,&vector_,&ART::vector<int>::pop_back) << " ms" <<'\n';
    file_write << "vector pop_back 100000 elemet -   ";
    file_write << my_timer(100000,&vector_,&ART::vector<int>::pop_back) << " ms" <<'\n';
    
    file_write << "list  pop_back  1000 element -   ";
    file_write << my_timer(1000,&list_,&ART::list<int>::pop_back) <<  " ms" << '\n';
    file_write << "list  pop_back  10000 element -   ";
    file_write << my_timer(10000,&list_,&ART::list<int>::pop_back) <<  " ms" << '\n';
    file_write << "list  pop_back  100000 element -   ";
    file_write << my_timer(100000,&list_,&ART::list<int>::pop_back) <<  " ms" << '\n';
    file_write.close();
    //ART::list<int> lists(7);
    //lists.push_back(100);
    //lists.push_back(1000);
    //ART::vector<int> vectors(2);
    //vectors[0] = 20;
    //vectors[1] = 30;
    //ART::list<int>::iterator list_it = lists.begin();
    //ART::vector<int>::iterator vec_it = vectors.begin();
    //while (list_it != nullptr) {
    //    std::cout << *list_it << "  ";
    //    ++list_it;
    //}
    //std::cout << std::endl;
    //while (vec_it != vectors.end()) {
    //    std::cout << *vec_it << "  ";
    //    ++vec_it;
    //}
    //std::cout << std::endl;
    //return 0;
}