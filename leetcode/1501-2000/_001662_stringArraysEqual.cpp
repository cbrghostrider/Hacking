class Solution {
    class StringCont {
     public:
        StringCont(const vector<string>& ip) : words(ip) {}
        bool hasNext() {
            if (word_ptr >= words.size() || 
                (word_ptr == words.size() && letter_ptr >= words.back().size())) {
                return false;
            }
            if (letter_ptr >= words[word_ptr].size()) {
                word_ptr++;
                letter_ptr = 0;
            }
            return true;
        }    
        char next() {
            if (!hasNext()) return ' ';
            char ret = words[word_ptr][letter_ptr++];
            hasNext();  // bookkeeping
            return ret;
        }
     private:
        const vector<string>& words;
        // Records next position to return.
        int word_ptr = 0;
        int letter_ptr = 0;
    };
public:
    // O(n) time, O(1) space.
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        StringCont ss1(word1), ss2(word2);
        while (ss1.hasNext() && ss2.hasNext()) {
            if (ss1.next() != ss2.next()) return false;
        }
        return (ss1.hasNext() == ss2.hasNext());
    }
};
