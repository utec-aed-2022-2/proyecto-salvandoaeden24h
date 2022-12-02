#include <functional>
#include <vector>
#include "forward.h"
#include "transaction.h"
using namespace std;

const float maxFillFactor = 0.5;
const int maxCollision = 3;

template<typename EyR, typename MT, typename dt>
class ChainHash
{
private: 
    ForwardList<Transaction>* array; //array of foward list (entry)
    int capacity;
    int size;
    hash<EyP> getHash; // get hash funtion

    bool esta(EyR emisor, EyR receptor, MT monto, dt date, int index){
        for (auto it: array[index]){
            if(it.emisor == emisor && it.receptor == receptor && it.monto == monto && it.date == date){
                return true;
            }
        }
        return false;
    }

public:
    ChainHash(int _capacity = 5){
        this->capacity = _capacity;
        this->array = new ForwardList<Transaction>[this->capacity];
        this->size = 0;
    }    

    float fillFactor(){
        return size / (capacity * maxCollision);
    }

    void insert(EyR emisor, EyR receptor, MT monto, dt date){
        if (fillFactor() >= maxFillFactor) rehashing();
        size_t hashcode = getHash(emisor);

        int index = hashcode % capacity;
        if (!esta(emisor, receptor, monto, date, index)) {
            array[index].push_front(Transaction(emisor, receptor, monto, date));
            size++;
        }   
    }

    vector<Transaction> get(EyR emisor){
        vector<Transaction> transacciones;

        size_t hashcode = getHash(emisor);
        int index = hashcode % capacity;

        for (auto it: array[index]){
            if(it.emisor == emisor){
                transacciones.push_back(it);
            }
        }

        return transacciones;
    }
    
    vector<Transaction> operator[](const EyR& emisor){
        vector<Transaction> transacciones;

        size_t hashcode = getHash(emisor);
        int index = hashcode % capacity;

        for (auto it: array[index]){
            if(it.emisor == emisor){
                transacciones.push_back(it);
            }
        }

        return transacciones;
    }

    void rehashing(){

        auto tempcapacity = capacity;
        capacity*=2;
        ForwardList<Transaction>* temp = new ForwardList<Transaction>[this->capacity*2];

        for(auto i = 0; i < tempcapacity; i++){
            for(auto it : array[i]){
                int index = getHash(it.emisor) % capacity;
                temp[index].push_front(Transaction(emisor, receptor, monto, date));
            }
        }

        delete [] array;
        array = temp;

    }

    void remove(EyR emisor){

        size_t hashcode = getHash(emisor);
        int index = hashcode % capacity;
        for(auto it : array[index]){
            if(it.key == key){
                erase(array[index].it);
                size--;
            }
        }
    }

    int bucket_count(){
        return capacity;
    }

    int bucket_size(int i_bucket){        
        return std::distance(array[i_bucket].begin(), array[i_bucket].end());
    }
    
    typename ForwardList<Transaction>::iterator begin(int i_bucket){
        return array[i_bucket].begin();
    }

    typename ForwardList<Transaction>::iterator end(int i_bucket){
        return array[i_bucket].end();
    }

    ~ChainHash(){
        delete[] this->array;
    }
};