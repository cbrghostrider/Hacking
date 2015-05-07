/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
    unordered_map<unsigned long, RandomListNode*> copy_; //copy from old to new
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == NULL) return NULL;
        auto cit = copy_.find((unsigned long)head);
        if (cit != copy_.end()) {
            return cit->second;
        }
        RandomListNode* headCopy = new RandomListNode(head->label);
        copy_.insert(make_pair(((unsigned long)(head)), headCopy));
        RandomListNode* copyNext = copyRandomList(head->next);
        RandomListNode* copyRand = copyRandomList(head->random);
        headCopy->next = copyNext;
        headCopy->random = copyRand;
        return headCopy;
    }
};
