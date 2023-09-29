class Solution {
public:
    // O(rows * cols) time, O(1) space.
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int scount=0;
        int r=0, c=0;
        int w_ptr=0;
        
        
        while (r < rows && c < cols) {
            int wsize = sentence[w_ptr].size();
            
            if (c + wsize > cols) {
                r++; c=0;
                continue;
            }
            
            w_ptr++;
            c += wsize;
            
            c++;  // add space
            if (c >= cols) {  
                r++; c=0;
            }
            
            if (w_ptr == sentence.size()) {
                w_ptr = 0;
                scount++;
            }
        }
        return scount;
    }
} 
