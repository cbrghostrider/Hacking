class Solution {
    using Container = set<string>;
    // Removes invalid the first time there's a mismatch due to extra close.    
    // Returns results matching against all possible prev opens.
    Container removeOneInvalidClose(const string& s) {
        if (s.size() == 0) return {""};
        if (s.size() >= 1 && s[0] == ')') {
            return {s.substr(1)};
        }
        
        int num_opens=0;
        vector<int> closes;
        Container ans;
        
        int i=0;
        bool fail = false;
        for (; i<s.size(); i++) {
            if (s[i] == '(') {
                num_opens++;
            } else if (s[i] == ')') {
                if (closes.size() < num_opens) {
                    closes.push_back(i);
                } else {
                    closes.push_back(i);
                    fail = true;
                    break;  // found first invalid close
                }
            }
        }
        
        if (fail) {
            for (int c_pos : closes) {
                string expr = s.substr(0, c_pos);
                expr += s.substr(c_pos+1);
                ans.insert(expr);
            }
        } else {
            ans = {s};
        }
        
        return ans;
    }
    
    Container repeatUntilDone(Container choices) {
        bool change = true;
        while (change) {
            Container ans;
            for (const string& choice : choices) {
                Container rec = removeOneInvalidClose(choice);
                for (const string& r : rec) {
                    ans.insert(r);
                }
            }
            change = (ans != choices);
            std::swap(ans, choices);
            ans.clear();
        }        
        return choices;
    }
    
    string reverseWithInversion(string str) {
        std::reverse(str.begin(), str.end());
        for_each(str.begin(), str.end(), [](char& ch) {
            if (ch == '(') ch = ')';
            else if (ch == ')') ch = '(';
        });
        return str;
    }
    
public:
    vector<string> removeInvalidParentheses(string s) {
        Container choices;
        
        // first run the algorithm through
        // so we get rid of spurious close        
        choices.insert(s);        
        choices = repeatUntilDone(choices);
        
        // Now reverse all the choices and do it again, to get rid of spurious opens.        
        Container choices2;
        for (const string& choice : choices) {
            string c2 = reverseWithInversion(choice);            
            choices2.insert(c2);
        }
        choices2 = repeatUntilDone(choices2);
     
        vector<string> ans;
        for (const string& choice : choices2) {
            string str=reverseWithInversion(choice);                          
            ans.push_back(str);
        }
        return ans;
    }
};
