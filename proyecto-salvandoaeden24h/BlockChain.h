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

    void alter_block_by_index( int index, Transaction* new_data, Block* bloque ) {
        if (bloque->get_index() == index) {
            bloque->set_data(new_data);
            bloque->remake_hash_code();
        } else {
            alter_block_by_index( index, new_data, bloque->prev);
        }

        bloque->remake_hash_code();
    }

    void alter_block_by_index(int index, Transaction* new_data) {
        alter_block_by_index(index, new_data, this->chain);
    }
};