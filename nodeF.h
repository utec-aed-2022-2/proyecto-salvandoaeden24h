#ifndef NODEF_H
#define NODEF_H

template <typename T>
struct NodeF {
    T data;
    NodeF<T>* next;

    NodeF() {
        this->next = nullptr;
    };

    NodeF(T value){
        this->data = value;
        this->next = nullptr;
    }

    void killSelf(){
        this->data = NULL;
        delete this->next;
    }
};

#endif