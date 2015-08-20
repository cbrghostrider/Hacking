// 
// Consider the string representation of binary trees. Each node is of the form 
// (lr) where l is left child and r is right child. 
// if l or r is 0, there is no left or right child.
// Otherwise for example a single node is represented as (00)
// This can be recursive, so a full subtree of height 1 is ((00)(00))
// 
// Given this recursive representation of a tree:
// Return either the depth of the tree if it is well formed, or -1 if it is not.
//
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

int find_depth_(string str, int& i) {
    if (str.length() <= i) return -1;
    if (str[i] == '0') {
        i++;
        return 0;
    }
    if (str[i] != '(') return -1;
    i++; //for the '('

    int depthlhs = find_depth_(str, i);
    if (depthlhs == -1) return -1;

    int depthrhs = find_depth_(str, i);
    if (depthrhs == -1) return -1;

    if (str[i] != ')') return -1;
    i++; // for the ')'

    return (1 + std::max(depthlhs, depthrhs));
}

int find_depth(string str) {
    int i=0;
    int ret = find_depth_(str, i);
    if (i != str.length()) return -1;
    return (ret - 1);
}

int main() {
    int ans1 = find_depth(string("(00)"));
    std::cout << ans1 << std::endl;
    int ans2 = find_depth(string("((00)0)"));
    std::cout << ans2 << std::endl;
    int ans3 = find_depth(string("((00)(00))"));
    std::cout << ans3 << std::endl;
    int ans4 = find_depth(string("((00)(0(00)))"));
    std::cout << ans4 << std::endl;
    int ans5 = find_depth(string("((00)(0(0(00))))"));
    std::cout << ans5 << std::endl;
    int ans6 = find_depth(string("x"));
    std::cout << ans6 << std::endl;
    int ans7 = find_depth(string("0"));
    std::cout << ans7 << std::endl;
    int ans8 = find_depth(string("()"));
    std::cout << ans8 << std::endl;
    int ans9 = find_depth(string("(0)"));
    std::cout << ans9 << std::endl;
    int ans10 = find_depth(string("(00)x"));
    std::cout << ans10 << std::endl;
    int ans11 = find_depth(string("(0p)"));
    std::cout << ans11 << std::endl;
}
