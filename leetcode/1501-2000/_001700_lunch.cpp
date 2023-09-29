class Solution {
public:
    // simulating the process
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        std::deque<int> q(students.begin(), students.end());
        std::reverse(sandwiches.begin(), sandwiches.end());
        int retry_count = 0;
        while (!sandwiches.empty() && retry_count != q.size()) {
            if (q.front() == sandwiches.back()) {
                retry_count = 0;
                q.pop_front();
                sandwiches.pop_back();
                continue;
            }
            retry_count++;
            q.push_back(q.front());
            q.pop_front();
            if (retry_count == q.size()) {
                break;
            }
        }
        return retry_count;
    }
};
