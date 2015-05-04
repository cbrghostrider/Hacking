//Lazy: No error checking!
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<int> operands;
        for (string& str : tokens) {
            if ((str == "+") || (str == "-") || (str == "*") || (str == "/")){
                int op2 = operands.back(); operands.pop_back();
                int op1 = operands.back(); operands.pop_back();
                if (str == "+") operands.push_back(op1 + op2); 
                if (str == "-") operands.push_back(op1 - op2); 
                if (str == "*") operands.push_back(op1 * op2); 
                if (str == "/") operands.push_back(op1 / op2); 
            } else {
                int op = std::stoi(str);
                operands.push_back(op);
            }
        }
        return operands[0];
    }
};
