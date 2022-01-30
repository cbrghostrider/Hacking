struct Elem {
    bool is_num=true;
    int num=0;
    char oper= ' ';
    
    Elem(int n)   :is_num(true),  num(n), oper(' ') {}
    Elem(char op) :is_num(false), num(0), oper(op)  {}
};

class Solution {           
    int compute(const vector<Elem>& elems, char oper1, char oper2) {
        vector<Elem> e2;
        e2.push_back(elems[0]);
        
        for (int i=1; i<elems.size(); i++) {
            if (elems[i].is_num) {
                e2.push_back(elems[i]);
            } else if (elems[i].oper == oper2) {
                e2.push_back(elems[i]);
            } else {  // oper1
                int prev_op = e2.back().num; e2.pop_back();
                int next_op = elems[i+1].num;
                i++;
                int result = oper1 == '*' ? prev_op*next_op : prev_op+next_op;
                e2.push_back(Elem(result));
            }
        }
        
        int result = e2[0].num;
        for (int i=1; i<e2.size(); i++) {
            if (e2[i].is_num) {assert(0);}
            int next_op = e2[i+1].num; 
            i++;
            result = oper2 == '*' ? result*next_op : result+next_op;
        }        
        return result;
    }
    
    unordered_map<string, unordered_set<int>> cache;
    
    string signature(const string& s, int start, int end) {
        return s.substr(start, end-start+1);
    }
    
    // start, end are indices into elems.
    // this gets all possible answers for 
    // getAnswers(start, pivot-1) `oper` getAnswers(pivot+1, end)
    //   where pivot is the index of all operations between [start, end]
    //   and oper is the operation implied by elems[pivot]
    unordered_set<int> getAnswers(const string& s, int start, int end) {
        string sig = signature(s, start, end);
        if (cache.find(sig) != cache.end()) return cache[sig];
        
        if (start == end) {
            cache[sig] = {stoi(sig)};
            return cache[sig];
        }
                
        for (int op_i=start+1; op_i<end; op_i+=2) {            
            const auto& lhs = getAnswers(s, start, op_i-1);
            const auto& rhs = getAnswers(s, op_i+1, end);
            for (int op_l : lhs) {
                for (int op_r : rhs) {
                    int result = s[op_i] == '*' ? op_l * op_r : op_l + op_r;
                    if (result > 1000) continue;
                    cache[sig].insert(result);
                }
            }
        }
        
        return cache[sig];
    }
    
public:    
    
    // Top down dynamic programming, this gets TLE too.
    int scoreOfStudents(string s, vector<int>& answers) {
        vector<Elem> elems;
        for (int i=0; i<s.size(); i++) {
            char ch = s[i];
            if (ch == '+' || ch == '*') {
                elems.push_back(Elem(ch));
            } else {
                elems.push_back(Elem(stoi(string(1, ch))));
            }
        }   
        
        // The full credit answer.
        int val_5pts = compute(elems, '*', '+');
        
        const auto& all_ans = getAnswers(s, 0, s.size()-1);
        
        int ans=0;
        for (int a : answers) {
            if (a == val_5pts) {
                ans += 5;
            } else if (all_ans.find(a) != all_ans.end()) {
                ans += 2;
            }
        }
        return ans;
    }
    
    // even positions contain numbers, odd positions contain operators
    // Bottom up DP, TLE, because we recompute the same thing repeatedly.
    int scoreOfStudents_(string s, vector<int>& answers) {
        vector<Elem> elems;
        for (int i=0; i<s.size(); i++) {
            char ch = s[i];
            if (ch == '+' || ch == '*') {
                elems.push_back(Elem(ch));
            } else {
                elems.push_back(Elem(stoi(string(1, ch))));
            }
        }   
        
        // The full credit answer.
        int val_5pts = compute(elems, '*', '+');
        
        // dp[sz][start] = {all interpretations of that string}
        unordered_map<int, unordered_map<int, unordered_set<int>>> dp;
        
        // DP base case, sz=1 is just the number
        for (int start=0; start<s.size(); start+=2) {
            dp[1][start] = {stoi(string(1, s[start]))};
        }
                
        for (int sz=3; sz<=s.size(); sz+=2) {
            for (int start=0; start<=s.size()-sz; start += 2) {
                int end = start+sz-1;  // inclusive                
                for (int op_i=start+1; op_i<end; op_i+=2) {
                    int lhs_sz = op_i - start;
                    int rhs_sz = end - op_i;
                    unordered_set<int> lhs = dp[lhs_sz][start];
                    unordered_set<int> rhs = dp[rhs_sz][op_i+1];
                    
                    for (int l_op : lhs) {
                        for (int r_op : rhs) {
                            int result = s[op_i] == '*' ? l_op * r_op : l_op + r_op;
                            if (result > 1000) continue;
                            dp[sz][start].insert(result);
                        }
                    }
                }
            }            
        }
        const auto& all_ans = dp[s.size()][0];
        int ans=0;
        for (int a : answers) {
            if (a == val_5pts) {
                ans += 5;
            } else if (all_ans.find(a) != all_ans.end()) {
                ans += 2;
            }
        }
        return ans;
    }    
};
