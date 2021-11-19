class Solution {
    class Decrypter {
      public:
        Decrypter(const string& s) : str(s) {}
        bool hasNext() { return (ptr < str.size()); }
        char next() {
            if (!hasNext()) return ' ';
            // str is guaranteed to be a well encrypted string.
            bool is_ext = false;
            if (str[ptr] == '1' || str[ptr] == '2') {
                if (ptr + 2 < str.size() && str[ptr+2] == '#') {
                    is_ext = true;
                }
            }
            int len = (is_ext ? 2 : 1);
            string ss = str.substr(ptr, len);
            ptr += len;
            if (is_ext) {ptr += 1;}  // # sign
            return to_char[ss];
        }
      private:
        unordered_map<string, char> to_char = {
            {"1", 'a'},  {"2", 'b'},  {"3", 'c'},  {"4", 'd'},  {"5", 'e'},
            {"6", 'f'},  {"7", 'g'},  {"8", 'h'},  {"9", 'i'},  {"10", 'j'},
            {"11", 'k'}, {"12", 'l'}, {"13", 'm'}, {"14", 'n'}, {"15", 'o'},
            {"16", 'p'}, {"17", 'q'}, {"18", 'r'}, {"19", 's'}, {"20", 't'},
            {"21", 'u'}, {"22", 'v'}, {"23", 'w'}, {"24", 'x'}, {"25", 'y'},
            {"26", 'z'}
        };
        string str;
        int ptr=0;
    };
public:
    string freqAlphabets(string s) {
        Decrypter dc(s);
        string ans;
        while (dc.hasNext()) {
            ans.push_back(dc.next());
        }
        return ans;
    }
};
