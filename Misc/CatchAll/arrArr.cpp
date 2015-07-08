// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// set every arr[i] to arr[arr[i]] WITHOUT using extra space (O(1) space)
//
#include <iostream>
#include <cstdio>
#include <vector>

using std::vector;

//since we are using a value within an array as an index, it is reasonable to assume that it is non-negative
//in other words, the MSB bit is 0
//we can use this as a temporary storage *flag*, and reset the flags later
void rearrange(vector<int>& nums) {
    int ctr = 0; 
    while (ctr < nums.size()) {             //keep repeating until I write all the positions
        int index=0;
        for (int i=0; i<nums.size(); i++) { //find first non-processed number
            if (nums[i] >= 0) { index = i; break;}
        }

        int temp = nums[index];             //now I can start writing from here
        while (nums[index] >= 0) {
            int newIndex = nums[index];     //this position freed up next
            nums[index] = nums[nums[index]];
            nums[index] |= 0x80000000;      //mark my flag as done
            if (nums[newIndex] >= 0) index = newIndex;
            ctr++; 
        }
        nums[index] = temp;                 //write our original value
    }

    //reset our flags
    for (int& n : nums) { n &= 0x7fffffff;}
}

int main() {
    int n; std::cin >> n;
    vector<int> nums;
    for (int i=0; i<n; i++) {
        int num; std::cin >> num;
        nums.push_back(num);
    }
    rearrange(nums);
    for (const int& ni : nums) std::cout << ni << " ";
    std::cout << std::endl;
}
