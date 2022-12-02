#include <functional>
#include <vector>
#include "forward.h"
using namespace std;

const float maxFillFactor = 0.5;
const int maxCollision = 3;

template<typename TK, typename TV>
class ChainHash
{
private:    
    struct Entry{
        TK key;
        TV value;
        size_t hashcode;
        Entry(){}
        Entry(TK _k, TV _v, size_t h){
            key = _k;
            value = _v;
            hashcode = h;
        }
    };
    ForwardList<Entry>* array; //array of foward list (entry)
    vector<size_t> buckethash; //index, hashcode -> almacena pos y hashcode para acceder por índice
    int capacity;
    int size;
    hash<TK> getHash; // get hash funtion

    bool esta(TK key, TV value, int index){
        for (auto it: array[index]){
            if(it.key == key){
                return true;
            }
        }
        return false;
    }

public:
    ChainHash(int _capacity = 5){
        this->capacity = _capacity;
        this->array = new ForwardList<Entry>[this->capacity];
        this->size = 0;
    }    

    float fillFactor(){
        return size / (capacity * maxCollision);
    }

    void insert(TK key, TV value){
        if(fillFactor() >= maxFillFactor) rehashing();
        size_t hashcode = getHash(key);
        int index = hashcode % capacity;
        if (!esta(key, value, index)) {
            array[index].push_front(Entry(key, value, hashcode));
            buckethash.push_back(hashcode);
            size++;
        }   
    }

    TV get(TK key){
        size_t hashcode = getHash(key);
        int index = hashcode % capacity;
        //TODO: iterar en la lista array[index] 
        for (auto it: array[index]){
            if(it.key == key){
                return it.value;
            }
        }
    }
    
    TV& operator[](const TK& key){
        size_t hash = getHash(key);
        int index = hash % capacity;
        for (Entry& entry : array[index]){
            if (entry.key == key){
                return key.value;
            }
        }
        throw ("No se encontro");
    }

    void rehashing(){

        auto tempcapacity = capacity;
        
        capacity*=2;

        ForwardList<Entry>* temp = new ForwardList<Entry>[this->capacity*2];
        auto indx = 0;
        for(auto i = 0; i < tempcapacity; i++){
            for(auto it : array[i]){
                int index = it.hashcode % capacity;
                temp[index].push_front(Entry(it.key, it.value, it.hashcode));
            }
        }

        delete [] array;
        array = temp;

    }

    void remove(TK key){
        //TODO
        size_t hashcode = getHash(key);
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
    
    typename ForwardList<Entry>::iterator begin(int i_bucket){
        return array[i_bucket].begin();
    }

    typename ForwardList<Entry>::iterator end(int i_bucket){
        return array[i_bucket].end();
    }

    ~ChainHash(){
        //TODO: liberar cada lista
        delete[] this->array;
    }
};