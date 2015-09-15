// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

////////////////////////////////////////////////////////////////////////////
//			Union-Find Data Structure
////////////////////////////////////////////////////////////////////////////

class QuickUnion {
public:
    ~QuickUnion() {}
    QuickUnion(const int numKeys);           //adds each key into its own set
    void Union(const int k1, const int k2);  //unions two sets
    int Find(const int k) const;             //finds what set is this key
    int NumSets() const;                     //returns number of sets in DS
private:
    int Root_(int index) const;
    vector<int> arr_;     //each key associated with its set here
    vector<int> sz_;      //size of each tree rooted here
};

QuickUnion::QuickUnion(const int numKeys) 
: arr_(), sz_()
{
    for (int i=0; i<numKeys; i++) {
        arr_.push_back(i);
        sz_.push_back(1); 
    }
}

int QuickUnion::Root_(int index) const
{
    while (index != arr_[index]) {
        index = arr_[index];
    }
    return index;
}

void QuickUnion::Union(const int kf, const int kt)
{
    int from = Root_(kf);
    int to   = Root_(kt);
    if (from == to) return;
    if (sz_[from] < sz_[to]) {
        arr_[from] = to;
        sz_[to] += sz_[from];
    } else {
        arr_[to] = from;
        sz_[from] += sz_[to];
    }
}

int QuickUnion::Find(const int k) const
{
    return Root_(k);
}

int QuickUnion::NumSets() const
{
    vector<int> examine;
    for (int i=0; i<arr_.size(); i++) {
        examine.push_back(Root_(i));
    }
    
    std::sort(examine.begin(), examine.end());
    auto newend = std::unique(examine.begin(), examine.end());
    int ctr=0;
    for (auto it=examine.begin(); it != newend; it++) {
        ctr++;
    }
    return ctr;
}

int main() {
    int TC; std::cin >> TC;
    for (int t=0; t<TC; t++) {
        int N; std::cin >> N;
        
        QuickUnion uf(N);
        
        for (int c=0; c<N; c++) {
            int bt; std::cin >> bt; 
            bt -= 1; // make 0-indexed
            uf.Union(c, bt);
        }
        std::cout << (uf.NumSets() - 1) << std::endl;
    }
}

