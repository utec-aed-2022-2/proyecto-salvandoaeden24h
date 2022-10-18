#include <iostream>
#include "block.h"

class BlockChain {
    Block* chain = nullptr; //el chain es el puntero al último bloque que hay (un puntero al head del forward list)

    int size; //size del blockhain

    Block* createGenesisBlock() { //crea un blocke génesis (FECHA VACÍA, TRANSACCIONES 0, FECHA 0, ÍNDICE 0, PREV NULL)
        Transaction* data = new Transaction("", "", 0, 0);
        Information* info = new Information();
        info->new_transaction(data);
        Block* genesis = new Block(info, 0, nullptr);
        return genesis;
    }

    void alter_block_by_index( int index, Information* new_data, Block* bloque ) { // Altera el bloque a partir del índice, por lo que hace una búsqueda.
        //Función recursiva
        if (bloque->get_index() == index) { //si el índice del bloque es correcto: alteras info y vuelves hacer el hash
            bloque->set_data(new_data);
            bloque->remake_hash_code(); //como es recursivo, rehace el hashcode de todo el blockain
        } else {
            alter_block_by_index( index, new_data, bloque->prev); //aplica la misma función pero al prev
        }
        bloque->remake_hash_code();
    }

    void fix_for_index(int index, Block* bloque) { //arregla todos los códigos hash a partir de cierto índice.
        //Si se cambia el código del índice x, arregla desde el índice x al z (hasta el final de la blocckain) de forma recursiva.
        if (bloque->get_index() != index){
            fix_for_index(index, bloque->prev);
        }
        bloque->mine(); //mino
        bloque->remake_hash_code(); //rehago el código del bloque
    }

    public:

    BlockChain() { //
        Block* genesis = createGenesisBlock(); //creo el bloque génesis
        this->chain = genesis; // puntero a génesis
        this->size = 1; // el primer bloque
    }

    void insertBlock(Information* trans) { // para insertar debo insertar una transacción que estará contenida en el bloque
        int index = this->size; // empieza desde el índice 1 (revisar BlockChain())
        Block* new_block = new Block(trans, index, chain); // para crear el bloque le paso la transacción, el index y el chain que será puesto por delante
        this->chain = new_block; // el hain ahora es el nuevo bloque
        this->size++; //aumento el size
    }

    bool isChainValid() {
        Block* temp = this->chain; //empiezo con un temporal a partir del último bloque (recorre hasta el génesis en el peor de los casos)

        while (temp->prev != nullptr) { //hash no válido
            if (!temp->isHashValid()) {
                return false;
            }

            if (this->size > 1 && temp->get_prev_hash() != temp->prev->get_hashcode()) { //si el hash anterior es distinto de lo que tiene a lo que debería tener (en el hash)
                return false; //no es válido
            }
            temp = temp->prev; // si no pasa nada, avanza para adelante
        }
        return true;
    }

    void printBlockChain() { //imprime el bloque
        Block* temp = this->chain;

        while (temp->prev != nullptr) {
            temp->print_block();
            temp = temp->prev;
        }

    }

    void alter_block_by_index(int index, Information* new_data) { //función recursiva que hace que la función del index
        alter_block_by_index(index, new_data, this->chain);
    }

    void fix_for_index(int index) {
        fix_for_index(index, this->chain );
    }
};