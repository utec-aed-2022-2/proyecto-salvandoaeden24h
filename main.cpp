#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include "BlockChain.h"

using namespace std;

void proof_of_work() {
    BlockChain* Bitcoin = new BlockChain();

    Transaction* data1 = new Transaction("Luis", "Coco", 123123.234);
    Information* info1 = new Information();
    info1->new_transaction(data1);
    Bitcoin->insertBlock(info1);

    Transaction* data2 = new Transaction("Pedro", "Martin", 234234.234);
    Information* info2 = new Information();
    info2->new_transaction(data2);
    Bitcoin->insertBlock(info2);

    Transaction* data3 = new Transaction("Luis", "Paolo", 871263.61523);
    Information* info3 = new Information();
    info3->new_transaction(data3);
    Bitcoin->insertBlock(info3);

    Transaction* data4 = new Transaction("Gabriel", "Pedro", 918273.12736);
    Information* info4 = new Information();
    info4->new_transaction(data4);
    Bitcoin->insertBlock(info4);

    Transaction* data5 = new Transaction("Enrique", "Popo", 9102783.176253);
    Information* info5 = new Information();
    info5->new_transaction(data5);
    Bitcoin->insertBlock(info5);

    Transaction* data6 = new Transaction("Paolo", "Pipi", 918273.126534);
    Information* info6 = new Information();
    info6->new_transaction(data6);
    Bitcoin->insertBlock(info6);

    Transaction* data7 = new Transaction("Kevin", "Pupu", 918273.127635);
    Information* info7 = new Information();
    info7->new_transaction(data7);
    Bitcoin->insertBlock(info7);

    Transaction* data8 = new Transaction("Explorer", "Purple", 123123.234);
    Information* info8 = new Information();
    info8->new_transaction(data8);
    Transaction* data9 = new Transaction("Explorer2", "Purple2", 345123.234);
    info8->new_transaction(data9);
    Bitcoin->insertBlock(info8);

    Bitcoin->printBlockChain();
    cout << "\nIs chain valid " << Bitcoin->isChainValid() << endl << endl;

    Transaction* hack = new Transaction("Heider", "pipipi", 81726387.1231);
    Information* hack2 = new Information();
    hack2->new_transaction(hack);
    Bitcoin->alter_block_by_index(4, hack2);//altero el bloque de índice 4
    Bitcoin->printBlockChain();
    cout << "\nIs chain valid " << Bitcoin->isChainValid() << endl; //imprime que no es válido

    Bitcoin->fix_for_index(4); //arregla la blockhain a partir del índice 4
    Bitcoin->printBlockChain();
    cout << "\nIs chain valid " << Bitcoin->isChainValid() << endl; //imprime que es válido

}

void get_transaccions_from_csv(string filename, int min, int max) {
    string line;
    BlockChain Bitcoin;

    string emisor, receptor;
    Transaction* data = nullptr;
    Information* info = nullptr;

    ifstream input_file(filename);

    int n = rand()%(max - min+ 1) + min;

    bool skip = true;
    while (getline(input_file, line)){
        if (skip) {
            info = new Information();
            skip = false;
        } else {
            vector<string> palabras;
            string palabra = "";
            for (auto letra: line) {
                if (letra == ',') {
                    palabras.push_back(palabra);
                    palabra = "";
                } else {
                    palabra += letra;
                }
            }
            palabras.push_back(palabra);

            
            data = new Transaction(palabras.at(0), palabras.at(1), atof(palabras.at(2).c_str()), (time_t)strtol(palabras.at(3).c_str(), NULL, 10));

            if (n == 0) {
                n = rand()%51 + 20;
                info->new_transaction(data);
                Bitcoin.insertBlock(info);
                info = new Information();
            } else {
                info->new_transaction(data);
                n--;
            }
        }
    }
    Bitcoin.insertBlock(info);
    input_file.close();
    Bitcoin.printBlockChain();
    cout << "\nIs chain valid " << Bitcoin.isChainValid() << endl;
}

int main() {
    srand(time(nullptr));
    get_transaccions_from_csv("MOCK_DATA_DEMO.csv", 30, 50);
    return 0;
}