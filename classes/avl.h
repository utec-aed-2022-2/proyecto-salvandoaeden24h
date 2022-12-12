#ifndef AVLTree_H
#define AVLTree_H
#include <string>
#include <iomanip>
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

template <typename T>
struct NodeBT {
    T data;
    int height;
    NodeBT* left; 
    NodeBT* right;
    NodeBT() : left(nullptr), right(nullptr), height(0) {}   
    NodeBT(T value) : data(value), left(nullptr), right(nullptr), height(0) {}

    void killSelf(){
        if(left != nullptr) left->killSelf();
        if(right != nullptr) right->killSelf();
        delete this;
    }
};

template <typename T>
class AVLTree {
  private:
    NodeBT<T> *root;
    std::function<bool(const T &, long double)> less;
    std::function<bool(const T &, long double)> greater;
    std::function<bool(const T &, long double)> equal; 
    std::function<bool(const T &, const T &)> less_classes;
	std::function<bool(const T &, const T &)> greater_classes;
	std::function<bool(const T &, const T &)> equal_classes;

  public:
    AVLTree(
        std::function<bool(const T &, long double)> _less,
    	std::function<bool(const T &, long double)> _greater,
		std::function<bool(const T &, long double)> _equal,
        std::function<bool(const T &, const T &)> _less_classes,
    	std::function<bool(const T &, const T &)> _greater_classes,
		std::function<bool(const T &, const T &)> _equal_classes
    ) : root(nullptr), less(_less), greater(_greater), equal(_equal),
    less_classes(_less_classes), greater_classes(_greater_classes), equal_classes(_equal_classes) {}

    void insert(T value) {
        insert(this->root, value);
    }

    bool find(T value) {
        return find(this->root, value);
    }

    string getPreOrder() {
        return getPreOrder(this->root);
    }

    int height() {
        return height(this->root);
    }

    T minValue() {
        return minValue(this->root);
    }

    T maxValue() {
        return maxValue(this->root);
    }

    bool isBalanced() {
        return isBalanced(this->root);
    }

    int size() {
        return size(this->root);
    }

    void remove(T value) {
        remove(this->root, value);
    }

    void range_search(long double start, long double end, vector<T> &vec) {
        range_search(this->root, start, end, vec);
    }

    void displayPretty() {
        displayPretty("", this->root, false);
    }

    ~AVLTree() {
        if (this->root != nullptr) {
            this->root->killSelf();
        }
    }

  private:
    string getPreOrder(NodeBT<T> *node){
        string preorder = "";
        displayPreOrder(node,preorder);
        return preorder;
    }

    void displayPreOrder(NodeBT<T> *node, string &temp) {
        if (node == nullptr)
            return;
        temp = temp + std::to_string(node->data) + " ";
        displayPreOrder(node->left, temp);
        displayPreOrder(node->right, temp);
    }

    void insert(NodeBT<T> *&node, T value) {
        if (node == nullptr)
            node = new NodeBT<T>(value);
        else if (less_classes(value, node->data))
            insert(node->left, value);
        else
            insert(node->right, value);

        updateHeight(node);
        balance(node);
    }

    bool find(NodeBT<T> *node, T value) {
        if (node == nullptr)
            return false;
        else if (less_classes(value, node->data))
            return find(node->left, value);
        else if (greater_classes(value, node->data))
            return find(node->right, value);
        else
            return true;
    }

    int height(NodeBT<T> *node) {
        if (node == nullptr)
            return -1;
        else
            return max(height(node->left), height(node->right)) + 1;
    }

    bool isBalanced(NodeBT<T> *node) {
        if (node == nullptr || (balancingFactor(node) >= -1 && balancingFactor(node) <= 1)) {
           return true;
        }
        return false;
    }

    T minValue(NodeBT<T> *node) {
        if (node == nullptr)
            throw("The tree is empty");
        else if (node->left == nullptr)
            return node->data;
        else
            return minValue(node->left);
    }

    T maxValue(NodeBT<T> *node) {
        if (node == nullptr)
            throw("The tree is empty");
        else if (node->right == nullptr)
            return node->data;
        else
            return maxValue(node->right);
    }

    int size(NodeBT<T> *node) {
        if (node == nullptr)
            return 0;
        else
            return 1 + size(node->left) + size(node->right);
    }


    void remove(NodeBT<T> *&node, T value){
         if (node == nullptr)
            return;
         else if (less(value, node->data))
            remove(node->left, value);
         else if (greater(value, node->data))
            remove(node->right, value);
         else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node; // free
                node = nullptr;
            } else if (node->left == nullptr) {
                NodeBT<T> *temp = node;
                node = node->right;
                delete temp;
            }

            else if (node->right == nullptr) {
                NodeBT<T> *temp = node;
                node = node->left;
                delete temp;
            } else {
                T temp = maxValue(node->left);
                node->data = temp;
                remove(node->left, temp);
            }
        }

        if (node != nullptr) {
            updateHeight(node);
            balance(node);
        }
    }

    void displayPretty(const std::string &prefix, const NodeBT<T> *node, bool isLeft) {
         // Referencia: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c

        if (node != nullptr) {
            cout << prefix;
            if (isLeft) {
                cout << "├──";
            }
            else {
                cout << "└──";
            }

            cout << node->data << std::endl;

            if (isLeft){
                displayPretty(prefix + "│   ", node->left, true);
                displayPretty(prefix + "│   ", node->right, false);
            }
            else{
                displayPretty(prefix + "    ", node->left, true);
                displayPretty(prefix + "    ", node->right, false);
            }
        }
    }

    void range_search(NodeBT<T> *root, long double start, long double end, vector<T> &vec){
        if (root == nullptr) {
            return;
        }

        if (greater(root->data, start)) {
            range_search(root->left,start,end,vec);
        }

        if ((greater(root->data, start) || equal(root->data, start)) && (less(root->data, end) || equal(root->data, end))) {
            vec.push_back(root->data);
        }

        if (less(root->data, end)) {
            range_search(root->right,start,end,vec);
        }
    }

    /*add for avl*/
    int balancingFactor(NodeBT<T> *node){
        return height(node->left) - height(node->right);
    }

    void updateHeight(NodeBT<T> *node){
        if (node == nullptr){
            return;
        }

        node->height = max(height(node->left),height(node->right)) + 1;
    }

    void balance(NodeBT<T> *&node){

        int fb = balancingFactor(node);

        if (fb >= 2){
            if (balancingFactor(node->left) <= -1){
                left_rota(node->left);
            }
            right_rota(node);
        }

        if (fb <= -2){
            if (balancingFactor(node->right) >= 1){
                right_rota(node->right);
            }
            left_rota(node);
        }

    }
    void left_rota(NodeBT<T> *&node){
        NodeBT<T> *temp = node->right;
        node->right = temp->left;
        temp->left = node;

        updateHeight(temp);
        updateHeight(node);

        node = temp;


    }
    void right_rota(NodeBT<T> *&node){
        NodeBT<T> *temp = node->left;
        node->left = temp->right;
        temp->right = node;

        updateHeight(temp);
        updateHeight(node);

        node = temp;
    }
};

#endif