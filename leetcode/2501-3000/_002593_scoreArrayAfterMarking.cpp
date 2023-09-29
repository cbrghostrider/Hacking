struct Info {
    int val=0;
    int ind=-1;
    bool mark=false;
    Info(int v, int i, bool m) : val(v), ind(i), mark(m) {}
};

bool compare_info(const Info* lhs, const Info* rhs) {
    if (lhs->val != rhs->val) return lhs->val > rhs->val;
    return lhs->ind > rhs->ind;
}

using MinHeap = priority_queue<Info*, vector<Info*>, std::function<bool(const Info*, const Info*)>>;

class Solution {
public:
    long long findScore(vector<int>& nums) {
        const int N=nums.size();
        vector<Info*> infos;
        MinHeap min_heap(compare_info);
        for (int i=0; i<nums.size(); i++) {
            Info* info = new Info(nums[i], i, false);
            infos.push_back(info);
            min_heap.push(info);
        }

        long long score=0;
        while (!min_heap.empty()) {
            Info* info = min_heap.top();
            min_heap.pop();
            if (info->mark) continue;
            score += info->val;
            if (info->ind != 0)   {infos[info->ind-1]->mark = true;}
            if (info->ind != N-1) {infos[info->ind+1]->mark = true;}
        }

        for (Info* info : infos) {
            delete info;
        }
        return score;
    }
};
