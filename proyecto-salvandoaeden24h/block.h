#include <string>
#include "hash.h"
#include "transaction.h"
using namespace std;

class Block {
    int index;
    string hashCode;
    string prevHashCode;
    Transaction* data;

    string generate_hash() {
        string information;
        if (this->prev == nullptr) {
            return this->hashCode;
        } else {
            information = to_string(this->index) + this->prev->get_hashcode() + data->get_info_to_hash();
        }
        return hash_information(information);
    }

    public:
    Block* prev;
    Block(Transaction* data_, int i, Block* previous): index(i), prev(previous), data(data_) {
        if (previous != nullptr) {
            this->prevHashCode = previous->get_hashcode();
        } else {
            this->prevHashCode = hash_information("");
        }
        hashCode = generate_hash();
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
        return generate_hash() == this->hashCode;
    }

    void print_block() {
        cout << "Indice: " << this->index << endl;
        cout << "HashCode: " << this->hashCode << endl;
        cout << "Prev HashCode: " << this->prevHashCode << endl;
        this->data->print_transaction();
        cout << endl;
    }
};