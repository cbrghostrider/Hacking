/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 enum Dir {
     RIGHT=0,
     DOWN,
     LEFT,
     UP
 };
 struct Coord {
     int r=0;
     int c=0;
 };

class Solution {
    vector<vector<int>> ans;
    int R, C;
    Dir cur_dir = RIGHT;
    Dir nextDir(Dir dir) {
         return (Dir)(((int)dir +1) % 4);
    }
    Coord nextCoord(Coord coord) {
        switch (cur_dir) {
            case RIGHT: return {coord.r,   coord.c+1};
            case DOWN:  return {coord.r+1, coord.c};
            case LEFT:  return {coord.r,   coord.c-1};
            case UP:    return {coord.r-1, coord.c};
        }
        return Coord();  // should not get here
    }
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        R=m; C=n;
        ans = vector<vector<int>>(R, vector<int>(C, -1));

        ListNode *node = head;
        Coord coord = {0, 0};
        while (node) {
            ans[coord.r][coord.c] = node->val;
            node = node->next;
            Coord next = nextCoord(coord);
            if (next.r == -1 || next.r == R || next.c == -1 || next.c == C || ans[next.r][next.c] != -1) {
                cur_dir = nextDir(cur_dir);
                next = nextCoord(coord);
            }
            coord = next;
        }
        return ans;
    }
};
