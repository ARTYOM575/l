#include <ctime>
#include <string>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <fstream>
#include "function.h"
#include "to_do_list.h"


int main() {
    pthread_t System;
    int res = pthread_create(&System, nullptr,Art::Shell,nullptr );
    pthread_t System1;
    int res1 = pthread_create(&System1, nullptr,Art::Sys_,nullptr );
    
    res1 = pthread_join(System1, nullptr);
    res = pthread_join(System, nullptr);
}