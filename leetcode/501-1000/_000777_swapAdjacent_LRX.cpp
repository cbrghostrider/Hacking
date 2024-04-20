class Solution {

string transform(const string& str) {
    string ret;
    for (char ch: str) {
        if (ch == 'X') continue;
        ret.push_back(ch);
    }
    return ret;
}

typedef priority_queue<int, vector<int>, std::less<int>> MaxHeap;
typedef priority_queue<int, vector<int>, std::greater<int>> MinHeap;

public:
    bool canTransform(string start, string end) {
        string orig_start = start, orig_end = end;

        string ts = transform(start);
        string te = transform(end);
        if (ts != te) return false;

        MaxHeap max_heap;
        MinHeap min_heap;
        for (int i=0; i<start.size(); i++) {
            if (start[i] == 'L') max_heap.push(i);
            if (start[i] == 'R') min_heap.push(i);
        }
        
        // The 'L's in the original string cannot move rightward.
        for (int i=end.size()-1; i>=0; i--) {
            if (end[i] != 'L') continue;
            int pos = max_heap.top(); max_heap.pop();
            if (i > pos)  {                
                return false;
            }
        }

        // The R's in the original string cannot move leftward.
        for (int i=0; i<end.size(); i++) {
            if (end[i] != 'R') continue;
            int pos = min_heap.top(); min_heap.pop();
            if (i < pos) {                
                return false;
            }
        }

        return true;
    }
};
