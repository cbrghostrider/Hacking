class Solution {
public:
    int countGoodRectangles(vector<vector<int>>& rectangles) {
        int max_side = 0;
        for_each(rectangles.begin(), rectangles.end(), [&max_side](const vector<int>& rect) {
            int len = std::min(rect[0], rect[1]);
            if (len > max_side) max_side = len;
        });
        int count = 0;
        for_each(rectangles.begin(), rectangles.end(), [&count, max_side](const vector<int>& rect){
            int len = std::min(rect[0], rect[1]);
            if (len == max_side) count++;
        });
        return count;
    }
};
