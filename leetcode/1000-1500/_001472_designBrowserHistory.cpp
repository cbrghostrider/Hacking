class BrowserHistory {
    vector<string> history;
    int cur=0;
public:
    BrowserHistory(string homepage) {
        history.push_back(homepage);
        cur=0;
    }
    
    void visit(string url) {
        while (!history.empty() && (int)history.size()-1 > cur) {history.pop_back();}
        history.push_back(url);
        cur = history.size()-1;
    }
    
    string back(int steps) {
        cur=std::max(cur-steps, 0);
        return history[cur];
    }
    
    string forward(int steps) {
        cur = std::min(cur+steps, (int)history.size()-1);        
        return history[cur];
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
