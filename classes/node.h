#ifndef NODE_H
#define NODE_H
#include <functional>

using namespace std;

template <typename TK>
struct Node
{
    // Numero M
    int M;
    // array de keyss
    TK *keys;
    // array de punteros a hijos
    Node **children;
    // cantidad de keyss
    int count;
    // indicador de nodo hoja
    bool leaf;

        std::function<bool(const TK &, const TK &)> less;
        std::function<bool(const TK &, const TK &)> greater;
        std::function<bool(const TK &, const TK &)> equal; 

    Node(
        std::function<bool(const TK &, const TK &)> _less,
    	std::function<bool(const TK &, const TK &)> _greater,
		std::function<bool(const TK &, const TK &)> _equal
    ) : keys(nullptr), children(nullptr), count(0), less(_less), greater(_greater), equal(_equal) {}
    Node(
        int M_, bool leaf_,
        std::function<bool(const TK &, const TK &)> _less,
    	std::function<bool(const TK &, const TK &)> _greater,
		std::function<bool(const TK &, const TK &)> _equal
    ) {
        this->less = _less;
    	this->greater = _greater;
    	this->equal = _equal;
        this->M = M_;
        this->keys = new TK[M_ - 1];
        this->children = new Node<TK> *[M_];
        this->count = 0;
        this->leaf = leaf_;
    }

  void killSelf()
  {
    for (int i = 0; i < count; i++)
    {
      if (leaf != true)
      {
        children[i]->killSelf();
      }
    }

    delete[] keys;
    delete[] children;
    delete this;
  }

  void SplitChild(Node<TK> *node)
  {
    Node<TK> *rightNode = new Node<TK>(M, true, less, greater, equal);

    auto ins_arriba = node->keys[(M - 1) / 2];

    for (int i = ((M - 1) / 2) + 1; i < M; i++)
    {
      rightNode->keys[rightNode->count] = node->keys[i];

      (node->count)--;
      (rightNode->count)++;
    }

    if (node->leaf == false)
    {
      int rgh_child = 0;
      for (int i = ceil(float(M) / 2); i <= M; i++)
      {
        rightNode->children[rgh_child] = node->children[i];
        rgh_child++;
      }
      rightNode->leaf = node->leaf;
    }

    int temp = count;
    while (children[temp] != node)
    {
      children[temp + 1] = children[temp];
      temp--;
    }
    children[temp + 1] = rightNode;

    int cont = count;

    while (cont > 0 && greater(keys[cont - 1], ins_arriba)) {
        keys[cont] = keys[cont - 1];
        cont--;
    }

    keys[cont] = ins_arriba;
    count++;
    (node->count)--;
  }

    Node<TK> *insert(TK data, Node<TK> *node_arr, Node<TK> *root) {
        if (!leaf) {
            int cont = 0;
            while (cont < count && greater(data, keys[cont])) {
                cont++;
            }
            children[cont]->insert(data, this, root);
        } else {
            int cont = count;
            while (cont > 0 && greater(keys[cont - 1], data)) {
                keys[cont] = keys[cont - 1];
                cont--;
            }
            keys[cont] = data;
            count++;
        }

        if (count == M) {
            if (this == root) {
                Node<TK> *node = new Node<TK>(M, false, less, greater, equal);
                node->children[0] = this;
                node->SplitChild(this);
                return node;
            } else {
                node_arr->SplitChild(this);
            }
        }
        return root;
    }
};

#endif