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
    
    string getHostname(const string& url) {
        const int start = 7;  // skip initial "http://"
        int pos = url.find_first_of("/", start);
        int len = pos == string::npos ? url.size()-start : pos-start;
        return url.substr(start, len);
    }
    
    void crawlRecurse(HtmlParser& htmlparser, const string& surl, const string& hostname) {
        if (crawled.find(surl) != crawled.end()) return;
        crawled.insert(surl);
        
        vector<string> urls = htmlparser.getUrls(surl);
        for (const string& url : urls) {
            if (getHostname(url) != hostname) continue;
            if (crawled.find(url) != crawled.end()) continue;
            crawlRecurse(htmlparser, url, hostname);
        }
    }
    
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        const string hostname = getHostname(startUrl);
        crawlRecurse(htmlParser, startUrl, hostname);
        vector<string> ans;
        ans.insert(ans.end(), crawled.begin(), crawled.end());
        return ans;
    }
};
