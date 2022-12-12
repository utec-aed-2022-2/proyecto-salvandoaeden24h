#include <string>
#include "classes/forward.h"
#include "classes/btree.h"
#include "classes/avl.h"
#include "transaction.h"
#include "classes/chainhash.h"

using namespace std;

class Information {
    ForwardList<Transaction*> info;
    BTree<Transaction*>* btree_info_order_by_date;
    BTree<Transaction*>* btree_info_order_by_amount;
    AVLTree<Transaction*>* avl_order_by_date;
    AVLTree<Transaction*>* avl_order_by_monto;
    ChainHash<string, double, long long int>* chain_hash_name;
    
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

        this->avl_order_by_date = new AVLTree<Transaction*>(
            [](const Transaction *first, long double second) { return first->date < second; },
            [](const Transaction *first, long double second) { return second < first->date; },
            [](const Transaction *first, long double second) { return second == first->date; },
            [](const Transaction *first, const Transaction *second) { return first->date < second->date; },
            [](const Transaction *first, const Transaction *second) { return second->date < first->date; },
            [](const Transaction *first, const Transaction *second) { return second->date == first->date; }
            );
        this->avl_order_by_monto = new AVLTree<Transaction*>(
            [](const Transaction *first, long double second) { return first->monto < second; },
            [](const Transaction *first, long double second) { return second < first->monto; },
            [](const Transaction *first, long double second) { return second == first->monto; },
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
        this->avl_order_by_date->insert(trans);
        this->avl_order_by_monto->insert(trans);
        this->chain_hash_name->insert(trans->emisor, trans->receptor, trans->monto, trans->date);
    }

    Transaction* get_most_recent_transaction() {
        return btree_info_order_by_date->maxKey();
    }

    Transaction* get_biggest_transaction() {
        return btree_info_order_by_amount->maxKey();
    }

    vector<Transaction*> get_range_search_date(long int start, long int end) {
        vector<Transaction*> vec;
        this->avl_order_by_date->range_search(start, end, vec);
        return vec;
    }

    vector<Transaction*> get_range_search_monto(long double start, long double end) {
        vector<Transaction*> vec;
        this->avl_order_by_monto->range_search(start, end, vec);
        return vec;
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

    vector<Transaction*> get_transactions_emisor(string name) {
        return this->chain_hash_name->get(name);
    }
};