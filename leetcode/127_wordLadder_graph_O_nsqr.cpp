// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//solution currently getting TLE on big inputs
//
//This version constructed a graph from all the words in the dictionary.
//Two nodes in the graph were connected with an edge if they differed in exactly one spot.
//The start and end words were also added to the graph, w/ proper edges.
//Then a BFS from start node was conducted, which gave the shortest path to the end node
//
//The time complexity of this algorithm is:
//Assuming: n words in dictionary
//Graph construction took O(n^2) to check every word against every other
//BFS is usually O(m+n) for m vertices and n edges
//depending on the input, each word could potentially be convertible into each other
//so this could be O(n^2) edges as well
//time complexity: O(n^2)
class Solution {
    //my neighbor string is one that differs from me in just one position
    bool isNeighbor_(const string& lhs, const string& rhs) {
        assert(lhs.length() == rhs.length());
        
        if (lhs == rhs || lhs.length() == 0) return false;       //same item 
        int diffCnt=0;
        for (int i=0; i<lhs.length(); i++) {
            if (lhs[i] != rhs[i]) {
                diffCnt++;
            }
        }
        return (diffCnt == 1 ? true : false);
    }
    
    class Node {
    public:
        string me;
        int val;
        bool explored;
        unordered_set<Node*> neighbors;
        
        Node(const string& str) : me(str), val(0), explored(false), neighbors() {}
        bool hasNeighbor(Node *const check) { return (neighbors.find(check) != neighbors.end());}
        void addNeighbor(Node *const nb) {if (!hasNeighbor(nb)) neighbors.insert(nb);}
    };
    
    void clearMarks() {
        for (Node* const& nd : words) {
            nd->val=0;
            nd->explored = false;
        }
    }
    
    unordered_set<Node*> words; //dictionary as nodes
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict) {
        
        //assign nodes to all words in dict
        for (const string& str : wordDict) {
            words.insert(new Node(str));
        }
        
        //add nodes for check strings
        Node *beginnode = new Node(beginWord);
        Node *endnode   = new Node(endWord);
        words.insert(beginnode);
        words.insert(endnode);
        
        //create graph
        for (Node* const& ndlhs : words) {
            for (Node* const& ndrhs : words) {
                if (isNeighbor_(ndlhs->me, ndrhs->me)) {
                    ndlhs->addNeighbor(ndrhs);
                    ndrhs->addNeighbor(ndlhs);
                }
            }
        }
        
        //check edge cases
        auto bit = words.find(beginnode);
        auto eit = words.find(endnode);
        if ((*bit)->neighbors.size() == 0 || (*eit)->neighbors.size()  == 0 || beginWord == endWord) {
                return 0; //no transformation possible, or trivial identity transformation
        }
        
        int pathLen=0;
        bool done = false;
        deque<Node*> que(1, beginnode);
        //breadth first search to get path length
        while (!que.empty() && !done) {
            Node* exp = que.front(); que.pop_front();
            exp->explored = true;
            
            for (Node *const& nd : exp->neighbors) {
                if (nd->explored) continue;
                nd->val = exp->val+1;
                que.push_back(nd);
                if (nd == endnode) {
                    done = true;
                    pathLen = nd->val;
                    break;
                }
            }
        }
        
        //free up the nodes
        for (Node *const& nd : words) {
            delete nd;
        }
        
        return (pathLen == 0 ? 0 : pathLen + 1);
    }
};
