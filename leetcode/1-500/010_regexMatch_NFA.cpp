// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// constructing a non-deterministic finite automata from the regex
// and simulating it to get the answer!
//
// complexity is O(mn) where m = length of regex, and n = length of input
const char WILDCARD = '.';
enum EdgeType {CHAR, EPSILON}; 
typedef int Node;
typedef pair<Node, EdgeType> Edge;

class DiGraph {
private:
    unordered_map<Node, vector<Edge> > adjList;
public:

    DiGraph(int numNodes);
    void addEdge(int from, int to, EdgeType type);
    unordered_set<Node> directedDFS(Node src);
    unordered_set<Node> directedDFS(unordered_set<Node> srcs);
    ~DiGraph();
};

DiGraph::DiGraph(int nnodes)
: adjList() {
    for (int i=0; i<nnodes; i++) {
        adjList[i] = vector<Edge>();
    }
}

DiGraph::~DiGraph() {
}

void DiGraph::addEdge(int from, int to, EdgeType type) {
    adjList[from].push_back(make_pair(to, type));
}

//find all Nodes reachable from src nodes through epsilon transitions
unordered_set<Node> DiGraph::directedDFS(unordered_set<Node> srcs) {
    unordered_set<Node> retval;
    vector<bool> visited(adjList.size(), false);
    vector<Node> stack;
    for (const Node& src : srcs) {
        stack.push_back(src);
        visited[src] = true;
    }

    while (!stack.empty()) {
        Node nd = stack.back(); stack.pop_back();

        retval.insert(nd);

        for (Edge& e : adjList[nd]) {
            if (visited[e.first]) continue;
            if (e.second == EPSILON) {
                visited[e.first] = true;
                stack.push_back(e.first);
            }
        }
    }
    return retval;
}

unordered_set<Node> DiGraph::directedDFS(Node src) {
    unordered_set<Node> srcs;
    srcs.insert(src);
    return (directedDFS(srcs));
}

class NFA {
private:
    string re;
    int M; //number of states
    DiGraph regraph;

public:
    NFA(string exp);
    ~NFA();
    void buildEpsilonTransitionGraph();
    bool recognizes(string haystack);
};

NFA::NFA(string exp) 
: re("(" + exp + ")"), M(exp.size()+1+2), regraph(M) {
    buildEpsilonTransitionGraph();
}

NFA::~NFA() {
}

void NFA::buildEpsilonTransitionGraph() {
    vector<Node> stack; //to store '(', '|', and ')'
    for (int i=0; i<M-1; i++) {
        int lpi = i;
        char ch = re[i];

        if (ch == '(' || ch == '|') {
            stack.push_back(i);
        }
        if (ch != '(' && ch != '|' && ch != ')' && ch != '*') {
            regraph.addEdge(i, i+1, CHAR);
        } else if (ch != '|') {
            regraph.addEdge(i, i+1, EPSILON);
        }

        if (ch == ')') {
            int ori = stack.back(); stack.pop_back();

            if (re[ori] == '|') {
                lpi = stack.back(); stack.pop_back();
                regraph.addEdge(ori, i,EPSILON);
                regraph.addEdge(lpi, ori+1, EPSILON);
            } else {
                lpi = ori;
            }
        }

        if (re[i+1] == '*') {
            regraph.addEdge(lpi, i+1, EPSILON);
            regraph.addEdge(i+1, lpi, EPSILON);
        }

    }
}

bool NFA::recognizes(string haystack) {
    //initial reachable states
    unordered_set<Node> states = regraph.directedDFS(0);

    for (int i=0; i<haystack.length(); i++) {
        unordered_set<Node> nextSrcs;

        for (const Node& nd : states) {
            if (nd == (M-1)) continue; //end state won't go anywhere
            if (re[nd] == haystack[i] || re[nd] == WILDCARD) {
                nextSrcs.insert(nd+1);
            }
        }

        //new reachable states
        states = regraph.directedDFS(nextSrcs);
    }

    for (const Node& nd : states) {
        if (nd == (M-1)) return true;
    }
    return false;
}

class Solution {
public:
    bool isMatch(string s, string p) {
        string ss(s);
        string ps(p);
        NFA nfa(ps);
        bool ans = nfa.recognizes(ss);
        return ans;
    }
};


