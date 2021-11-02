class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> stack;
        for (const string& op : ops) {
            if (op == "+") {
                int num1 = stack[stack.size() - 1];
                int num2 = stack[stack.size() - 2];
                stack.push_back(num1 + num2);
            } else if (op == "C") {
                stack.pop_back();
            } else if (op == "D") {
                int num = stack.back();
                stack.push_back(num * 2);
            } else {
                int num = std::stoi(op);
                stack.push_back(num);
            }
        }
        int sum = 0;
        std::for_each(stack.begin(), stack.end(), [&sum](int num) { sum += num; });
        return sum;
    }
};
