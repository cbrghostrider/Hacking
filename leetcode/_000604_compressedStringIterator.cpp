class StringIterator {
    string all_letters;
    string compressed;
    
    // To track iterator.
    char letter = ' ';
    int remaining = 0;
    size_t next_position = 0;
public:
    StringIterator(string compressedString) {
        for (char c = 'a'; c<='z'; c++) {
            all_letters.push_back(c);
        }
        for (char c = 'A'; c<='Z'; c++) {
            all_letters.push_back(c);
        }
        compressed = compressedString;
    }
    
    char next() {
        if (!hasNext()) return ' ';
        remaining--;
        return letter;
    }
    
    // also does the heavy lifting to maintain the iterator
    bool hasNext() {
        if (remaining != 0) return true;
        if (remaining == 0 && next_position == string::npos) return false;
        
        letter = compressed[next_position];
        size_t digit_start = next_position+1;
        next_position = compressed.find_first_of(all_letters, digit_start+1);
        
        size_t digit_str_length = (next_position == string::npos ? compressed.size() : next_position) - digit_start;
        string digit_str = compressed.substr(digit_start, digit_str_length);
        remaining = std::stoi(digit_str);
        
        return true;
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
