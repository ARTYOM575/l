#include <iostream>
#include <vector> 
using namespace std;
class Customer {
    string name;
    string address;
    string contact;
    vector <Account> accounts;
public:
    void set_name(string name) {this->name = name;}
    string get_name() {return this->name;}
    void set_address(string address) {this->address = address;}
    string set_address() {return this->address;}
    void set_contact (string contact) {this->contact = contact;}
    string get_contact () {return this->contact;}
    //Account* get_acc (int i) {return accounts[i];}
};



class Account {
    string aType;
    double aBalance;
    int Arate;
    vector<Transaction*> tra;
public:
    string get_aType() {return this->aType;}
    double get_aBalance () {return this->aBalance;}
    int Arate () {return this->Arate;}
    void add_balance (double bal) {this->aBalance += bal;}
    void minus_balance (double bal) {this->aBalance -= bal;}

    void add_transaction (Account * acc) {
        Transaction * tran = new Transaction;
        tran->set_trans_type(this->aType);
        tran->set_amuont (this->Arate);
        tra.push_back(tran);
        
    }

    virtual void deposit (double num) = 0;
    virtual void wildraw (double num) = 0;
    virtual void transfer(Account* acount, double num) = 0;
};
class Transaction {
    Account* account;
    string trans_type;
    double amount;
public:
    void set_trans_type (string type) {this->trans_type = type;}
    void set_amuont (double arate) {this->amount = arate;}
};
class savingAccount:public Account {
    void deposit (double num) {
        add_balance (num);
    }
    void wildraw (double num) {
        minus_balance(num);
    }
    void transfer(Account * account ,double num) {
        account->add_balance (num);
        minus_balance(num);
    }
};
