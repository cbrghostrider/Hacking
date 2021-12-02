class Solution {
    struct CitAndNum {
        int citations=0;  // exactly these number of citations
        int num_papers=0; // for these number of papers
    };
public:
    int hIndex(vector<int>& citations) {
        map<int, int> cits_to_num_papers;
        for (int c : citations) {cits_to_num_papers[c]++;}
        
        vector<CitAndNum> can;
        for (const auto& kv : cits_to_num_papers) {can.push_back({kv.first, kv.second});}
        std::sort(can.begin(), can.end(), [](const CitAndNum& lhs, const CitAndNum& rhs) -> bool {
            if (lhs.citations != rhs.citations) return (lhs.citations < rhs.citations);
            return (lhs.num_papers < rhs.num_papers);
        });
        
        const int total_papers=citations.size();
        
        int sum_papers=0;
        int h = can.back().citations;
        int cp = can.size()-1;
        for (; h>=0 && cp>=0; h--) {
            if (h == can[cp].citations) {
              sum_papers += can[cp--].num_papers;
            }

            if (sum_papers >= h) {
                return h;
            }
        }
        return citations.size();
    }
};
