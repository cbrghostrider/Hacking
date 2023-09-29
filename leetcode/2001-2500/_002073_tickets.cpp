class Solution {
public:
    // Brute force
    // O(n*m) time: n is len of tickets, m is maxvalue of each ticket
    int timeRequiredToBuy2(vector<int>& tickets, int k) {
        if (k >= tickets.size() || k < 0) return -1;
        std::deque<std::pair<int, int>> tick_tags;
        int i=0;
        std::transform(tickets.begin(), tickets.end(), std::back_inserter(tick_tags), 
                       [&i](int tickets) -> std::pair<int, int> {
            return std::make_pair(tickets, i++);
        });
        
        int time=0;
        while (!tick_tags.empty()) {
            auto& front = tick_tags.front();
            time++;
            front.first--;
            if (front.first == 0 && front.second == k) {
                return time;
            }
            if (front.first > 0) tick_tags.push_back(front);
            tick_tags.pop_front();
        }
        return -1;  // should not get here
    }  
};
