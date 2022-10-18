#include <string>
#include "hash.h"
#include "information.h"
using namespace std;

class Block {
    int index; //indice del bloque en la blockchain
    int nonce = 0; //
    string hashCode; //código hasheado
    string prevHashCode; //código hasheado del código anterior
    Information* data; // es la colección de información unida en un string

    string generate_hash() { // retorna el código hash generado por todo el bloque, mas aún no es asignado. (Retorna lo que debería ser el hash)
        //si es el bloque génesis retorna 0 x64
       // sino, concatena la información del bloque y lo hashea.
        string information;
        if (this->prev == nullptr) {
            return "0000000000000000000000000000000000000000000000000000000000000000";
        } else {
            information = to_string(this->nonce) + to_string(this->index) + this->prev->get_hashcode() + data->get_all_info();
        }
        return hash_information(information);
    }

    public:
    Block* prev; // un puntero al bloque anterior
    Block(Information* data_, int i, Block* previous): index(i), prev(previous), data(data_) { //constructor del bloque
        //le paso la data previamente contruida + índice del nuevo bloque + índice al bloque anterior
        if (previous != nullptr) {
            this->prevHashCode = previous->get_hashcode();
        } else {
            this->prevHashCode = "0000000000000000000000000000000000000000000000000000000000000000";
        }
        do {
            this->nonce++; //aumenta de uno en uno hasta que en algún momento el código hash empiece con 4 0's. Acaba si se cumple
            this->hashCode = generate_hash();
        } while(!isHashValid());
    };

    void remake_hash_code() {
        this->prev->make_self_hash_code();
        this->prevHashCode = this->prev->get_hashcode();
        this->hashCode = generate_hash();
    }

    void make_self_hash_code() { //rehacer el código hash y se vuelve a asignar al bloque
        this->hashCode = generate_hash();
    }

    string get_hashcode() {   //getter
        return this->hashCode;
    }

    string get_prev_hash() { //getter
        return this->prev->generate_hash();
    }

    int get_index() { //getter
        return this->index;
    }

    void set_data(Information* new_data) { //asigna a la trasacción
        this->data = new_data;
    }

    bool isHashValid() { //un código hash es válido si es que la función generada por el generade hash es la función generada por el bloque
        if (generate_hash() == this->hashCode) {
            if (this->hashCode[0] == '0' && this->hashCode[1] == '0' && this->hashCode[2] == '0' && this->hashCode[3] == '0') {
                return true;
            }
        }
        return false;
    }

    void print_block() { //imprime el bloque
        cout << "Indice: " << this->index << endl;
        cout << "Nonce: " << this->nonce << endl;
        cout << "HashCode: " << this->hashCode << endl;
        cout << "Prev HashCode: " << this->prevHashCode << endl;
        this->data->print_transaction();
        cout << endl;
    }

    void mine() { //cuando se cambia la info del bloque, el código hash del bloque cambia por lo que deja de empezar con 4 0's y se vuelve inválido. La función mine se encarga de hacer empezar con 4 0's pero con nueva información para que la cadena sea aceptada.
        //Esta función ese l proof of work
        // Hace que el código hash sea válido solo para este bloque
        this->nonce = 0;
        do {
            this->nonce++;
            this->hashCode = generate_hash();
        } while(!isHashValid());
    }
};