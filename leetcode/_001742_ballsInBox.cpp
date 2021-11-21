class Solution {
    int sumDigits(int n) {
        int sum=0;
        while (n) {
            sum += (n%10);
            n /= 10;
        }
        return sum;
    }
public:
    // O(n) time, O(n) space.
    int countBalls(int lowLimit, int highLimit) {
        unordered_map<int, int> boxes;
        int most_box_index = -1;
        for (int b=lowLimit; b<=highLimit; b++) {
            int label = sumDigits(b);
            boxes[label]++;
            if (boxes[label] > boxes[most_box_index]) {most_box_index = label;}
        }
        return boxes[most_box_index];
    }
};
