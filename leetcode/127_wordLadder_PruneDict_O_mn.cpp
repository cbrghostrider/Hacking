// this one was accepted by online judge
// The prev algorithm was too slow. 
// This algorithm first enters the start and end words in dict.
// Then it begins with the start word, and tries each position, in sequence
//    during each position, it changes the letter into other letters (~26 tries)
//    if this new candidate is found to be in dictionary, it is put in a list 
//    (and deleted from the dictionary to prevent back-and-forth thrashing)
//    its distance from the prev is also recorded
//    in the end, either we find the end word and min-distance, or exit with no path.
// time complexity:
// Assuming max word length is m, this will try 26*m combinations for each word
// Assuming n words, complexity is O(mn)
// This is better than the previous because the length of any word is usually
// much smaller than the length of the dictionary!
class Solution {
    class Node {
    public:
        string me;
        int val;
        Node(const string& str) : me(str), val(0){}
    };

    vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                             'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                             'u', 'v', 'w', 'x', 'y', 'z'};
    
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict) {
        
        //check edge cases
        if (beginWord == endWord) {
            return 0; //no transformation possible, or trivial identity transformation
        }

        wordDict.insert(beginWord);
        wordDict.insert(endWord);

        Node *begin = new Node(beginWord);
	begin->val = 1;
        wordDict.erase(beginWord);
        int pathLen=0;
        bool done = false;
        deque<Node*> que(1, begin);
        while (!que.empty() && !done) {
            Node *exp = que.front(); que.pop_front();
            string word = exp->me;
            int myval   = exp->val;

            for (int i=0; i<word.length() && !done; i++) {
                for (int k=0; k<alphabet.size(); k++) {
                    string newstr = word.substr(0, i) + string(1, alphabet[k]) + word.substr(i+1);
                    assert(newstr.size() == word.size());
                    if (wordDict.find(newstr) == wordDict.end()) continue;

                    Node *newNd = new Node(newstr);
                    newNd->val = myval + 1;
                    que.push_back(newNd);
                    wordDict.erase(newstr);
                    if (newstr == endWord) {
                        pathLen = newNd->val;
                        done = true;
                        break;
                    }
                }
            }
            delete exp;
        }

        //unpopped items to be deleted in case of early exit
        for (Node*& nd : que) {
            delete nd;
        }
        
        return pathLen;
    }
};

