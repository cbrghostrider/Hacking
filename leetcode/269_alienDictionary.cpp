// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
typedef int Node;
typedef unordered_set<Node> Bucket;
typedef vector<Bucket> AdjList;

class AlienDictionary {
public:
    AlienDictionary(const vector<string>& dict);
    string alienOrder();
private:
    enum VisitType {UNVISITED, TEMP, PERM};
    void processGraph();                         //builds a graph of relationships
    void processHorizontal(int index);           //builds relationships within a string
    void processVertical(int f, int rb, int re); //builds vertical relationships           
    void topologicalSort();                      //computes the correct ordering among alien letters
    void addDependency(char from, char to);
    void dfs(int index, vector<VisitType>& visited);

    const vector<string> words;                  //original dictionary
    unordered_map<char, Node> charToNode;        //naming scheme 
    unordered_map<Node, char> nodeToChar;        //and its reverse
    AdjList adjList;                             //relationships
    int nodeCtr;                                 //assign unique numbers to letters
    vector<int> rPostOrder;
    bool cycle;
};

AlienDictionary::AlienDictionary(const vector<string>& dict)
: words(dict), charToNode(), adjList(), nodeCtr(0), rPostOrder(), cycle(false) {
}

void AlienDictionary::addDependency(char from, char to) {
    auto fit = charToNode.find(from);
    if (fit == charToNode.end()) { 
        charToNode.insert(make_pair(from, nodeCtr)); 
        nodeToChar.insert(make_pair(nodeCtr, from));
        nodeCtr++;
        adjList.push_back(Bucket());
    }

    auto tit = charToNode.find(to);
    if (tit == charToNode.end()) {
        charToNode.insert(make_pair(to, nodeCtr));
        nodeToChar.insert(make_pair(nodeCtr, to));
        nodeCtr++;
        adjList.push_back(Bucket());
    }

    if (from == to) return;

    if (adjList[charToNode[from]].find(charToNode[to]) != adjList[charToNode[from]].end()) return;

    adjList[charToNode[from]].insert(charToNode[to]);
}

void AlienDictionary::processHorizontal(int index) {
    for (int i=0; i<words[index].size(); i++) {
        addDependency(words[index][i], words[index][i]); 
    }
}


void AlienDictionary::processVertical(int front, int rowBegin, int rowEnd) {
    if (rowBegin >= rowEnd) return;

    if (words[rowBegin].size() <= front) {
        processVertical(front, rowBegin+1, rowEnd);
        return;
    }

    int rstart  = rowBegin;
    for (int rctr=rowBegin+1; rctr<=rowEnd; rctr++) {
        if (words[rctr][front] != words[rstart][front]) {
            processVertical(front+1, rstart, rctr-1);
            addDependency(words[rstart][front], words[rctr][front]);
            rstart = rctr;
        }
    }
    processVertical(front+1, rstart, rowEnd);
}

void AlienDictionary::processGraph() {
    for (int i=0; i<words.size(); i++) {
        processHorizontal(i);
    }

    processVertical(0, 0, words.size()-1);
}

void AlienDictionary::dfs(int index, vector<VisitType>& visited) {
    if (visited[index] == PERM) return;
    if (visited[index] == TEMP) {
        cycle = true;
        return;
    }
    visited[index] = TEMP;

    for (const Node& n : adjList[index]) {
        if (visited[n] == PERM) continue;
        if (visited[n] == TEMP) {cycle = true;return;}
        dfs(n, visited);
    }
    visited[index] = PERM;
    rPostOrder.push_back(index);
}

void AlienDictionary::topologicalSort() {
    //and perform topological sort
    vector<VisitType> visited(adjList.size(), UNVISITED);

    for (int i=0;i<adjList.size(); i++) {
        if (visited[i] == PERM) continue;
        dfs(i, visited);
    }
}

string AlienDictionary::alienOrder() {
    processGraph();
    topologicalSort();
    if (cycle) return "";
    string retval;
    for (int i=rPostOrder.size()-1; i>=0; i--) {
        retval.push_back(nodeToChar[rPostOrder[i]]);
    }
    return retval;
}

class Solution {
public:
    string alienOrder(vector<string>& words) {
        AlienDictionary ad(words);
        return ad.alienOrder();
    }
};
