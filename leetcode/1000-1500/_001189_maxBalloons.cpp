class Solution {
public:
    int maxNumberOfBalloons(string text) {
        unordered_map<char, int> freqs;
        for (char ch : text) {freqs[ch]++;}
        string balloon = "balloon";
        int min = std::numeric_limits<int>::max();
        freqs['l'] /= 2;
        freqs['o'] /= 2;
        for (char ch : balloon) {
            if (freqs[ch] < min) {min = freqs[ch];}
        }
        return min;
    }
};
