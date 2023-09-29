class Logger {
    std::unordered_map<string, int> last_print;
public:
    Logger() {}      
    
    bool shouldPrintMessage(int timestamp, string message) {
        if (last_print.find(message) != last_print.end() && 
            last_print[message] + 10 > timestamp) {
            return false;
        }
        last_print[message] = timestamp;
        return true;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
