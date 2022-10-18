#include <iostream>
#include "BlockChain.h"

using namespace std;

int main() {
    Transaction* data = new Transaction("", "", 0, 0);
    Information* info = new Information();
    info->new_transaction(data);

    BlockChain Bitcoin;

    Transaction* data1 = new Transaction("Luis", "Coco", 123123.234, 912873981723987);
    Transaction* data2 = new Transaction("Pedro", "Martin", 234234.234, 7512437651231);
    Transaction* data3 = new Transaction("Luis", "Paolo", 87126344.61523, 123123123123123123);
    Transaction* data4 = new Transaction("Gabriel", "Pedro", 918273.12736, 871725638765123);
    Transaction* data5 = new Transaction("Enrique", "Popo", 9102783.176253, 761523765123123);
    Transaction* data6 = new Transaction("Paolo", "Pipi", 918273.126534, 87162387612381276);
    Transaction* data7 = new Transaction("Kevin", "Pupu", 918273.127635, 817276387162387612);
    Transaction* data8 = new Transaction("Explorer", "Purple", 123123.234, 817623876218736);
    Transaction* data9 = new Transaction("Explorer2", "Purple2", 345123.234, 912837981273312);

    Information* info1 = new Information();
    Information* info2 = new Information();
    Information* info3 = new Information();
    Information* info4 = new Information();
    Information* info5 = new Information();
    Information* info6 = new Information();
    Information* info7 = new Information();
    Information* info8 = new Information();

    info1->new_transaction(data1);
    info2->new_transaction(data2);
    info3->new_transaction(data3);
    info4->new_transaction(data4);
    info5->new_transaction(data5);
    info6->new_transaction(data6);
    info7->new_transaction(data7);
    info8->new_transaction(data8);
    info8->new_transaction(data9);

    Bitcoin.insertBlock(info1);
    Bitcoin.insertBlock(info2);
    Bitcoin.insertBlock(info3);
    Bitcoin.insertBlock(info4);
    Bitcoin.insertBlock(info5);
    Bitcoin.insertBlock(info6);
    Bitcoin.insertBlock(info7);
    Bitcoin.insertBlock(info8);
    Bitcoin.printBlockChain();
    cout << "\nIs chain valid " << Bitcoin.isChainValid() << endl << endl;

    Transaction* hack = new Transaction("Heider", "pipipi", 81726387.1231, 817236817263);
    Information* hack2 = new Information();
    hack2->new_transaction(hack);
    Bitcoin.alter_block_by_index(4, hack2);//altero el bloque de índice 4
    Bitcoin.printBlockChain();
    cout << "\nIs chain valid " << Bitcoin.isChainValid() << endl; //imprime que no es válido

    Bitcoin.fix_for_index(4); //arregla la blockhain a partir del índice 4
    Bitcoin.printBlockChain();
    cout << "\nIs chain valid " << Bitcoin.isChainValid() << endl; //imprime que es válido

}