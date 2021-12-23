class Solution {
public:
    int minInsertions(string s) {
        int insertions=0;
        int opens=0;
        int surplus_close=0;
        
        for (int i=0; i<s.size(); i++) {
            if (s[i] == '(') {
                if (surplus_close && opens == 0) {
                    insertions++;  // open a new bracket previously
                    insertions++;  // and use this and the parsed bracket to close it
                    surplus_close = 0;
                } else if (surplus_close) {  // dang I need to close this...
                    insertions++;  // close out the previous '(' by pairing a new ')' with the surplus
                    opens--;       // reduce the previous opens, which got matched to our double close
                    surplus_close=0; // double close, so this goes away
                } 
                opens++;  // add this opens
            } else {  // s[i] == ')'
                if (surplus_close == 0) {
                    surplus_close++;                     
                } else if (opens == 0) {  // surplus_close is 1 implied
                    insertions++;  // insert a '(' for the surplus and current close
                    surplus_close = 0;  // consumed the surplus_close
                } else {  // consume an already open and double match with surplus close
                    opens--; 
                    surplus_close=0;
                }  
            }
        }
        
        if (surplus_close != 0) {
            if (opens > 0) {
                insertions++;  // one more ')' with the surplus will...
                opens--;       // ... close out this open
            } else {
                insertions++;  // insert a '('
                insertions++;  // and insert a ')' for the second close
            }
            surplus_close=0;
        }
        
        insertions += 2*opens;  // any leftover opens need 2 closes each
        
        return insertions;
    }
};
