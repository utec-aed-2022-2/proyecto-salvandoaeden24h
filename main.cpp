#include <iostream>
#include "BlockChain.h"

using namespace std;

int main() {
    BlockChain Bitcoin;

    Transaction* data1 = new Transaction("Luis", "Coco", 123123.234, 912873981723987);
    Transaction* data2 = new Transaction("Pedro", "Martin", 234234.234, 7512437651231);
    Transaction* data3 = new Transaction("Luis", "Paolo", 87126344.61523, 123123123123123123);
    Transaction* data4 = new Transaction("Gabriel", "Pedro", 918273.12736, 871725638765123);
    Transaction* data5 = new Transaction("Enrique", "Popo", 9102783.176253, 761523765123123);
    Transaction* data6 = new Transaction("Paolo", "Pipi", 918273.126534, 87162387612381276);
    Transaction* data7 = new Transaction("Kevin", "Pupu", 918273.127635, 817276387162387612);
    Transaction* data8 = new Transaction("Explorer", "Purple", 123123.234, 817623876218736);
    
    Bitcoin.insertBlock(data1);
    Bitcoin.insertBlock(data2);
    Bitcoin.insertBlock(data3);
    Bitcoin.insertBlock(data4);
    Bitcoin.insertBlock(data5);
    Bitcoin.insertBlock(data6);
    Bitcoin.insertBlock(data7);
    Bitcoin.insertBlock(data8);
    Bitcoin.printBlockChain();
    cout << "\nIs chain valid " << Bitcoin.isChainValid() << endl << endl;

    Transaction* hack = new Transaction("Heider", "pipipi", 81726387.1231, 817236817263);

    Bitcoin.alter_block_by_index(4, hack);
    Bitcoin.printBlockChain();
    cout << "\nIs chain valid " << Bitcoin.isChainValid() << endl;

    Bitcoin.fix_for_index(4);
    Bitcoin.printBlockChain();
    cout << "\nIs chain valid " << Bitcoin.isChainValid() << endl;

}