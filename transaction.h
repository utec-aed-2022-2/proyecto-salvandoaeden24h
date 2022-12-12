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
        string dt = asctime(localtime(&this->date));
        dt.pop_back();
        cout << '(' << emisor << ',' << receptor << ',' << monto << ',' << dt << ')' << endl;
    }
};

bool operator < (Transaction t1, Transaction* t) {
    return t1.date < t->date;
}

bool operator > (Transaction t1, Transaction* t) {
    return t1.date > t->date;
}

bool operator == (Transaction t1, Transaction* t) {
    return t1.date == t->date;
}

ostream& operator << (ostream& os, Transaction* t) {
    string dt = asctime(localtime(&t->date));
    dt.pop_back();
    os << '(' << t->emisor << ',' << t->receptor << ',' << t->monto << ',' << dt << ')';
    return os;
}