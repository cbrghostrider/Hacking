class Solution {
public:
    string interpret(string command) {
        string ans;
        int c_ptr=0;
        while (c_ptr < command.size()) {
            if (command[c_ptr] == 'G') {
                ans.push_back('G');
                c_ptr++;
            } else if (command[c_ptr] == '(' && c_ptr < command.size()-1 && 
                       command[c_ptr+1] == ')') {
                ans.push_back('o');
                c_ptr += 2;
            } else if (command[c_ptr] == '(' && c_ptr < command.size()-3 && 
                       command[c_ptr+1] == 'a' && command[c_ptr+2] == 'l' && command[c_ptr+3] == ')') {
                ans.push_back('a');
                ans.push_back('l');
                c_ptr += 4;
            } else {
                return "Error: Malformed command.";
            }
        }
        return ans;
    }
};
