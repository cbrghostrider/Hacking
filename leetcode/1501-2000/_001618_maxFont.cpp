/**
 * // This is the FontInfo's API interface.
 * // You should not implement it, or speculate about its implementation
 * class FontInfo {
 *   public:
 *     // Return the width of char ch when fontSize is used.
 *     int getWidth(int fontSize, char ch);
 *     
 *     // Return Height of any char when fontSize is used.
 *     int getHeight(int fontSize)
 * };
 */
class Solution {
    FontInfo* finfo=nullptr;
    int W, H;
    string text;
    vector<int> fonts;
    
    bool possible(int fsize) {
        if (finfo->getHeight(fsize) > H) return false;
        int total=0;
        for (char ch : text) {
            total += finfo->getWidth(fsize, ch);
            if (total > W) return false;
        }
        return true;
    }
    
    // lo and hi and return val are indices within fonts.
    int binSearch(int lo, int hi) {
        if (lo == hi) return lo;
        if (lo + 1 == hi) {
            if (possible(fonts[hi])) return hi;
            return lo;
        }
        int mid = (lo+hi)/2;
        bool check = possible(fonts[mid]);
        if (check) {
            return binSearch(mid, hi);
        }
        return binSearch(lo, mid);
    }
    
public:
    // O(k log n) time; k = |text|, n = |fonts|.
    // O(log n) space for the binary search recursion.
    int maxFont(string t, int w, int h, vector<int>& fs, FontInfo fontInfo) {
        text = t;
        W=w; H=h;
        fonts = fs;
        finfo = &fontInfo;
        
        if (!possible(fonts[0])) return -1;  // even the smallest doesn't work.
        if (possible(fonts.back())) return fonts.back();
        int index = binSearch(0, fonts.size()-1);
        return fonts[index];
    }
};
