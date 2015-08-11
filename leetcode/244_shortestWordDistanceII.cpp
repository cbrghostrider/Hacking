// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Currently getting TLE for very large input; 
// I ran on my local machine, and that input takes 2.5 seconds (~4500 queries, and thousands of words in dictionary)
//
// Note that I am doing repeated bfs, better perhaps to do all pairs shortest paths
// Also note that wordDistance.h contains the dictionary and wordQueries.h contains the queries
// Posting entire program, in case someone wants to run it
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>
#include <limits>
#include "wordDistance.h"

using std::string;
using std::queue;
using std::pair;
using std::make_pair;
using std::vector;
using std::unordered_map;
using std::unordered_set;

class WordDistance {
    vector<vector<int>> adjList; //graph
    unordered_map<string, unordered_set<int>> wordToLocations; //tells us where various words are found
    vector<bool> visited;          //for graph search

    void clearFlags() { for (int i=0; i<visited.size(); i++) { visited[i] = false; }  }

    int bfs(int fromNd, const unordered_set<int>& cands) {
        queue<pair<int, int>> bfsqu;
        bfsqu.push(make_pair(fromNd, 0)); 
        visited[fromNd] = true;

        while (!bfsqu.empty()) {
            pair<int, int> quelem = bfsqu.front(); bfsqu.pop();
            if (cands.find(quelem.first) != cands.end()) {
                return quelem.second; //found a candidate node for "to" string!
            }
            for (const int& neigh : adjList[quelem.first]) {
                if (visited[neigh]) continue;
                visited[neigh] = true;
                bfsqu.push(make_pair(neigh, quelem.second+1));
            }
        }
        return -1; //not found in bfs
    }

public:
    WordDistance(vector<string>& words) {
        adjList = vector<vector<int>>(words.size(), vector<int>());
        visited = vector<bool>(words.size(), false);

        for (int i=0; i<words.size(); i++) {
            if (i != 0) { adjList[i].push_back(i-1); }
            if (i != words.size()-1) { adjList[i].push_back(i+1); }

            auto it = wordToLocations.find(words[i]);
            if (it == wordToLocations.end()) {
                wordToLocations.insert(make_pair(words[i], unordered_set<int>()));
            }
            wordToLocations[words[i]].insert(i);
        }
    }

    int shortest(string word1, string word2) {
        if (wordToLocations.find(word1) == wordToLocations.end() || 
            wordToLocations.find(word2) == wordToLocations.end()) {
            return -1; //undefined really
        }

        string& from = (wordToLocations[word1].size() > wordToLocations[word2].size()) ? word2 : word1;
        string& to   = (wordToLocations[word1].size() <= wordToLocations[word2].size()) ? word2 : word1;

        int distance = std::numeric_limits<int>::max();

        for (const int& fromNd : wordToLocations[from]) {
            clearFlags();
            int bfsval = bfs(fromNd, wordToLocations[to]);
            if (bfsval < distance) {
                distance = bfsval;
            }
        }
        return distance;
    }
    int distance(string twowords) {
        size_t pos = twowords.find_first_of(",");
        string word1 = twowords.substr(0, pos);
        string word2 = twowords.substr(pos+1);
        return shortest(word1, word2);
    }
};

int test1() {
    vector<string> words = {"practice", "makes", "perfect", "coding", "makes"};
    WordDistance wd(words); 
    int ans1 = wd.shortest("coding", "practice");
    std::cout << ans1 << std::endl;
    int ans2 = wd.shortest("makes", "coding");
    std::cout << ans2 << std::endl;
}

int test2() {
    vector<string> words = WORDS;
    WordDistance wd(words); 
#include "wordQueries.h"
}

int main() {
    test2();
}


