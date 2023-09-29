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
    int countLargestGroup(int n) {
        unordered_map<int, int> groups;
        int max_size = 0;
        for (int i=1; i<=n; i++) {
            int sum = sumDigits(i);
            groups[sum]++;
            if (groups[sum] > max_size) {max_size = groups[sum];}
        }
        int count=0;
        for (const auto& kv : groups) {
            if (kv.second == max_size) count++;
        }
        return count;
    }
};
