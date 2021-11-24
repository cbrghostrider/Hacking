class Solution {
    unordered_map<int, int> pval;
    int powVal(int val) {
        int pv=0;
        while(val != 1) {
            if (pval.find(val) != pval.end()) {  
                pv += pval[val]; 
                break;
            }
            if ((val & 0x1) == 0) {
                val = val/2;
            } else {
                val = (val*3) + 1;
            }
            pv++;
        }
        pval[val] = pv;
        return pv;
    }
public:
    int getKth(int lo, int hi, int k) {
        pval[1] = 0;
        vector<int> values;
        values.reserve(hi-lo+1);
        for (int i=lo; i<=hi; i++) {values.push_back(i);}
        
        std::sort(values.begin(), values.end(), [this](int left, int right) -> bool {
            int lpval = powVal(left);
            int rpval = powVal(right);
            if (lpval != rpval) return lpval < rpval;
            return left < right;
        });
        
        return values[k-1];
    }
};
