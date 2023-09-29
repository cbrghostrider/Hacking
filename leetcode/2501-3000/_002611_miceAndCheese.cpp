class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        vector<int> indices;
        for (int i=0; i<reward1.size(); i++) {
            indices.push_back(i);
        }
        std::sort(indices.begin(), indices.end(), [&reward1, &reward2](const int& left, const int& right) -> bool {
            int diff_left = reward1[left] - reward2[left];
            int diff_right = reward1[right] - reward2[right];
            if (diff_left == diff_right) return false;
            return diff_left > diff_right;
        });
        int sum=0;
        for (int i=0; i<k; i++)              { sum += reward1[indices[i]];}
        for (int i=k; i<indices.size(); i++) { sum += reward2[indices[i]];}
        return sum;
    }
};
