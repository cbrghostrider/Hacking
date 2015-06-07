// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
private:
    typedef UndirectedGraphNode UGN;
    unordered_map<int, UGN*> nodeMap_; // node label -> node ptr mapping

public:

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL) return NULL;
        auto it = nodeMap_.find(node->label);
        if (it != nodeMap_.end()) {
            return it->second;
        }
        
        //allocate my node
        UGN *myNode = new UGN(*node);
        nodeMap_.insert(make_pair(myNode->label, myNode));          //even though self-reference not established yet, this is ok!
        
        for (unsigned int i=0; i<node->neighbors.size(); i++) {
            myNode->neighbors[i] = cloneGraph(node->neighbors[i]);  //self reference established automatically if needed
        }
        return myNode;
    }
};
