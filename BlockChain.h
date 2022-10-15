#include "block.h"
#include "forward.h"

class BlockChain {
    ForwardList<Block*> chain;

    Block* createGenesisBlock() {
        Transaction* data = new Transaction("", "", 0, 0);
        Block* genesis = new Block(data, 0, nullptr);
        return genesis;
    }

    public:

    BlockChain() {
        Block* genesis = createGenesisBlock();
        chain.push_front(genesis);
    }
    
    void insertBlock(Transaction* trans) {
        int index = chain.size() - 1;
        Block* block = new Block(trans, index, chain.front());
    }
};