class Solution {
public:
    vector<string> generatePossibleNextMoves(string currentState) {
        if (currentState.size() <= 1) return {};
        vector<string> ans;
        for (int i=1; i<currentState.size(); i++) {
            if (currentState[i] == currentState[i-1] && currentState[i] == '+') {
                string state = currentState;
                state[i] = state[i-1] = '-';
                ans.push_back(state);
            }
        }
        return ans;
    }
};
