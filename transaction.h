#include <iostream>
#include <string>
using namespace std;

struct Transaction {
    string str1, str2;
    double number;
    long long int date;

    Transaction()=default;

    Transaction( string s1, string s2, double num, long long int date_ ):
            str1(s1), str2(s2), number(num), date(date_) {

    }

    string get_info_to_hash() {
        string result = this->str1 + this->str2 + to_string(this->number) + to_string(this->date);
        return result;
    }

    void print_transaction() {
        cout << '(' << str1 << ',' << str2 << ',' << number << ',' << date << ')' << endl;
    }
};