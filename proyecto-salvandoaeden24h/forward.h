#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"

using namespace std;

template<class T>
class FrwdIterator{
    private:
        NodeF<T>* current;
    public:
        FrwdIterator(){
            current = nullptr;
        }
        FrwdIterator(NodeF<T>* ptr){
            current = ptr;
        }

        FrwdIterator& operator++(){
            if (current == nullptr){
                throw("end of list");
            }
            
            current = current->next;
            return (*this);
        }

        T& operator*(){
            return current->data;
        }

        bool operator !=(const FrwdIterator<T> &iterator2){
            return this->current != iterator2.current;
        }
};

// TODO: Implement all methods
template <typename T>
class ForwardList : public List<T> {
    public:
        typedef FrwdIterator<T> iterator;
        iterator begin(){
            return iterator(head);
        }
        iterator end(){
            return iterator(nullptr);
        }

    private:
        NodeF<T>* head;
        int nodes;

    public:
        ForwardList() : List<T>() {
            this->head = nullptr;
            this->nodes = 0;
        }

        ~ForwardList() {
            this->clear();
        }

        T front(){
            return this->head->data;
        }

        T back(){
            NodeF<T>* temp = this->head;
            while(temp->next != nullptr) {
                temp = temp->next;
            }
            return temp->data;
        }

        void push_front(T data){
            NodeF<T>* nodo = new NodeF(data);
            nodo->next = this->head;
            this->head = nodo;
            this->nodes++;
        }

        void push_back(T data){
            NodeF<T>* nodo = new NodeF(data);
            NodeF<T> *temp = this->head;
            if (head != nullptr) {
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = nodo;
            } else {
                this->head = nodo;
            }
            this->nodes++;
        }

        T pop_front(){
            if (this->head == nullptr){
                throw("No se puede eliminar un elemento porque la lisa esta vacia.");
            }
            if (this->head->next == nullptr) {
                NodeF<T>* temp = this->head;
                delete this->head;
                head = nullptr;
                T deleted = temp->data;
                cout << this->head << endl;
                this->nodes--;
                return deleted;
            }
            NodeF<T>* temp = this->head;
            this->head = this->head->next;
            T deleted = temp->data;
            this->nodes--;
            return deleted;
        }

        T pop_back(){
            if (this->head == nullptr){
                throw("No se puede eliminar un elemento porque la lisa esta vacia.");
            }

            NodeF<T>* temp = this->head;
            
            if (this->head->next == nullptr) {
                delete this->head;
                this->head = nullptr;
                T deleted = temp->data;
                this->nodes--;
                return deleted;
            }
            
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            
            T deleted = temp->next->data;
            temp->next = nullptr;
            this->nodes--;
            return deleted;
        }

        void insert(T data, int pos){
            if (pos + 1 > this->size() || pos < 0){
                throw("index out of range");
            }

            NodeF<T>* nodo = new NodeF(data);
            NodeF<T>* temp = this->head;
            for (int i = 0; i < pos-1; i++){
                temp = temp->next;
            }
            nodo->next = temp->next;
            temp->next = nodo; 
            this->nodes++;
        }

        bool remove(int pos){
            if (pos + 1 > this->size() || pos < 0){
                return false;
            }

            if (pos == 0){
                this->pop_front();
            }
            else if (pos == this->size() - 1){
                this->pop_back();
            }
            else{
                NodeF<T>* nodo = head;
                for (int i = 0; i < pos-1; i++)
                    nodo = nodo->next;

                NodeF<T> *temp = nodo->next;
                nodo->next = temp->next;
                delete temp;
            }

            return true;
        }

        T& operator[](int pos){
            if (pos + 1 > this->size() || pos < 0){
                throw("index out of range");
            }

            NodeF<T>* temp = this->head;
            for (int i = 0; i < pos; i++ ) {
                temp = temp->next;
            }
            return temp->data;
        }

        bool is_empty(){
            return this->head==nullptr;
        }

        int size(){
            return this->nodes;
        }

        void clear(){
            while(this->head != nullptr){
                NodeF<T>* temp = head;
                this->head = this->head->next;
                delete temp;
            }
            this->nodes = 0;
        }
        
        void sort(){
            NodeF<T> *remp = head;
            NodeF<T> *temp = nullptr;
            NodeF<T> *temp2 = nullptr;
            T val;
            
                while (remp != nullptr)
                {
                    temp = remp->next;
                    temp2 = remp;

                    while (temp != nullptr)
                    {
                        if (temp2->data > temp->data)
                        {
                            val = temp2->data;
                            temp2->data = temp->data;
                            temp->data = val;
                        }
                        temp = temp->next;
                        temp2 = temp2->next;
                    }
                    remp = remp->next;
                }
            }

        bool is_sorted(){
            if (this->head == nullptr || this->head->next == nullptr) {
                return true;
            }

            bool increasing = true;
            bool decreasing = true;
            NodeF<T>* temp = this->head;
            while (temp->next->next != nullptr){
                if (temp->data < temp->next->data) {
                    decreasing = false;
                }
                if (temp->data > temp->next->data) {
                    increasing = false;
                }
                temp = temp->next;
            }
            return increasing || decreasing;
        }

        void reverse(){
            NodeF<T>* izq = nullptr;
            NodeF<T>* medio = head;
            NodeF<T>* der = nullptr;;

            while(medio != nullptr){
                der = medio->next;
                medio->next = izq;
                izq = medio;
                medio = der;
            }

            head = izq;
        }

        std::string name(){
            return "ForwardList";
        }
};

#endif
