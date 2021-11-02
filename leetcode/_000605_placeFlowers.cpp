class Solution {
    bool canPlant(const vector<int>& flowerbed, int pos) {
        if (flowerbed[pos] != 0) return false;
        bool left_ok = (pos == 0 || flowerbed[pos-1] != 1);
        bool right_ok = (pos == flowerbed.size()-1 || flowerbed[pos+1] != 1);
        return left_ok && right_ok;
    }
    
public:
    
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if (n == 0) return true;
        for (int i=0; i<flowerbed.size(); i++) {
            if (canPlant(flowerbed, i)) {
                flowerbed[i] = 1;
                n--;
                if (n == 0) return true;
            }
        }
        return false;
    }
};
