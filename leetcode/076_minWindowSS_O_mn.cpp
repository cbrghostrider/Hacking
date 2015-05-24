// for each char in the string S, I check a heap for each char in T per iteration
// if size of S is n, and size of T is m, the complexity is
// O(mn) time complexity
//
// The total space consumed by ALL heaps is O(m)
// size of charToInd and charOfT is also O(m)
// So the space complexity is O(m)

class Solution {
    typedef std::priority_queue<int, std::vector<int>, std::greater<int> > MinHeap;
    unordered_map<char, int> charOfT;       //mapping from char to # of times it occurs in T (i.e. various k values)
    unordered_map<char, MinHeap> charToInd; //mapping from char of T to indices in S 
                                            //(stores indices of most recent k occurrences of char in T, in S)
                                            //k = # of times that char occurs in T
    
public:
    string minWindow(string s, string t) {
        if (t == "" || s == "") return "";
        for (int ind=0; ind<t.size(); ind++) { //count how many times a char appears in T
            auto it = charOfT.find(t[ind]);
            if (it == charOfT.end()) {
                charOfT[t[ind]]   = 1;
                charToInd[t[ind]] = MinHeap(); //create a minheap for the first time a new char appears
            } else {
                charOfT[t[ind]] += 1;
            }
        }
        
        int maxInd=std::numeric_limits<int>::max();
        int minInd=std::numeric_limits<int>::min();
        bool foundSoln = false;
        for (int ind=0; ind<s.size(); ind++) {
            if (charOfT.find(s[ind]) == charOfT.end()) continue; //not a character in T
            
            //enter index in proper heap, and if needed, remove least recent entry for this character
            MinHeap& heap = charToInd[s[ind]];
            heap.push(ind);
            if (heap.size() > charOfT[s[ind]]) heap.pop(); 

            int currmin = -1;
            //for all my current min candidates, find the one furthest left
            for (pair<const char, MinHeap>&  ctoi : charToInd) {
                MinHeap& heap = ctoi.second;
                if (heap.size() < charOfT[ctoi.first]) {
                    currmin = -1;
                    break; //didn't find enough chars of this type
                }
                if (currmin == -1 || currmin > heap.top()) currmin = heap.top();
            }
            
            //check for possible better solution
            if (currmin != -1 && (foundSoln == false || ((ind - currmin) < (maxInd - minInd)))) {
                maxInd = ind;
                minInd = currmin;
                foundSoln = true;
            }
        } 
        if (!foundSoln) return "";
        return (s.substr(minInd, maxInd-minInd+1));
    }
};
