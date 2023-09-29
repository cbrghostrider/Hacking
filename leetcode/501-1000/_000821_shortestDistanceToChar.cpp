class Solution {
public:
    // O(n) time
    vector<int> shortestToChar(string s, char c) {
        vector<int> dist(s.size(), std::numeric_limits<int>::max());
        
        int last = std::numeric_limits<int>::max();
        for (int i=0; i<s.size(); i++) {
            if (s[i] == c){
                last = i;
                dist[i] = 0;
                continue;
            } else if (last == std::numeric_limits<int>::max()) {
                dist[i] = std::numeric_limits<int>::max();
            } else {
                dist[i] = i - last;
            }
        }
        
        last = std::numeric_limits<int>::max();
        for (int i=s.size()-1; i>=0; i--) {
            if (s[i] == c) {
                last = i;
                continue;
            } else if ((last - i) < dist[i]) {
                dist[i] = last - i;
            }
        }
        return dist;
    }
};
