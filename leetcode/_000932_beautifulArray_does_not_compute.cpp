class Solution {
public:
    
    // THIS SOLUTIONS DOES NOT WORK
    // THIS SOLUTIONS DOES NOT WORK
    // THIS SOLUTIONS DOES NOT WORK
    // THIS SOLUTIONS DOES NOT WORK
    // THIS SOLUTIONS DOES NOT WORK
    // THIS SOLUTIONS DOES NOT WORK
    // THIS SOLUTIONS DOES NOT WORK
    //
    // surprisingly it works for up to n=11 or 12 I think
    // after that it fails
    // it seems like I decide too early what is the current sequence, and later it turns out to be wrong
    // 
    // FIRST PROBLEM I GAVE UP ON!
    // Only including solution for completeness.
    
    vector<int> beautifulArray(int n) {
        vector<int> ans;
        for (int number=1; number<=n; number++) {  // insert each new number into the array
            unordered_set<int> lhs, rhs;
            for (int i=0; i<ans.size(); i++) {
                rhs.insert(ans[i]);
            }
            
            int pos=0;
            for (; pos<ans.size(); pos++) {
                bool violation = false;
                
                // check violation where number is the middle thing
                for (int l_check : lhs) {
                    if (rhs.find(2*number - l_check) != rhs.end()) {  // violation
                        lhs.insert(ans[pos]);
                        rhs.erase(ans[pos]);
                        violation = true;
                        break;
                    }
                }
                
                // check violation where number is not the middle, and both are in left
                unordered_set<int> temp;
                for (int i=0; i<pos; i++) {
                    if (temp.find(2*ans[i]-number) != temp.end()) {
                        lhs.insert(ans[pos]);
                        rhs.erase(ans[pos]);
                        violation = true;
                        break;                     
                    } else {
                        temp.insert(ans[i]);
                    }
                }
                
                
                // check violation where number is not the middle thing, and both are in right
                temp.clear();
                for (int i=ans.size()-1; i>=pos; i--) {
                    if (temp.find(2*ans[i]-number) != temp.end()) {
                        lhs.insert(ans[pos]);
                        rhs.erase(ans[pos]);
                        violation = true;
                        break;
                    } else {
                        temp.insert(ans[i]);
                    }
                }
                if (violation) continue; else break;
            }
            if (pos != ans.size()) ans.insert(begin(ans)+pos, number);
            else ans.push_back(number);
        }
        return ans;
    }
};
