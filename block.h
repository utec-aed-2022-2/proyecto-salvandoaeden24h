#include <string>
#include "hash.h"
#include "transaction.h"
using namespace std;

class Block {
    int index;
    int nonce = 0;
    string hashCode;
    string prevHashCode;
    Transaction* data;

    string generate_hash() {
        string information;
        if (this->prev == nullptr) {
            return "0000000000000000000000000000000000000000000000000000000000000000";
        } else {
            information = to_string(this->nonce) + to_string(this->index) + this->prev->get_hashcode() + data->get_info_to_hash();
        }
        return hash_information(information);
    }

    public:
    Block* prev;
    Block(Transaction* data_, int i, Block* previous): index(i), prev(previous), data(data_) {
        if (previous != nullptr) {
            this->prevHashCode = previous->get_hashcode();
        } else {
            this->prevHashCode = "0000000000000000000000000000000000000000000000000000000000000000";
        }
        do {
            this->nonce++;
            this->hashCode = generate_hash();
        } while(!isHashValid());
    };

    void remake_hash_code() {
        this->prev->make_self_hash_code();
        this->prevHashCode = this->prev->get_hashcode();
        this->hashCode = generate_hash();
    }

    void make_self_hash_code() {
        this->hashCode = generate_hash();
    }

    string get_hashcode() {   
        return this->hashCode;
    }

    string get_prev_hash() {
        return this->prev->generate_hash();
    }

    int get_index() {
        return this->index;
    }

    void set_data(Transaction* new_data) {
        this->data = new_data;
    }

    bool isHashValid() {
        if (generate_hash() == this->hashCode) {
            if (this->hashCode[0] == '0' && this->hashCode[1] == '0' && this->hashCode[2] == '0' && this->hashCode[3] == '0') {
                return true;
            }
        }
        return false;
    }

    void print_block() {
        cout << "Indice: " << this->index << endl;
        cout << "HashCode: " << this->hashCode << endl;
        cout << "Prev HashCode: " << this->prevHashCode << endl;
        this->data->print_transaction();
        cout << endl;
    }

    void mine() {
        this->nonce = 0;
        do {
            this->nonce++;
            this->hashCode = generate_hash();
        } while(!isHashValid());
    }
};