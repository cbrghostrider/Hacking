class Solution {
public:
    // Two possible cases exist:
    // 1. let c be the max char letter
    //   c --------> c ---------> c ---------> c and we fit the other letters in between (with gaps left over)
    // 2. There are no gaps, so we just make additional space for the other letters in between the c's
    // 
    // Case 2 is easy, just k2 = sum(freqs) is the answer.
    // For case 1, we need to know if there's "overflow" past the last max, because other chars have the same freq of occurrence
    // k1 = (max-1) * n + max + overflow is the answer
    // where overflow = max_count + 1
    //
    // O(n) time, O(1) space.
    int leastInterval(vector<char>& tasks, int n) {
        int total=0, max=0;
        vector<int> freqs(26, 0);
        for (char ch : tasks) {
            freqs[ch - 'A']++;
            total++;
            if (freqs[ch - 'A'] > max) {max = freqs[ch - 'A'];}
        }
        int max_count=0;  // how many letters occur max times
        for (int i=0; i<26; i++) {
            if (freqs[i] == max) {max_count++;}
        }
        int k1 = (max-1)*n+ max + (max_count-1);
        int k2 = total;
        return std::max(k1, k2);
    }
};
