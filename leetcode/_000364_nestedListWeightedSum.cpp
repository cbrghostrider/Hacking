/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
    int getMaxDepth(const vector<NestedInteger>& nl) {
        int max = 0;
        for (const auto& ni : nl) {
            int level=0;
            if (ni.isInteger()) {level = 1;}
            else {level = 1 + getMaxDepth(ni.getList());}
            if (level > max) {max = level;}
        }
        return max;
    }
    
    int computeWeightedSum(const vector<NestedInteger>& nl, int max_depth, int in_depth) {
        int sum=0;
        for (const auto& ni : nl) {
            if (ni.isInteger()) {
                sum += ((max_depth - in_depth + 1) * ni.getInteger());
            } else {
                sum += computeWeightedSum(ni.getList(), max_depth, in_depth+1);
            }
        }
        return sum;
    }
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int max_depth = getMaxDepth(nestedList);
        int sum = computeWeightedSum(nestedList, max_depth, 1);
        return sum;
    }
};
