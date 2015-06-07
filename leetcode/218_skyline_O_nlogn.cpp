// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Here is my writeup from leetcode
//
// I am using a max-heap to store the height of any buildings currently being processed. 
// I am also processing each point separately (building start and end points).
//
// When a building start point is added, I output the coordinate if it is the highest point currently. 
// I also put the line in the heap.
// 
// When a building end point is added, I remove the line from the heap, and output 
// a coordinate if there is no higher point currently. In this case, the point I output 
// is brought down to the next lower level in the heap (if that makes sense).
// 
// In both cases, I have to do some heap bookkeeping (multiple lines may be deleted 
// during any start/end event). However, total over the entire program each line is added 
// and deleted exactly once, and therefore time to add/delete all lines in heap is O(nlogn) for n lines.
// 
// I also have to do a rather clever sort, on the various points, to get some tricky cases 
// to work properly (e.g. when multiple buildings start and/or end at the same x, but have different heights).
//
// Here is the entire code, which is accepted by OJ:
// 
enum PtType {START=0, END=1};
class Solution {
    struct Point {
        int uid;    //unique id (name of the line)
        int ht;     //height
        int x;      //xcrd
        PtType typ; //is this start of building or end
        Point(int u, int h, int xc, PtType t) : uid(u), ht(h), x(xc), typ(t) {}
    };
    struct CompareHeight {
        bool operator () (const Point& lhs, const Point& rhs) {
            return (lhs.ht < rhs.ht);
        }
    };
    typedef priority_queue<Point, vector<Point>, CompareHeight> MaxHtHeap;
    int IDCTR;
    MaxHtHeap htHeap;
    vector<Point> crds;
    vector<pair<int, int>> results;
    vector<bool> lineExists;
    
    //returns all start and end points, sorted by x-crd, then start/end type, then ht
    vector<Point> createPoints(vector<vector<int>>& buildings) {
        IDCTR=0;
        for (vector<int>& data : buildings) {
            crds.push_back(Point(IDCTR, data[2], data[0], START));
            crds.push_back(Point(IDCTR, data[2], data[1], END));
            IDCTR++;
        }
        std::sort(crds.begin(), crds.end(), [] (const Point& lhs, const Point& rhs) -> bool {
            if (lhs.x != rhs.x) {
                return (lhs.x < rhs.x);     //keep lower x first
            } else if (lhs.typ != rhs.typ) {
                return (lhs.typ < rhs.typ); //keep start before end
            } else {
                if (lhs.typ == START /* same as == rhs.typ*/) {
                    return (lhs.ht > rhs.ht);   //keep higher height first
                } else {
                    return (lhs.ht < rhs.ht);   //keep lower height first
                }
            }
        });
        return crds;
    }

    void adjustHeapBookkeeping() {
        //get topmost non-deleted line in heap
        while (!htHeap.empty() && !lineExists[htHeap.top().uid]) { 
            htHeap.pop();
        }
    }

    void handleBuildingStart(Point& pt) {
        adjustHeapBookkeeping();

        bool tallest = (htHeap.empty()) ? true : (htHeap.top().ht < pt.ht);
        htHeap.push(pt);
        lineExists[pt.uid] = true;
        if (!tallest) return;

        results.push_back(make_pair(pt.x, pt.ht));
        
    }

    void handleBuildingEnd(Point& pt) {
        lineExists[pt.uid] = false;
        adjustHeapBookkeeping();

        int hthp = (htHeap.empty()) ? 0 : (htHeap.top().ht);
        if (hthp >= pt.ht) return;

        results.push_back(make_pair(pt.x, hthp));
    }

public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        if (buildings.empty()) return vector<pair<int, int>>();

        createPoints(buildings);
        lineExists = vector<bool>(IDCTR, false);

        for (Point& pt : crds) {
            if (pt.typ == START) { //starting a building's contour
                handleBuildingStart(pt);
            } else {                //ending a building's contour
                handleBuildingEnd(pt);
            }
        }
        return results;
    }
};
