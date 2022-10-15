#include <string>
#include "hash.h"
#include "transaction.h"
using namespace std;

class Block {
    int index;
    string nonce;
    string hashCode;
    string prevHashCode;
    Block* prev;
    Transaction* data;

    string generate_hash() {
        string information = to_string(this->index) + this->nonce + prevHashCode + data->get_info_to_hash();
        return hash_information(information);
    }

    public:
    Block(Transaction* data_, int i, Block* previous): index(i), prev(previous), data(data_) {
        if (previous != nullptr) {
            this->prevHashCode = previous->get_hashcode();
        } else {
            this->prevHashCode = hash_information("");
        }
        hashCode = generate_hash();
    };


    string get_hashcode() {   
        return this->hashCode;
    }

    string get_prev_hash() {
        return this->prevHashCode;
    }

    bool isHashValid() {
        return generate_hash() == this->hashCode;
    }
};