class Solution {
public:
    string reformatNumber(string number) {
        string temp, ans;
        for (char ch : number) {if (ch != ' ' && ch != '-') {temp.push_back(ch);}}
        int quot = temp.size()/3;
        int rem = temp.size()%3;
        if (rem == 1 && quot > 0) {
            quot--;
            rem += 3;
        }
        for (int i=0; i<quot; i++) {
            ans += temp.substr(i*3, 3) + "-";
        }
        if (rem == 0) {ans.pop_back();}
        if (rem == 1) {ans.push_back(temp.back());}
        if (rem == 2) {ans.push_back(temp[temp.size()-2]); ans.push_back(temp.back());}
        if (rem == 4) {
            ans.push_back(temp[temp.size()-4]); ans.push_back(temp[temp.size()-3]);
            ans.push_back('-');
            ans.push_back(temp[temp.size()-2]); ans.push_back(temp[temp.size()-1]);
        }
        return ans;
    }
};
