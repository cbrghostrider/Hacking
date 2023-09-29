class Solution {
public:
    
    int wordsTyping_(vector<string>& sentence, int rows, int cols, int& w_ptr) {
        int scount=0;
        int r=0, c=0;        
        
        while (r < rows && c + sentence[w_ptr].size() <= cols) {
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
    
    
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        unordered_map<int, int> counts;
        unordered_map<int, int> next_wptr;
        
        int scount=0;
        int w_ptr=0;
        
        for (int r=0; r<rows; r++) {
            if (counts.find(w_ptr) != counts.end()) {
                scount += counts[w_ptr];
                w_ptr = next_wptr[w_ptr];
                continue;
            }
            
            int nwptr = w_ptr;
            int my_count = wordsTyping_(sentence, 1, cols, nwptr);
            
            counts[w_ptr] = my_count;
            next_wptr[w_ptr] = nwptr;
            scount += my_count;
            w_ptr = nwptr;
        }  
        return scount;
    }
};
