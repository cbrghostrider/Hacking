// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Time complexity O(nlogn)
// Space complexity O(n)
// 
// Here is my writeup from leetcode
//
// This solution assumes you have implemented a QuickUnion union-find DS class, with logn complexity for Union operation.
//
// Initially, enter all n indices into union-find, each with their own id.
// Then create pairs of (height, index) for each histogram, put them into a vector, and sort the vector on height of histograms. 
//     We will use this vector as a stack (popping from highest height histograms).
// while stack not empty {
//     hist = element at the top, pop it
//     if this hist's left and/or right neighbor have height GREATER than this hist, then union with their sets. 
//       (This lets me know how many neighbors are to my left and right that have height >= mine. 
//       This is because of the order we pop from the stack, from largest to smallest).
//     Find the size of my cluster, from Union-Find DS.
//     candidate for max area is (sz of cluster)*(my height)
//     if this candidate is greater than previously recorded max area, update max area.
// }
// And that's it, just return max area at the end. Here is the code:
class QuickUnion {
public:
    ~QuickUnion() {}
    QuickUnion(const int numKeys);           //adds each key into its own set
    void Union(const int k1, const int k2);  //unions two sets
    int Find(const int k) const;             //finds what set is this key
    int NumSets() const;                     //returns number of sets in DS
    int SizeSet(int nd) const;               //returns size of set in cluster of nd
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

int QuickUnion::SizeSet(int nd) const 
{
    int ndp = Root_(nd);
    return (sz_[ndp]);
}

class Solution {
    class Hist {
    public:
        int ht;
        int index;
        Hist(int h, int i) : ht(h), index(i) {}
    };

public:
    int largestRectangleArea(vector<int>& height) {
        if (height.size() == 0) return 0;

        vector<Hist> histograms;
        for (int i=0; i<height.size(); i++) {
            histograms.push_back(Hist(height[i], i));
        }

        std::sort(histograms.begin(), histograms.end(), [] (const Hist& lhs, const Hist& rhs) -> bool {
            return (lhs.ht < rhs.ht);
        });

        int max=0;
        QuickUnion uf(histograms.size());
        while (!histograms.empty()) {
            Hist hist = histograms.back(); histograms.pop_back();
            if (hist.index != 0 && hist.ht <= height[hist.index-1]) { //left neighbor
                uf.Union(hist.index, hist.index-1);
            }
            if (hist.index != height.size()-1 && hist.ht <= height[hist.index+1]) { //right neighbor
                uf.Union(hist.index, hist.index+1);
            }
            int clusterSz = uf.SizeSet(hist.index);
            if (max < (clusterSz * hist.ht)) {
                max = clusterSz * hist.ht;
            }
        }
        return max;
    }
};
