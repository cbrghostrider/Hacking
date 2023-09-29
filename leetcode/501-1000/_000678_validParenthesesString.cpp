// It is easy to keep track of num_opens and num_stars as we parse, 
// and use them (preferentially to opens) to match against any closes.
// The problem happens at the end, when we have some non-zero amount
// of num_opens and num_stars.
// 
// e.g. consider these two end states:
// "***(((" and "(((***"
// both end up with 3 num_stars and 3 num_opens.
// however only one of them is valid.
//
// An easy way to get around this is as follows:
// Do only the initial matching (opens/stars against closes)
// This tells you if the closes obey the rules.
// 
// Now replace each open with a close and vice versa, and reverse the string.
// Then run it through the same algorithm!
// This tells you if the opens (which are now closes) also obey the rules!
// The stars of course always obey the rules, since they can be anything (including empty).
class Solution {
    // checks if all closes match opens or stars
    // DOES NOT CHECK pending stars/opens remaining at the end
    bool checkValidity(string s) {
        int num_opens=0, num_stars=0;
        for (char ch : s) {
            if (ch == '*') {
                num_stars++;
            } else if (ch == '(') {
                num_opens++;
            } else {  // ch == ')'
                if (num_opens > 0) {num_opens--;}
                else if (num_stars > 0) {num_stars--;}
                else return false;
            }
        }
        return true;
    }
public:
    bool checkValidString(string s) {
        bool check_close = checkValidity(s);
        for (char& ch : s) {
            if (ch == '(') {ch = ')';}
            else if (ch == ')') {ch = '(';}
        }
        std::reverse(s.begin(), s.end());
        bool check_open = checkValidity(s);
        return check_close && check_open;
    }
};
