#include <string>
#include "classes/forward.h"
#include "classes/btree.h"
#include "transaction.h"

using namespace std;

class Information {
    ForwardList<Transaction*> info;
    BTree<Transaction*>* btree_info_order_by_date;
    BTree<Transaction*>* btree_info_order_by_amount;
    
    public:
    Information() {
        this->btree_info_order_by_date = new BTree<Transaction*>(
            15,
            [](const Transaction *first, const Transaction *second) { return first->date < second->date; },
            [](const Transaction *first, const Transaction *second) { return second->date < first->date; },
            [](const Transaction *first, const Transaction *second) { return second->date == first->date; }
            );

        this->btree_info_order_by_amount = new BTree<Transaction*>(
            15,
            [](const Transaction *first, const Transaction *second) { return first->monto < second->monto; },
            [](const Transaction *first, const Transaction *second) { return second->monto < first->monto; },
            [](const Transaction *first, const Transaction *second) { return second->monto == first->monto; }
            );
    };

    auto get_btree() {
        return this->btree_info_order_by_date;
    }

    void new_transaction(Transaction* trans) {
        this->info.push_front(trans);
        this->btree_info_order_by_date->insert(trans);
        this->btree_info_order_by_amount->insert(trans);
    }

    Transaction* get_most_recent_transaction() {
        return btree_info_order_by_date->maxKey();
    }

    Transaction* get_biggest_transaction() {
        return btree_info_order_by_amount->maxKey();
    }

    string get_all_info() {
        string result = "";
        int size = this->info.size();

        for (int i = 0; i < size; i++) {
            result += (this->info)[i]->get_info_to_hash();
        }

        return result;
    }

    void replace_index(int index, Transaction* trans) {
        info.remove(index);
        info.insert(trans, index);
    }

    void print_transaction() {
        int size = this->info.size();

        for (int i = 0; i < size; i++) {
            (this->info)[i]->print_transaction();
        }
    }
};