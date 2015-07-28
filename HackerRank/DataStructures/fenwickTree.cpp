// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <limits>

using std::vector;

typedef long long Elem;

template <typename T>
struct MaxVal {
    T operator() (const T& lhs, const T& rhs) {
        return (lhs > rhs ? lhs : rhs);
    }
};

//binary indexed tree
template <typename T>
class BIT {
public:
    typedef std::function<T (const T&, const T&)> BinOp;
    BIT(int size, BinOp oper);
    T read(int index);
    void update(int index, const T& val);
private:
    void readInput();
    BinOp binop;
    vector<T> tree;
};

template<typename T>
BIT<T>::BIT(int size, BinOp oper)
: tree(size+1, T()), binop(oper) {
    readInput();
}

template<typename T>
void BIT<T>::readInput() {
    int n = tree.size()-1;
    for (int i=0; i<n; i++) {
        T val; std::cin >> val;
        update(i, val);
    }
}

template<typename T>
T BIT<T>::read(int index) {
    T acc = T();
    index += 1;
    if (index >= tree.size()) {
        return acc;
    }

    while (index > 0) {
        acc = binop(acc, tree[index]);
        index -= (index & -index);
    }
    return acc;
}

template<typename T>
void BIT<T>::update(int index, const T& val) {
    index += 1;
    if (index >= tree.size()) {
        return;
    }

    while (index < tree.size()) {
        tree[index] = binop(val, tree[index]);
        index += (index & -index);
    }
    return;
}

int main() {
    const int size = 10;
    BIT<Elem> bit(size, std::plus<Elem>());
    for (int i=0; i<size; i++) {
        std::cout << bit.read(i) << std::endl;
    }
}


