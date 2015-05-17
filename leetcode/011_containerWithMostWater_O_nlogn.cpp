// Here is my writeup from leetcode.
//
// I haven't looked at the O(n) solution, since I wanted to solve this myself. 
// I came up with a O(nlogn) algorithm, which is better than the O(n^2) naive one. 
// OJ accepted it, so I'm happy. :)
//
// I simply thought that it would be interesting to present, so I'm posting it below.
//
// This solution involves 3 heaps (2 min heaps and 1 max heap): 
// 1st. min heap on height of lines. 
// 2nd. min heap on x-crd of lines. 
// 3rd. max heap on x-crd of lines.
//
// Initially I enter all lines (x-crd, height) into all three heaps. 
// The I start picking from the smallest height line in the htHeap, 
// and find out which line from the min x-crd and max-x-crd heaps still exist. 
// Accordingly, I compute the area with these two candidates, and 
// record maxarea if either are bigger. Then I mark the line deleted.
//
// Even though there are 2 nested while loops, the total runtime 
// is amortized O(nlogn). A simple way to see this is that at most all lines 
// will be deleted from all 3 heaps in the nested while loops before termination. 
// This involves 3 * n * logn = O(nlogn) amortized time. In some iterations only 
// 1 line is deleted, in some iterations many many lines are deleted.

class Solution {
private:
    typedef int Height;
    typedef int XCrd;
    typedef std::pair<XCrd, Height> Line;
    
    class CmpHeight {
    public:
        bool operator() (const Line& lhs, const Line& rhs) {
            return (lhs.second > rhs.second);
        }
    };
    
    class CmpXLesser {
    public:
        bool operator() (const Line& lhs, const Line& rhs) {
            return (lhs.first > rhs.first);
        }
    };
    
    class CmpXGreater {
    public:
        bool operator() (const Line& lhs, const Line& rhs) {
            return (lhs.first < rhs.first);
        }
    };
    
public:
    int maxArea(vector<int>& height) {
        std::priority_queue<Line, vector<Line>, CmpHeight>   htHeap;
        std::priority_queue<Line, vector<Line>, CmpXLesser>  xLoHeap;
        std::priority_queue<Line, vector<Line>, CmpXGreater> xHiHeap;
        
        for(unsigned int i=1; i <= height.size(); i++) {
            Line l = make_pair(i, height[i-1]);
            htHeap.push(l);
            xLoHeap.push(l);
            xHiHeap.push(l);
        }
        
        vector<int> deleted(height.size(), false);
        
        int maxarea=0;
        while (!htHeap.empty()) {
            Line l = htHeap.top(); htHeap.pop(); //get line with lowest height
            int xmin, xmax;                      //min and max x that are not deleted
            
            //get min x crd of line still available
            while (deleted[xLoHeap.top().first-1]) {
                xLoHeap.pop();
            }
            xmin = xLoHeap.top().first;
            
            //get max x crd of line still available
            while (deleted[xHiHeap.top().first-1]) {
                xHiHeap.pop();
            }
            xmax = xHiHeap.top().first;
            
            int area1 = l.second * abs(l.first - xmin);
            int area2 = l.second * abs(l.first - xmax);
            if (area1 > maxarea) maxarea = area1;
            if (area2 > maxarea) maxarea = area2;
            
            deleted[l.first-1] = true;
        }
        
        return maxarea;
    }
};
