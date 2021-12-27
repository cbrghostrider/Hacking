class Solution {
    // Can be a number, or an operator
    struct Token {       
        bool is_number = false;
        int number = 0;
        char op = ' ';
    };
    
public:
    int calculate(string s) {
        vector<Token> expr, expr2;
        int s_ptr=0;
        while (s_ptr < s.size() && s_ptr != string::npos) {
            size_t pos = s.find_first_of("+-*/", s_ptr);
            int len = pos == string::npos ? s.size()-s_ptr: pos-s_ptr;
            int num = std::stoi(s.substr(s_ptr, len));
            expr.push_back({true, num, ' '});
            if (pos != string::npos) {
                expr.push_back({false, 0, s[pos]});
                s_ptr = pos+1;
            } else {
                s_ptr = pos;
            }            
        }
        
        for (int i=0; i<expr.size(); i++) {
            if (expr[i].is_number || expr[i].op == '+' || expr[i].op == '-') {
                expr2.push_back(expr[i]);
                continue;
            }
            
            expr2.pop_back();
            
            int n1 = expr[i-1].number;            
            int n2 = expr[i+1].number;
            int val=0;
            if (expr[i].op == '*') {
                val = n1*n2;
            } else {
                val = n1/n2;
            }
            expr2.push_back({true, val, ' '});
            expr[i+1] = {true, val, ' '};
            i++;
        }
        
        for (int i=0; i<expr2.size(); i++) {
            if (expr2[i].is_number) {continue;}
            int n1 = expr2[i-1].number;
            int n2 = expr2[i+1].number;
            
            int val=0;
            if (expr2[i].op == '+')  {
                val = n1 + n2;
            } else {
                val = n1 - n2;
            }
            expr2[i+1].number = val;
            i++;
        }
        
        return expr2.back().number;
    }
};
