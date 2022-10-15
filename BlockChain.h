#include <iostream>
#include "block.h"
#include "forward.h"

class BlockChain {
    Block* chain = nullptr;

    int size;

    Block* createGenesisBlock() {
        Transaction* data = new Transaction("", "", 0, 0);
        Block* genesis = new Block(data, 0, nullptr);
        return genesis;
    }

public:

    BlockChain() {
        Block* genesis = createGenesisBlock();
        this->chain = genesis;
        this->size = 1;
    }

    void insertBlock(Transaction* trans) {
        int index = this->size;
        Block* new_block = new Block(trans, index, chain);
        this->chain = new_block;
        this->size++;
    }

    bool isChainValid() {
        Block* temp = this->chain;

        while (temp->prev != nullptr) {
            if (!temp->isHashValid()) {
                return false;
            }

            if (this->size > 1 && temp->get_prev_hash() != temp->prev->get_hashcode()) {
                cout << "PREV??" << endl;
                return false;
            }
            temp = temp->prev;
        }
        return true;
    }

    void printBlockChain() {
        Block* temp = this->chain;

        while (temp->prev != nullptr) {
            temp->print_block();
            temp = temp->prev;
        }

    }

    /*
    void try_hack_index(int index, Transaction* hackeo) {
        Block* temp = this->chain;

        while(temp->get_index() != index) {
            temp = temp->prev;

        }
    }*/
};