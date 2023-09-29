class Solution {
public:
    // Make two halves.
    // If mid is greater than target, look in left half.
    // If mid is less than or equal to target, look in right half.
    // left and right are both inclusive.
    char findNeedle(const vector<char>& letters, int left, int right, char target) {
        if (left == right) {
            return letters[left];
        }
        if (left + 1 == right) {
            if (letters[left] > target) {
                return letters[left];
            }
            return letters[right];
        }
        
        int mid = ((long long)left + right)/2;
        if (letters[mid] > target) {
            return findNeedle(letters, left, mid, target);
        }
        return findNeedle(letters, mid, right, target);
    }
    
    char nextGreatestLetter(vector<char>& letters, char target) {
        char needle = findNeedle(letters, 0, letters.size() - 1, target);
        
        // wrap around case
        if (needle == letters[letters.size() - 1] && needle <= target) {
            return letters[0];
        }
        return needle;
    }
};
