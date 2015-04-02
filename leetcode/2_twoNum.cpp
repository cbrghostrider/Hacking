 
class Solution {
public:
    ListNode *head = NULL;
    ListNode *last = NULL;
    
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        addTwoNumbers_(l1, l2, 0);
        return head;
    }
    
    void addTwoNumbers_(ListNode *l1, ListNode *l2, int carry) {
        int val1 = 0, val2 = 0;
        if (l1 != NULL) {
            val1 = l1->val;
        if (l2 != NULL) {
            val2 = l2->val;
        }
        
        int mySum = val1 + val2 + carry;
        if (mySum == 0 && l1 == NULL && l2 == NULL) {
            return;
        }
        
        int myVal = mySum % 10;
        int myCarry = mySum / 10;
        
        ListNode *myNode = new ListNode(myVal);
        if (head == NULL) {
            head = last = myNode;
        } else {
            last->next = myNode;
            last = myNode;
        }
        
        addTwoNumbers_(l1 ? l1->next : l1, l2 ? l2->next : l2, myCarry);
    }

};
