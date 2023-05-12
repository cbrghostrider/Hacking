class Solution {
    struct Info {
        bool from_a=false;
        bool from_b=false;
    };
    unordered_map<int, Info> htable;
    bool both_marked(int elem) {
        return htable[elem].from_a && htable[elem].from_b;
    }
    void mark_a(int elem) { htable[elem].from_a = true; }
    void mark_b(int elem) { htable[elem].from_b = true; }

public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int count=0;
        vector<int> C;
        for (int i=0; i<A.size(); i++) {
            if (A[i] == B[i]) {                
                if (both_marked(A[i])) {
                    // already counted.
                    C.push_back(count);
                    continue;
                }
                mark_a(A[i]);
                mark_b(B[i]);                
                count++;
                C.push_back(count);
                continue;
            }            
            if (!both_marked(A[i])) {
                mark_a(A[i]);
                if (both_marked(A[i])) {count++;}
            }
            if (!both_marked(B[i])) {
                mark_b(B[i]);
                if (both_marked(B[i])) {count++;}
            }
            C.push_back(count);
        }
        return C;
    }
};
