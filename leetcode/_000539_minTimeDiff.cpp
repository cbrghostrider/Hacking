class Solution {
    unordered_map<string, unordered_map<string, int>> cache_fwd, cache_back;
    const string START = "00:00";
    const string END   = "23:59";
    
    void decrement(int& hrs, int& mins) {
        mins--;
        if (mins == -1) {
            mins = 59;
            hrs--;
        }
        if (hrs == -1) {
            mins = 59;
            hrs = 23;
        }
    }
    
    void increment(int& hrs, int& mins) {
        mins++;
        if (mins == 60) {
            mins = 0;
            hrs++;
        }
        if (hrs == 24) {
            mins = 0;
            hrs = 0;
        }
    }
    
    string update(const string& time, bool is_increment) {
        int pos = time.find_first_of(":");
        int hrs = stoi(time.substr(0, pos));
        int mins = stoi(time.substr(pos+1));
        
        if (is_increment) {
            increment(hrs, mins);
        } else {
            decrement(hrs, mins);
        }
        
        string hrs_str = to_string(hrs);
        if (hrs_str.size() == 1) {hrs_str = "0"+hrs_str;}
        string min_str = to_string(mins);
        if (min_str.size() == 1) {min_str = "0"+min_str;}
        string ret =  hrs_str + ":" + min_str;
        return ret;        
    }
    
    void precompute() {
        int count=0;
        string start = END;        
        while (count == 0 || start != END) {
            cache_fwd[start][END] = count++;
            start = update(start, /*is_increment=*/false);
        }        
        
        count = 0;
        string end = START;
        while (count == 0 || end != START) {
            cache_back[START][end] = count++;
            end = update(end, /*is_increment=*/true);
        }                
    }        
    
public:
    // O(n log n) for sort.
    int findMinDifference(vector<string>& timePoints) {
        if (timePoints.size() <= 1) return 0;
        precompute();
        
        std::sort(timePoints.begin(), timePoints.end(), [](const string& lhs, const string& rhs) -> bool {
            for (int i=0; i<=4; i++) {
                if (lhs[i] < rhs[i]) return true; else if (lhs[i] > rhs[i]) return false;
            }
            return false;            
        });
                
        int min_diff = std::numeric_limits<int>::max();
        for (int i=0; i<timePoints.size(); i++) {
            
            string tp1 = timePoints[i];
            string tp2 = i == timePoints.size()-1 ? timePoints[0] : timePoints[i+1];
                
            int cand1 = std::abs(cache_fwd[tp1][END] - cache_fwd[tp2][END]);                
            int cand2 = std::abs(cache_fwd[tp1][END] + cache_back[START][tp2] + 1);
            int cand3 = std::abs(cache_fwd[tp2][END] + cache_back[START][tp1] + 1);
            min_diff = std::min(std::min(min_diff, cand1),std::min(cand2, cand3));            
        }
        return min_diff;
    }
};
