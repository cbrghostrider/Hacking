class ExamRoom {
    int N;
    std::set<int> seats;
    bool occupied_first=false;
    bool occupied_last=false;
public:
    ExamRoom(int n) {
        N = n;
    }
    
    // O(log k + k) = O(k) time to seat; k = number of students
    int seat() {
        if (seats.size()==0) {occupied_first=true; seats.insert(0);return 0;}
        if (seats.size()==1 && occupied_first) {occupied_last=true; seats.insert(N-1); return N-1;}
        if (seats.size() == N) return -1;  // can't seat
        
        int widest=0;
        int chosen = -1;
        if (!occupied_first) {
            widest = *(seats.begin());
            chosen = 0;
        }
        auto it=seats.begin();
        int last = *it; it++;
        for (; it != seats.end(); it++) {
            int diff = *it - last;
            if (diff/2 > widest) {
                widest = diff/2;
                chosen = last + diff/2;
            }
            last = *it;
        }
        if (!occupied_last) {
            int dist = N - 1 - *(seats.rbegin());
            if (dist > widest) {
                widest = dist;
                chosen = N-1;
            }
        }
        seats.insert(chosen);
        if (chosen == 0) {occupied_first=true;}
        if (chosen == N-1) {occupied_last = true;}
        return chosen;
    }
    
    // O(log k) time.
    void leave(int p) {
        seats.erase(p);
        if (p == 0) {occupied_first = false;}
        if (p == N-1) {occupied_last = false;}
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
