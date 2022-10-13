#include <string>
#include "hash.h"
using namespace std;

struct Block {
    string hashCode;
    Block* prev;
    string data;

    Block(string data_=""): data(data_) {
        hashCode = hash_information(this->data);
    };
};