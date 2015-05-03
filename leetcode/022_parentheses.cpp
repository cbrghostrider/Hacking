class Solution {
public:
    vector<string> generateParenthesisPrime(vector<string> soFar, int nopen, int nclose, const int n) {
        if (nopen == n && nclose == n) {
            return soFar; //recursion termination
        }
        
        vector<string> retval;
        vector<string> moreOpen  = soFar;
        vector<string> moreClose = soFar;
        
        if (nopen < n) {
            for_each(moreOpen.begin(), moreOpen.end(), [] (string& str) -> void {
                str += "(";
            });
            moreOpen = generateParenthesisPrime(moreOpen, nopen+1, nclose, n);
            retval.insert(retval.end(), moreOpen.begin(),  moreOpen.end());
        }
        
        if (nclose < nopen) {
            for_each(moreClose.begin(), moreClose.end(), [] (string& str) -> void {
                str += ")";
            });
            moreClose = generateParenthesisPrime(moreClose, nopen, nclose+1, n);
            retval.insert(retval.end(), moreClose.begin(), moreClose.end());
        }
        
        return retval;
    }
    
    vector<string> generateParenthesis(int n) {
        vector<string> init;
        init.push_back(string(""));
        return(generateParenthesisPrime(init, 0, 0, n));
    }
};
