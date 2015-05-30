// Modeled this question as a graph problem this time around
//
// Constructed a graph from the dictionary words
// Every word in the dict is a node in the graph
// Links connect words that differ by exactly one letter
// start and end strings are also added to the graph
//
// The problem then reduces to finding ALL shortest paths from start to end
// in the constructed graph.
// I use DFS traversal to get the shortest paths, since edge weights are all 1


class Graph {
private:
    struct GraphNode {
        string name; 
        int id;
        int val;
        GraphNode(string n, int i) : name(n), id(i), val(std::numeric_limits<int>::max()){}
    };
public:
    Graph(string start, string end, unordered_set<string>& dict);
    ~Graph();
    vector<vector<string>> shortestPaths(string start, string end);
private:
    int nodeId(const string& str) {return ((strMap.find(str))->second->id);}
    void constructGraph(string start, string end, unordered_set<string>& dict);
    vector<vector<string>> compileBackLinks(GraphNode* ret); 

    typedef vector<GraphNode*> Bucket;
    vector<Bucket> adjList;
    unordered_map<string, GraphNode*> strMap;
    const int NUM_LETTERS;

};

Graph::Graph(string start, string end, unordered_set<string>& dict)
: adjList(), strMap(), NUM_LETTERS(26)
{
    constructGraph(start, end, dict);
}

Graph::~Graph()
{
    for (pair<string, GraphNode*> sm : strMap) {
        delete (sm.second);
    }
}

void Graph::constructGraph(string start, string end, unordered_set<string>& dict)
{
    dict.insert(start);
    dict.insert(end);

    int ctr=0;
    for (const string& word : dict) {
        GraphNode *gn = new GraphNode(word, ctr);
        strMap.insert(make_pair(word, gn));
        adjList.push_back(Bucket());
        ctr++;
    }

    for (const string& word : dict) {
        for (int i=0; i<word.size(); i++) {
            for (int j=0; j<NUM_LETTERS; j++) {
                char letter = 'a' + j;
                if (letter == word[i]) continue;
                string w = word.substr(0, i) + string (1, letter) + word.substr(i+1);
                auto it = dict.find(w);
                if (it == dict.end()) continue;
                adjList[nodeId(word)].push_back((strMap.find(w))->second); //don't push back other end, because it will happen later
            }
        }
    }
}

vector<vector<string>> Graph::compileBackLinks(GraphNode* ret) 
{
    if (ret == NULL) return vector<vector<string>>();
    if (ret->val == 0) return vector<vector<string>>(1, vector<string>(1, ret->name)); 

    vector<vector<string>> retval;

    for (GraphNode* nd : adjList[ret->id]) {
        if (nd->val != ret->val - 1) continue;
        vector<vector<string>> recurse = compileBackLinks(nd);
        for (vector<string>& vs : recurse) {
            vs.push_back(ret->name);
            retval.push_back(vs);
        }
    }
    return retval;
}

vector<vector<string>> Graph::shortestPaths(string start, string end)
{
    int minlen = std::numeric_limits<int>::max();

    if (strMap.find(start) == strMap.end() || strMap.find(end) == strMap.end()) return vector<vector<string>>();

    GraphNode *ret = NULL;

    queue<GraphNode*> nodes;
    GraphNode *startNd = (strMap.find(start))->second;
    startNd->val = 0;
    nodes.push(startNd);


    while (!nodes.empty()) {

        //if already got all candidates within minlen distance, just return back
        while (!nodes.empty() && nodes.front()->val > minlen) {
            nodes.pop();
            return compileBackLinks(ret);
        }

        GraphNode* me = nodes.front(); nodes.pop();

        if (me->name == end) { //found end word
            minlen = me->val;  //this is how far along I want to search
            ret = me;
            continue;
        }

        for (GraphNode*& gn : adjList[me->id]) {
            if (gn->val <= me->val) continue; //don't want to go back
            gn->val = me->val + 1;
            nodes.push(gn);
        }
    }

    return compileBackLinks(ret);

}

class Solution {
public:
    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        Graph graph(start, end, dict);
        return graph.shortestPaths(start, end);
    }
};

