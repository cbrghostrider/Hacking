class Solution {
    class Calc {
        vector<int> vals;
      public:
        Calc() {}
        int evaluate() {
            if (vals.empty()) return 1;
            int sum = 0;
            for (int i=0; i<vals.size(); i++) {sum += vals[i];}
            return 2*sum;
        }
        void append(int val) {
            vals.push_back(val);
        }
    };
public:
    int scoreOfParentheses(string s) {
        vector<Calc> stack;
        stack.push_back(Calc());
        
        for (char ch : s) {
            if (ch == '(') {
                stack.push_back(Calc());
            } else {  // ch == ')'
                int val = stack.back().evaluate();
                stack.pop_back();
                stack.back().append(val);
            }
        }
        return stack.back().evaluate()/2;
    }
};
