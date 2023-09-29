class Solution {
    // get smallest INDEX that has value >= val
    int binSearchLeftBoundary(const vector<int>& citations, int val, int lo, int hi) {
        if (lo == hi) return lo;
        int mid=(lo+hi)/2;
        if (citations[mid] >= val) return binSearchLeftBoundary(citations, val, lo, mid);
        return binSearchLeftBoundary(citations, val, mid+1, hi);
    }
    
    // does guess of h satisfy h-index?
    // returns the difference of papers with at least h citations and h
    // if the difference is > 0, it means we need to focus our search on a bigger h
    int guess(const vector<int>& citations, int h) {
        int k = binSearchLeftBoundary(citations, h, 0, citations.size()-1);
        int papers_with_at_least_h_cits = citations.size() - k;
        return (papers_with_at_least_h_cits - h);
    }
    
    int search(const vector<int>& citations, int h_lo, int h_hi) {
        if (h_lo == h_hi) return h_lo;
        if (h_lo + 1 == h_hi) {
            if (guess(citations, h_hi) >= 0) return h_hi;
            return h_lo;
        }
        int h_mid = (h_lo+h_hi)/2;
        if (guess(citations, h_mid) >= 0) {
            return search(citations, h_mid, h_hi);
        }
        return search(citations, h_lo, h_mid);
    }
public:
    int hIndex(vector<int>& citations) {
        if (citations.empty()) return 0;
        if (citations.size() == 1) {
            return citations[0] >= 1 ? 1 : 0;
        }
        // upper bound for h is citations.back()
        // lower bound for h is 1? or 0?
        int h = search(citations, 1, citations.back());
        return h;
    }
};
