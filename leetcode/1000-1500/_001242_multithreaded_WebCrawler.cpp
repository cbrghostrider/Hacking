/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
class Solution {
    unordered_set<string> crawled;
    std::mutex mut;
    
    bool isCrawled(const string& check) {
        std::lock_guard<std::mutex> lck(mut);
        return (crawled.find(check) != crawled.end());
    }
    
    void setCrawled(const string& check) {
        std::lock_guard<std::mutex> lck(mut);
        crawled.insert(check);
    }
    
    string getHostname(const string& url) {
        const int start = 7;  // skip initial "http://"
        int pos = url.find_first_of("/", start);
        int len = pos == string::npos ? url.size()-start : pos-start;
        return url.substr(start, len);
    }

public:
    
    void crawlRecurse(HtmlParser& htmlparser, const string& surl, const string& hostname) {
        
        vector<std::thread> my_threads;
        vector<string> urls = htmlparser.getUrls(surl);
        for (const string& url : urls) {
            if (getHostname(url) != hostname) continue;
            if (isCrawled(url)) continue;
            setCrawled(url);
            std::thread th = std::thread(&Solution::crawlRecurse, 
                                         this, std::ref(htmlparser), std::ref(url),
                                         std::ref(hostname));
            my_threads.push_back(std::move(th));
            
        }
        
        for (int i=0; i<my_threads.size(); i++) {
            my_threads[i].join();
        }
    }
    

    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        const string hostname = getHostname(startUrl);
        setCrawled(startUrl);
        
        std::thread thread(&Solution::crawlRecurse, this, 
                           std::ref(htmlParser), std::ref(startUrl), std::ref(hostname));
        
        thread.join();
        vector<string> ans;
        ans.insert(ans.end(), crawled.begin(), crawled.end());
        return ans;
    }
};
