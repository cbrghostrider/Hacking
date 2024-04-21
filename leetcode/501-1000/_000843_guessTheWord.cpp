/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
 
class Solution {

// We keep a probability for each character, depending on previous guesses.
struct ProbInfo {
    double prob=0.0;  // The current probability.
    int times=0;      // How many times we re-computed the probability so far.
};

// The probabilities.
unordered_map<char, ProbInfo> probabilities;

double get_probability(const string& word) {
    double prob=0.0;      
    for (char ch : word) {
        prob += probabilities[ch].prob;
    }
    prob /= 6;
    return prob;
}

void update_probability(char ch, double new_prob) {
    if (probabilities[ch].times == 0) {
        probabilities[ch].times = 1;
        probabilities[ch].prob = new_prob;
        return;
    } 
    // The probability is only updated if it gets better, not worse!!!
    if (probabilities[ch].prob > new_prob) {
        return;
    } 
    probabilities[ch].prob = new_prob;
    probabilities[ch].times++;
}

int num_uniques(const string& word) {
    unordered_set<char> uniques;
    for (char ch : word) {uniques.insert(ch);}
    return uniques.size();
}

void order_by_probabilities(vector<string>& wordlist) {
    std::sort(wordlist.begin(), wordlist.end(), [this](const string& lhs, const string& rhs) -> bool {
        double plhs = get_probability(lhs);
        double prhs = get_probability(rhs);
        int luniq = num_uniques(lhs);
        int runiq = num_uniques(rhs);
        if (plhs != prhs) return plhs > prhs;
        if (luniq != runiq) return luniq < runiq;
        return lhs < rhs;  // deterministic tiebreaker
    });
}

// value is the value returned by master.
void update_probabilities_word(const string& word, int value) {        
    if (value == -1 || value > 6) return;  // invalid    
    double prob = (double)value / 6.0;
    // Only update non-unique letters once.
    set<char> uniques;
    for (char ch : word) {uniques.insert(ch);}
    for (char ch : uniques) {update_probability(ch, prob);}
}

// A skipset is updated when we get 0 matches.
// This tells us the specified letters are DEFINITELY NOT in the specified positions
// (Note the letters can't be filtered out completely as they can be in other positions).
// This helps us filter the list further.
unordered_map<char, unordered_set<int>> skipset;

// Takes in a sorted listed, based on probabilities of each word.
string next_guess(const vector<string>& words) {
    if (words.size() >= 1) return words[0];    
    return "debugg";
}

// Returns true if position of chars in word vs. guess have at least value exact matches.
// If any letter matches the position in its skipset, then we skip the word entirely.
bool should_keep_word(const string& guess, const string& word, int value) {        
    for (int i=0; i<6; i++) {
        if (skipset[word[i]].find(i) != skipset[word[i]].end()) {            
            return false;
        }
    }

    int m=0;
    for (int i=0; i<6; i++) {
        if (guess[i] == word[i]) m++;
    }
    return (m >= value);
}

// Keep only those words with letters that guess has.
vector<string> filter_list(const vector<string>& words, const string& guess, int value) {    
    // Update the skipset.
    if (value == 0) {
        for (int i=0; i<6; i++) {
            skipset[guess[i]].insert(i);
        }
    }

    vector<string> new_list;

    for (const string& word : words) {
        // Skip the word that we have guessed before.
        if (word == guess) {            
            continue;
        }

        // Only keep those words that have "value" number of exact matches with guess.
        // Also perform skipset testing.
        if (should_keep_word(guess, word, value)) {            
            new_list.push_back(word);
        }

    }
    return new_list;
}

public:
    void findSecretWord(vector<string>& words, Master& master) {
        const int MAX_GUESSES = 30;   // from the problem constraints.
        for (int i=0; i<MAX_GUESSES; i++) {        
            order_by_probabilities(words);                 
            string new_guess = next_guess(words);            
            int val = master.guess(new_guess);
            // printf("Guessing %s; got matches %d\n", new_guess.c_str(), val);
            if (val == 6) return;  // found the secret!
            words = filter_list(words, new_guess, val);
            update_probabilities_word(new_guess, val);                       
        }
    }
};
