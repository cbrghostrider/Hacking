#include <cctype>

class Solution {
enum class Token {
    ELEMENT=0,
    COUNT=1,
    BRACKET_OPEN=2,
    BRACKET_CLOSE=3
};

struct TokenInfo {
    Token token;
    int count=0;
    string element;
};

typedef map<string, int> Answer_t;

Answer_t add(const Answer_t& t1, const Answer_t& t2) {
    Answer_t ans = t1;
    for (const auto& kv2 : t2) {
        if (t1.find(kv2.first) != t1.end()) {
            ans[kv2.first] = t1.at(kv2.first) + kv2.second;
        } else {
            ans[kv2.first] = kv2.second;
        }
    }
    return ans;
}

void multiply(Answer_t& t1, int count) {
    for (auto& kv : t1) {
        kv.second = kv.second * count;
    }
}

const string lletters = "abcdefghijklmnopqrstuvwxyz";

vector<TokenInfo> tokenize(const string& formula) {    
    auto illformed = [](const string& str, int index) {
        printf("Tokenizer: Ill-formed character at index %d: %c (string: %s)\n", index, str[index], str.c_str());
        exit(1);
    };
    vector<TokenInfo> tokens;
    int ind=0;
    while (ind < formula.size()) {
        if (formula[ind] == '(' || formula[ind] == ')') {
            Token ttype = (formula[ind] == '(' ? Token::BRACKET_OPEN : Token::BRACKET_CLOSE);
            tokens.push_back({ttype, 0, ""});
            ind++;            
        } else if (std::isdigit(formula[ind])) {
            size_t nind = formula.find_first_not_of("0123456789", ind);
            if (nind == std::string::npos) { nind = formula.size(); }
            int count = std::stoi(formula.substr(ind, nind - ind));
            tokens.push_back({Token::COUNT, count, ""});
            ind = nind;
        } else if (std::isupper(formula[ind])) {
            string element = std::string(1, formula[ind]);
            ind++;  // consume the uppercase character
            size_t nind = formula.find_first_not_of(lletters, ind);
            if (nind == std::string::npos) { nind = formula.size(); }
            element += formula.substr(ind, nind - ind);
            tokens.push_back({Token::ELEMENT, 0, element});
            ind = nind;            
        } else {
            illformed(formula, ind);
        }
    }
    return tokens;
}

// Can be called recursively.
// Computes the answer for a single sequence of tokens (possibly within open/close brackets followed by the count).
// ind is the next token TO BE CONSUMED (or past the end if done).
Answer_t compute(const vector<TokenInfo>& tokens, int& ind) {    
    if (ind >= tokens.size()) return {};
    Answer_t my_ans;

    if (tokens[ind].token == Token::BRACKET_OPEN) {
        ind++;  // consume the open bracket.

        my_ans = compute(tokens, ind);
    
        if (ind >= tokens.size() || tokens[ind].token != Token::BRACKET_CLOSE) {
            // Ill-formed!
            printf("Ill formed token at index %d: %d\n", ind, tokens[ind].token);
            exit(1);
        }
        ind++; // consume the close bracket.

    } else if (tokens[ind].token == Token::ELEMENT) {
        my_ans[tokens[ind].element] = 1;
        ind++;  // consume the element
    } else if (tokens[ind].token == Token::BRACKET_CLOSE) {
        // return what we have without consuming anything; the caller will consume the bracket close.
        return my_ans;
    }

    if (ind < tokens.size() && tokens[ind].token == Token::COUNT) {
        multiply(my_ans, tokens[ind].count);
        ind++;  // consume the count
    } 

    // Deal with concatenation.
    Answer_t rec = compute(tokens, ind);
    my_ans = add(my_ans, rec);
    return my_ans;
}

// Takes the answer, and turns it into the form required.
string make_canonical(const Answer_t& answer) {
    string ret;
    for (const auto& kv : answer) {
        ret += kv.first;
        if (kv.second > 1) {
            ret += std::to_string(kv.second);
        }
    }
    return ret;
}

public:
    string countOfAtoms(string formula) {        
        vector<TokenInfo> tokens = tokenize(formula);
        int ind=0;
        Answer_t ans = compute(tokens, ind);
        string ansstr = make_canonical(ans);
        return ansstr;
    }
};
