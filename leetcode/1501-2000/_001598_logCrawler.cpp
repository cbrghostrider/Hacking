class Solution {
public:
    // O(n) time, O(1) space.
    int minOperations(vector<string>& logs) {
        int count=0;
        for (string log : logs) {
            if (log == "../") {
                if (count!=0) count--;
            } else if (log == "./") {
                ;
            } else {
                count++;
            }
        }
        return count;
    }
};
