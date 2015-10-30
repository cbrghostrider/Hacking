// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>

using std::string;
using std::pair;
using std::make_pair;
using std::unordered_map;
using std::vector;

typedef long long Val;
typedef int Node;

enum RLECmp {RLELT, RLEEQ, RLEGT};

struct RLEString {
    RLEString() : rle() {}

    void addChar(char ch);
    RLECmp compare(const RLEString& rhs);

    vector<pair<char, int>> rle;
};

void RLEString::addChar(char ch) {
    if (rle.size() == 0) {
        rle.push_back(make_pair(ch, 1));
        return;
    }
    if (rle[0].first == ch) {
        rle[0].second += 1;
        return;
    }
    pair<char, int> fpr = make_pair(ch, 1);
    rle.insert(rle.begin(), fpr);
}

RLECmp RLEString::compare(const RLEString& rhs) {
    if (rle.size() == 0 && rhs.rle.size() == 0) return RLEEQ;
    if (rle.size() == 0) return RLELT; 
    if (rhs.rle.size() == 0) return RLEGT; 

    int myind = 0, rhsind = 0;
    pair<char, int> myrle('a', 0); // = rle[myind++];
    pair<char, int> rhsrle('a', 0); // = rhs.rle[rhsind++];

    while ((myind < rle.size() || myrle.second > 0) && (rhsind < rhs.rle.size() || rhsrle.second > 0)) {
        if (myrle.second == 0) { myrle = rle[myind++]; }
        if (rhsrle.second == 0) {rhsrle = rhs.rle[rhsind++];} 

        if (myrle.first > rhsrle.first) { return RLEGT; }
        if (myrle.first < rhsrle.first) { return RLELT; }

        int limit = std::min(myrle.second, rhsrle.second);
        myrle.second -= limit;
        rhsrle.second -= limit;
    }

    if (myind == rle.size() && rhsind == rhs.rle.size()) {
        if (myrle.second == 0 && rhsrle.second == 0) return RLEEQ;
        if (myrle.second == 0) return RLELT;
        if (rhsrle.second == 0) return RLEGT;
    }
    if (myind == rle.size()) return RLELT; 
    if (rhsind == rhs.rle.size()) return RLEGT; 
    return RLEEQ;
}

// for node x, w/ parent node y,
// the lexicographically biggest path is (endnode, stringval)
struct CacheElem {
    Node endnode;
    RLEString sval;
    CacheElem(Node en=0) : endnode(en), sval() {}
};

typedef unordered_map<Node, char> Bucket;
typedef vector<Bucket> AdjList;
typedef unordered_map<Val, CacheElem> MemoCache;

class ATree {
public:
    ATree(int n);
    void computeCache();
private:
    inline Val makeKey(Node me, Node parent);
    CacheElem& computeMax(Node me, Node parent);

    const int N;
    AdjList adjlist;
    MemoCache mcache;
};

inline Val ATree::makeKey(Node me, Node parent) {
    return ((((Val)(parent)) << 32 ) | ((Val)(me))) ;
}

ATree::ATree(int n)
: N(n),
  adjlist(N, Bucket()),
  mcache() {
    for (int i=0; i<N-1; i++) {
        Node n1, n2; std::cin >> n1 >> n2;
        n1 -= 1; n2 -= 1; //0-indexed
        char ch; std::cin >> ch;

        adjlist[n1].insert(make_pair(n2, ch));
        adjlist[n2].insert(make_pair(n1, ch));
    }
}

CacheElem& ATree::computeMax(Node me, Node parent) {
    Val key = makeKey(me, parent);
    auto cit = mcache.find(key);
    if (cit != mcache.end()) {
        return cit->second;
    }
    CacheElem ret;

    if (parent != -1 && adjlist[me].size() == 1) {
        ret.endnode = me;
        mcache.insert(make_pair(key, ret));
        return mcache[key];
    }

    vector<Node> cands;
    char chhi = 'a';

    for (pair<Node, char> nchp : adjlist[me]) {
        Node neigh = nchp.first;
        char ech   = nchp.second;
        if (neigh == parent) continue;
        if (ech > chhi) {
            chhi = ech;
            cands.clear();
            cands.push_back(neigh);
        } else if (ech == chhi) {
            cands.push_back(neigh);
        }
    }

    for (Node neigh : cands) {
        const CacheElem& ce = computeMax(neigh, me);
        int cmpresult = ret.sval.compare(ce.sval);
        if (cmpresult == RLELT || (cmpresult == RLEEQ && ret.endnode < ce.endnode)) {
            ret.sval = ce.sval;
            ret.endnode = ce.endnode;
        }
    }

    ret.sval.addChar(chhi);

    mcache.insert(make_pair(key, ret));
    return mcache[key];
}

void ATree::computeCache() {
    for (int n=0; n<N; n++) {
        CacheElem& ce = computeMax(n, -1);
        Node me = n + 1;
        Node end = ce.endnode + 1;
        std::cout << end << " "; 
    }
    std::cout << std::endl;
}

int main() {
    int n; std::cin >> n;
    ATree at(n);
    at.computeCache();
}
