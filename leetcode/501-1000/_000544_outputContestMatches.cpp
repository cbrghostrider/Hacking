class Solution {

struct Info {
    int rank=0;
    string output;
};

struct InfoCmpMin {
    bool operator()(const Info& lhs, const Info& rhs) const {
        return lhs.rank > rhs.rank;
    }
};

struct InfoCmpMax {
    bool operator()(const Info& lhs, const Info& rhs) const {
        return lhs.rank < rhs.rank;
    }
};

typedef std::priority_queue<Info, vector<Info>, InfoCmpMin> MinHeap;
typedef std::priority_queue<Info, vector<Info>, InfoCmpMax> MaxHeap;

public:
    string findContestMatch(int n) {
        MinHeap min1, min2;
        MaxHeap max1, max2;

        // Initialize.
        for (int i=1; i<=n; i++) {
            Info info(i, std::to_string(i));
            min1.push(info);
            max1.push(info);
        }

        while (min1.size() > 1) {  
            const int init_size = min1.size();
            while (!min1.empty() && min1.size() > init_size/2) {
                Info worst = max1.top(); max1.pop();
                Info best  = min1.top(); min1.pop();
                string output = "(" + best.output + "," + worst.output + ")";
                Info matchup(best.rank, output);  // best wins
                min2.push(matchup);
                max2.push(matchup);
            }
            min1 = min2; min2 = MinHeap();
            max1 = max2; max2 = MaxHeap();
        }
        
        return min1.top().output;
    }
};
