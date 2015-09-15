// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <limits>

using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::make_pair;
using std::pair;

typedef unsigned int Node;
typedef unsigned long long Key;
typedef long long Token;
typedef unordered_set<Node> Bucket;
typedef vector<Bucket> AdjList;

class TreeGame {
public:
    TreeGame(int n);
    Token playGame();
private:
    void readInput();
    Token subtreeSize(Node stroot, Node parent);
    inline Key makeKey(Node stroot, Node parent);

    const int N;
    vector<Token> ns;
    Token TOTAL;
    AdjList adjList;
    unordered_map<Key, Token> cache;
};

TreeGame::TreeGame(int n)
: N(n), ns(N, 0), TOTAL(0), adjList(N, Bucket()), cache() {
    readInput();
}

inline Key TreeGame::makeKey(Node stroot, Node parent) {
    return ((((Key)stroot) << 32) | ((Key)parent));
}

void TreeGame::readInput() {
    for (int i=0; i<N; i++) {
        std::cin >> ns[i];
        TOTAL += ns[i];
    }
    for (int i=0; i<N-1; i++) { //read edges
        Node n1, n2; std::cin >> n1 >> n2;
        n1 -=1 ;  n2 -= 1; //make 0-indexed
        adjList[n1].insert(n2);
        adjList[n2].insert(n1);
    }
}

Token TreeGame::subtreeSize(Node stroot, Node parent) {
    Key cacheKey = makeKey(stroot, parent);
    auto cit = cache.find(cacheKey);

    //check memoization cache
    if (cit != cache.end()) { return cit->second; }

    //compute subtree size, rooted at stroot, and having parent as parent
    Token token = ns[stroot];
    for (const Node& neigh : adjList[stroot]) {
        if (neigh == parent) continue;
        Token nsize = subtreeSize(neigh, stroot);
        token += nsize;
    }

    //insert into memoization cache
    cache.insert(make_pair(cacheKey, token));
    return token;
}

Token TreeGame::playGame() {
    //when finally computed, minimax will be my opponents score, 
    //when both of us have played optimally
    Token minimax = std::numeric_limits<Token>::max();

    for (int node=0; node<N; node++) { //this is the root
        //max of node's subtrees
        Token max = std::numeric_limits<Token>::min();

        for (const Node& neigh : adjList[node]) {
            Token nsize = subtreeSize(neigh, node);
            if (nsize > max) { max = nsize; }
        }

        if (max < minimax) {
            minimax = max;
        }
    }

    return (TOTAL - minimax);
}

int main() {
    int n; std::cin >> n;
    TreeGame tg(n);
    Token ans = tg.playGame();
    std::cout << ans << std::endl;
}

