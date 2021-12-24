constexpr int NUM_ELEMS = 26 + 26 + 10;

class Solution {
    
    struct Node {
        char ch = ' ';
        bool ends_here = false;
        vector<Node*> children;
        
        Node(char c = ' ') : ch(c) {
            children = vector<Node*>(NUM_ELEMS, nullptr);
        }
        ~Node() {
            for (Node* n : children) { delete n; }
        }
    };
    Node* root=nullptr;  // root of the trie
    
    unordered_map<char, int> positions;  // placement of char in children array
    
    void setPositions() {
        int pos=0;
        for (char ch='a'; ch <= 'z'; ch++) {
            positions[ch] = pos++;
        }
        for (char ch='A'; ch <= 'Z'; ch++) {
            positions[ch] = pos++;
        }
        for (char ch='0'; ch<='9'; ch++) {
            positions[ch] = pos++;
        }
    }
    
    void buildTrie(const vector<string>& words) {
        for (const string& word : words) {
            Node* node = root;
            for (int i=0; i<word.size(); i++) {
                char me = word[i];
                Node* child = node->children[positions[me]];
                if (child == nullptr) {
                    child = node->children[positions[me]] = new Node(me);
                }
                if (i == word.size()-1) {
                    child->ends_here = true;
                }
                node = child;
            }
        }
    }
    
    // Interval marks the start and end indices (inclusive) of a substr that matched.
    struct Interval {
        int start=-1;
        int end=-1;
    };
    vector<Interval> matches;
    
    // MatchInfo stores information about matches in progress.
    struct MatchInfo {
        Interval interval;
        Node* node=nullptr;
    };
    
    vector<MatchInfo> in_progress;
    
public:
    // Any time we encounter a next letter, we potentially:
    // 1. Start a new trie match.
    // 2. Continue an in-progress trie match.
    // 3. End an in-progress trie-match (successfully or unsuccessfully).
    //
    // When we end 3 successfully, we save the interval.
    void populateIntervals(const string& s) {
        for (int i=0; i<s.size(); i++) {
            char ch = s[i];
            
            int num_in_progress = in_progress.size();
            
            // start a new trie match if needed.
            if (root->children[positions[ch]]) {
                in_progress.push_back({{i, -1}, root->children[positions[ch]]});
            }
            
            // check the ones already in progress.
            vector<int> fail;
            for (int p=0; p<num_in_progress; p++) {
                if (in_progress[p].node->children[positions[ch]] == nullptr) {
                    fail.push_back(p);
                    continue;
                }
                in_progress[p].node = in_progress[p].node->children[positions[ch]];
            }            
            for (int f=fail.size()-1; f>=0; f--) {
                in_progress.erase(begin(in_progress) + fail[f]);
            }
            
            // note the ones that passed
            for (int p=0; p<in_progress.size(); p++) {
                if (in_progress[p].node->ends_here) {
                    matches.push_back({in_progress[p].interval.start, i});
                    // DO NOT remove this, as the trie could get another match further into i
                }
            }
        }
    }
    
    // processes possibly overlapping and adjacent intervals into
    // a bunch of DISJOINT and NON-ADJACENT intervals
    void processIntervals() {
        std::sort(matches.begin(), matches.end(), 
                  [](const Interval& lhs, const Interval& rhs) -> bool {
            if (lhs.start != rhs.start) return lhs.start < rhs.start;
            return lhs.end > rhs.end;
        });
        
        // 
        vector<Interval> ans; 
        
        Interval prev = {-1, -1};
        for (int i=0; i<matches.size(); i++) {
            if (prev.start == -1) {prev = matches[i]; continue;}
            if (matches[i].start <= prev.end + 1) {
                prev.end = std::max(prev.end, matches[i].end);
            } else {
                ans.push_back(prev);
                prev = matches[i];
            }
        }
        if (prev.start != -1) { ans.push_back(prev);}
        
        matches = ans;
    }
    
    // n: |s|; m = |word|; k = num_words
    string addBoldTag(string s, vector<string>& words) {
        root = new Node();

	// O(1) time, O(1) space.
        setPositions();

	// O(km) time, O(km) space.
        buildTrie(words);

        // O(nk) time, O(k) space for in_progress array, O(n) space for intervals found. 	
        populateIntervals(s);

        // O(n) time, O(n) space.	
        processIntervals();
        
        string ans;
        int next=0;
	// O(n) time for going through matches and constructing new substr.
        for (int i=0; i<matches.size(); i++) {
            if (next < matches[i].start) {
                ans += s.substr(next, matches[i].start - next);
            }
            ans += "<b>";
            ans += s.substr(matches[i].start, matches[i].end-matches[i].start+1);
            ans += "</b>";
            next = matches[i].end+1;
        }
        if (next < s.size()) {
            ans += s.substr(next);
        }
        return ans;
    }
};
