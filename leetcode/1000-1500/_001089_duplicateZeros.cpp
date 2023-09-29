class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int zeros = 0;
        for (int n : arr) {if (n == 0) zeros++;}
        
        int write_ptr = arr.size()-1 + zeros;
        for (int read_ptr = arr.size()-1; read_ptr>=0; read_ptr--) {
            if (arr[read_ptr] == 0) {
                if (write_ptr >= arr.size()) { write_ptr--;} else {arr[write_ptr--] = 0;}
                if (write_ptr >= arr.size()) { write_ptr--;} else {arr[write_ptr--] = 0;}
            } else {
                if (write_ptr >= arr.size()) { write_ptr--; } else { arr[write_ptr--] = arr[read_ptr];}
            }
        }
    }
};
