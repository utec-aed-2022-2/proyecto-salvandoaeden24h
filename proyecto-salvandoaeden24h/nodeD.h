#ifndef NODED_H
#define NODED_H

template <typename T>
struct NodeD
{
    T data;
    NodeD<T> *next;
    NodeD<T> *prev;

    NodeD()
    {
        this->next = nullptr;
        this->prev = nullptr;
    };

    NodeD(T value)
    {
        this->data = value;
        this->next = nullptr;
        this->prev = nullptr;
    }

    void killSelf()
    {
        this->data = NULL;
        delete this->next;
        delete this->prev;
    }
};

#endif