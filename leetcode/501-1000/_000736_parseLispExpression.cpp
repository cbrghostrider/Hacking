class Solution {
enum class Token {
    VARIABLE=0,
    VALUE=1,    
    BRACKET_OPEN=2,
    BRACKET_CLOSE=3,
    MULTIPLY=4,
    ADD=5,
    LET=6
};

struct TokenInfo {
    Token token;
    int value=0;
    string variable;    
};

const string lletters = "abcdefghijklmnopqrstuvwxyz";
const string digits = "0123456789";

vector<TokenInfo> tokenize(const string& expression) {    
    auto illformed = [](const string& str, int index) {
        printf("Tokenizer: Ill-formed character at index %d: %c (string: %s)\n", index, str[index], str.c_str());
        exit(1);
    };
    vector<TokenInfo> tokens;
    int ind=0;    
    while (ind < expression.size()) {
        if (expression[ind] == '(' || expression[ind] == ')') {
            Token ttype = (expression[ind] == '(' ? Token::BRACKET_OPEN : Token::BRACKET_CLOSE);            
            tokens.push_back({ttype, 0, ""});
            ind++;            
        } else if(ind+3 <= expression.size() && expression.substr(ind, 3) == "let") {
            tokens.push_back({Token::LET, 0, ""});
            ind += 3;
        } else if(ind+3 <= expression.size() && expression.substr(ind, 3) == "add") {
            tokens.push_back({Token::ADD, 0, ""});
            ind += 3;
        } else if(ind+4 <= expression.size() && expression.substr(ind, 4) == "mult") {
            tokens.push_back({Token::MULTIPLY, 0, ""});
            ind += 4;
        } else if (std::isdigit(expression[ind]) || expression[ind] == '-') {
            bool minus = false;
            if (expression[ind] == '-') {
                minus = true;
                ind++;  // consume the minus
            }
            size_t nind = expression.find_first_not_of("0123456789", ind);
            if (nind == std::string::npos) { nind = expression.size(); }
            int value = std::stoi(expression.substr(ind, nind - ind));
            if (minus) {value *= -1;}
            tokens.push_back({Token::VALUE, value, ""});
            ind = nind;
        } else if (std::islower(expression[ind])) {            
            size_t nind = expression.find_first_not_of(lletters + digits, ind);
            if (nind == std::string::npos) { nind = expression.size(); }
            string variable = expression.substr(ind, nind - ind);
            tokens.push_back({Token::VARIABLE, 0, variable});
            ind = nind;            
        } else if (std::isspace(expression[ind])) {
            ind++;  // consume the space
        } else {
            illformed(expression, ind);
        }
    }
    return tokens;
}

// Outer key: Variable name.
// Inner key: nesting level.
// Value: value of that variable at that nesting level.
map<string, unordered_map<int, int>> symbol_table;
int curr_nesting=0;

bool lookup_symbol_table(const string& var, int& ret) {
    auto it = symbol_table.find(var);
    if (it == symbol_table.end()) return false;
    for (int nest=curr_nesting; nest >=0; nest--) {
        auto it2 = it->second.find(nest);
        if (it2 != it->second.end()) {
            ret = it2->second;
            return true;
        }
    }
    return false;
}

void update_symbol_table(const string& var, int value) {
    symbol_table[var][curr_nesting] = value;
}

void eliminate_symbols(int nest) {
    for (auto& kv : symbol_table) {
        if (kv.second.find(nest) != kv.second.end()) {
            kv.second.erase(nest);
        }
    }
}

// Will be recursive.
// Called always with a bracket token at the current index.
// Will evaluate until this same nesting level is reached on the close bracket, and return the results.
int evaluate(const vector<TokenInfo>& tokens, int& index) {
    auto illformed = [](const vector<TokenInfo>& tokens, int index) {
        printf("evaluate: Ill-formed tokens: Index %d -> Token %d\n", index, (int)(tokens[index].token));
        exit(1);
    };

    int ret=0;

    // We might be evaluating just a variable, based on past lets/computations.
    if (tokens[index].token == Token::VARIABLE) {
        const string& var = tokens[index].variable;
        if (!lookup_symbol_table(var, ret)) {
            printf("evaluate: Symbol table missing info for var %s (curr_nesting: %d)\n", var.c_str(), curr_nesting);
            exit(1);
        }
        index++;
        return ret;
    }

    // We might be evaluating just a constant.
    if (tokens[index].token == Token::VALUE) {
        ret = tokens[index].value;
        index++;
        return ret;
    }    
    

    if (tokens[index].token != Token::BRACKET_OPEN) {illformed(tokens, index);}
    index++;
    curr_nesting++;

    if (tokens[index].token == Token::MULTIPLY) {
        index++;
        int op1 = evaluate(tokens, index);
        int op2 = evaluate(tokens, index);
        ret = op1 * op2;
    } else if (tokens[index].token == Token::ADD) {
        index++;
        int op1 = evaluate(tokens, index);
        int op2 = evaluate(tokens, index);
        ret = op1 + op2;
    } else if (tokens[index].token == Token::LET) {
        index++;
        // first get all the let assignments.
        while (index < tokens.size() && tokens[index].token == Token::VARIABLE && 
               index < tokens.size()-1 && tokens[index+1].token != Token::BRACKET_CLOSE) {
            string var_name = tokens[index].variable;
            index++;
            int val = evaluate(tokens, index);
            update_symbol_table(var_name, val);
        }
        // and then evaluate the expression that follows
        ret = evaluate(tokens, index);
    } else {
        illformed(tokens, index);
    }

    // Once done, consume the close, and eliminate needed scoped variables.
    if (tokens[index].token != Token::BRACKET_CLOSE) {illformed(tokens, index);}
    eliminate_symbols(curr_nesting);
    curr_nesting--;
    index++;

    return ret;
}

public:
    int evaluate(string expression) {
        vector<TokenInfo> tokens = tokenize(expression);
        int index=0;
        int ret = evaluate(tokens, index);
        return ret;
    }
};
