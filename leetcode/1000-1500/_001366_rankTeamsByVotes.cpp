class Solution {
    unordered_map<char, vector<int>> ranks;
    
    void initialize() {
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            ranks[ch] = vector<int>(26, 0);
        }
    }
    
    void accumulate(const string& vote) {
        for (int i=0; i<vote.size(); i++) {
            char ch = vote[i];
            ranks[ch][i]++;
        }
    }
public:
    // O(1) space, because ranks can only have up to 26 keys, and each key only has a vector of size 26 as value.
    // O(n) time, which is the amount of time needed to go through the votes vector.
    string rankTeams(vector<string>& votes) {
        initialize();
        for (const string& vote : votes) {
            accumulate(vote);
        }
        string ans = votes[0];
        int size=votes[0].size();
        std::sort(ans.begin(), ans.end(), [this, size](char lhs, char rhs) -> bool {
            for (int i=0; i<size; i++) {
                if (ranks[lhs][i] != ranks[rhs][i]) return ranks[lhs][i] > ranks[rhs][i];
            }
            return lhs < rhs;
        });
        return ans;
    }
};
