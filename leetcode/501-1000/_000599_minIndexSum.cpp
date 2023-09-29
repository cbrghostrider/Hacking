class Solution {
    std::unordered_map<string, int> count;
    std::unordered_map<string, int> index_sum;
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        for (int i=0; i<list1.size(); i++) {
            count[list1[i]]++;
            index_sum[list1[i]] += i;
        }
        for (int i=0; i<list2.size(); i++) {
            count[list2[i]]++;
            index_sum[list2[i]] += i;
        }
        int isum = std::numeric_limits<int>::max();
        std::vector<string> chosen;
        for (const std::pair<string, int>& kv : index_sum) {
            const string& r = kv.first;
            if (count[r] < 2) continue;
            if (kv.second < isum) {
                isum = kv.second;
                chosen.clear();
                chosen.push_back(kv.first);
            } else if (kv.second == isum) {
                chosen.push_back(kv.first);
            }
        }
        return chosen;
    }
};
