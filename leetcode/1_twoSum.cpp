
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        // first let's special case a check for solution (target = target/2 + target/2)
        if ((target % 2) == 0) {
            int checkNum = target / 2, i=1;
            vector<int> halfValues;
            
            std::for_each (numbers.begin(), numbers.end(), [&halfValues, checkNum, &i] (const int& num) -> void {
                if (num == checkNum) {
                    halfValues.push_back(i); //1-based indexing required
                }
                i++;
            });
            
            if (halfValues.size() >= 2) {
                if (halfValues.size() > 2) {
                    halfValues.erase(halfValues.begin()+2, halfValues.end());    
                }
                return halfValues;
            }
        }
        
        //now my hashtable can check for the case where the sum is not from same numbers
        std::unordered_map<int, int> numberHash; // mapping from number to its index
        std::vector<int> retVal;
        int i = 1;
        for (const int& num : numbers) {
            numberHash[num] = i++;
        }
        
        for (const int& num : numbers) {
            if ((target - num != num) && numberHash.find(target - num) != numberHash.end()) {
                retVal.push_back(numberHash[num]);
                retVal.push_back(numberHash[target-num]);
                return retVal;
            }
        }
        return retVal;
    }
};
