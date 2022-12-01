#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;

struct Transaction {
    string emisor, receptor;
    double monto;
    time_t date;

    Transaction()=default;
    
    Transaction( string s1, string s2, double num):
    emisor(s1), receptor(s2), monto(num) {
        this->date = time(nullptr);
    }

    Transaction( string s1, string s2, double num, time_t _date):
    emisor(s1), receptor(s2), monto(num), date(_date) {}

    string get_info_to_hash() {
        string result = this->emisor + this->receptor + to_string(this->monto) + to_string(this->date);
        return result;
    }

    void print_transaction() {
        cout << '(' << emisor << ',' << receptor << ',' << monto << ',' << date << ')' << endl;
    }
};