#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Orders {
    Customer* cus;
    Dish* dish;
    int price;
};

class Customer{
    string name;
    string cint;
    vector <Orders> orders;
public:
    //void set_name(const string &name) {this->name = name;}
    const string get_name() {return this->name;}
    const string get_cint() {return this->cint;}
    Customer(const string & name, const string & cint) {this->name = name; this->cint = cint;}
};

class Menu {
    virtual map<Dish*,int> getters() = 0;
    virtual void add() = 0;
public:
    virtual ~Menu();
};

class Dish{
    string name;
public:

};

class appetizer: public Menu {
    map <Dish,int> my_map;
    map<Dish*,int> getters() {};
    void add(){}
};

int main() {

}