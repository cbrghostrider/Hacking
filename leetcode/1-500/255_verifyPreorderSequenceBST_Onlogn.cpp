// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Here is my write from leetcode. Solution is O(n log n)
//
// I'm in bit of disbelief that my solution was accepted. I coded it up while I was really sleepy, and hit submit, 
// fully expecting it to fail compilation or something...
//
// The logic is as follows:
//
// For any pre-order sequence, we have:
// 1. The root, followed by
// 2. Another preorder sequence for the LHS, where everything is less than root, followed by,
// 3. Another preorder sequence for the RHS, where everything is greater than root.
// In order to find the boundary of the LHS preorder and the RHS preorder, you can run binary search to look for the boundary where 
// the elements transition from being (< root) to being (> root).
//
// Once you find the boundary, you can recursively call the verify function on the LHS preorder sequence and 
// the RHS preorder sequence. The trick is to pass two elements along, that say what the relationship of the 
// elements should be w.r.t. the ancestors that have gone by so far. e.g. I am passing two elements 
// (lessThan and greaterThan) which say that all elements in the preorder sequence need to be less than lessThan, 
// and greater than greaterThan. Look at the recursive calls for lhsverify and rhsverify bools to see what is 
// being passed on to recursive calls.
//
class Solution {
    //boundary denotes LAST number that is less than or equal to num
    int binarySearchBoundary(vector<int>& preorder, int from, int to, int num) {
        if (from == to) return from;
        int mid = (from+to)/2;
        int midplus = mid + 1;
        if (preorder[mid] <= num && preorder[midplus] > num) return mid;
        if (preorder[mid] > num) return binarySearchBoundary(preorder, from, mid, num);
        return binarySearchBoundary(preorder, midplus, to, num);
    }

    //verify the sequence from from to to, in which every elements needs to be less than, and greater than the numbers stated
    bool verify(vector<int>& preorder, int from, int to, int lessThan, int greaterThan) {
        if (from > to) return true;
        int root = preorder[from];
        if (root > lessThan || root < greaterThan) return false;
        if (from == to) return true;
        
        int boundary = binarySearchBoundary(preorder, from, to, root);
        bool lhsverify = verify(preorder, from+1, boundary, min(lessThan, root), greaterThan); 
        bool rhsverify = verify(preorder, boundary+1, to, lessThan, max(root, greaterThan)); 
        return (lhsverify && rhsverify);
    }

public:
    bool verifyPreorder(vector<int>& preorder) {
        if (preorder.size() == 0) return true;
        return verify(preorder, 0, preorder.size()-1, std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
    }
};
