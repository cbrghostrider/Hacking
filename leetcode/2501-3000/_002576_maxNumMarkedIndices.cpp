// Assume the array is sorted.
//
// Terminology:
// Consider for any marked pair (i, j), imagine an arrow connecting them.
// Call the "smaller" value in the marked pair the "source".
// Call the "larger" value in the marked pair the "destination".
//
// Assertion 1: If the array is odd sized, I can throw out the middle number and solve for the even array, and the answer is unchanged.
// Proof: In an odd sized array, at least 1 number will be unused in markings.
// There are at most |num|/2 sources and destinations.
// If the middle number is the "source" for a marking, I can discard it and choose a smaller source to its left.
// If instead, the middle number is the "destination" for a marking, I can discard it and choose a larger destination to its right. 
// In both cases, one is guaranteed to exist, because 
//      exactly 1 number HAS to be unused, and 
//      you can't have unequal number of sources and destinations.
//  OR, because you can perform a swap for 2 src-dest pairs as explained below.
// 
// Assertion 2:
// The greedy property is this:
// For every source-destination pair that belongs entirely in the first half, we can pick a destination in the second half (since the property holds).
// Similarly, for every source-destination that belongs in the second half, we can pick a source in the first half (since the property holds).
// Since no more than |nums|/2 pairs exist, we can always pick from first half to second half.
//
// Proof:
// If we have |num|/2 pairs, 
//    For each src-dest pair in the first half, there HAS to exist another src-dest pair in the second half.
//    Then we can perform the operation in the greedy property, and maintain the same number of pair selections.
//    Eventually we will have all sources in the first half and all destinations in the second half.
//
// If we don't have |num|/2 pairs:
//    If the src-dest is in the first half, either:
//        There is an unused number in the second half, in which case, we can just use that dest
//        Or there is a src-dest pair in the second half, so we perform the previous operation to swap them.
//
//    Similar proof exists for src-dest in the second half.
//
// Eventually, you will have all sources in the first half, and all destinations in the second half.
class Solution {
public:

    int maxNumOfMarkedIndices(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());

        int mid = nums.size()/2;         
        int count=0;
        
        int src=0, dst=mid;
        // throw away the middle number for odd sized arrays, since it contributes to nothing
        if (nums.size() % 2) {dst++;} 

        while (src < mid) {
            while (dst < nums.size() && (nums[src]*2 > nums[dst])) {
                dst++;
            }
            if (dst >= nums.size()) break;
            // Found candidates (src, dst).
            count += 2;
            src++;
            dst++;
        }
        return count;
    }

};

