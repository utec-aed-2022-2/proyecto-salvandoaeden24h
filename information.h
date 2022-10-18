#include <string>
#include "forward.h"
#include "transaction.h"

using namespace std;

class Information {
    ForwardList<Transaction*> info;

    public:

    Information()=default;

    void new_transaction(Transaction* trans) {
        this->info.push_front(trans);
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