// Solution accepted by OJ!
// Algorithmic complexity = O(n^2)
// 
// Note that the for loops in handleTrioOfCases, and the std::sort and std::unique in 
// recordBestCandidates do NOT operate on n items, but only on ~5 items detailed below.
//
// Dynamic programming algorithm is functionally correct.
// The dyn programming cache stores a vector of rectangles for each coord (r, c)
// The candidate rectangles are those that are the biggest rectangle with that coordinate as lower right coord.
// And all the candidates in the vector have the same area. 
// i.e. they are all the rectangles rooted w/ right corner as (r, c) and having the same max area.
//
// When I look at a new coord (r, c), I look at the following candidates:
//   1. The vector of candidates from (r-1, c)
//   2. The vector of candidates from (r, c-1)
//   3. The vector of candidates from (r-1, c-1)
//   4. The candidate formed by vertical strip from (r, c) of width 1
//   5. The candidate formed by horizontal strip from (r, c) of height 1
//
// For #1, I check to make sure the new bottom edge has 1's, and how far its width is.
// For #2, I check to make sure the new right edge has 1's, and how far its height is.
// For #3, I do both of the above. 
//
// In order to perform the above 3 computations quickly, I pre-compute the 
// widthCache and heightCache, which is the # of 1's upward and leftward from any cell
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <assert.h>
#include <string>

using std::string;
using std::pair;
using std::make_pair;
using std::vector;

class Solution {
    typedef pair<int, int> RectStat; //(height, width) - status of max rectangle at any point

    //dynamic programming cache
    //for each [r][c], store all the candidate rectangles with max area
    vector<vector<vector<RectStat>>> cache;

    //for pre-computing the various upwards and leftwards values
    vector<vector<int>> heightCache;
    vector<vector<int>> widthCache;

    //checks upwards from current cell, [r, r-h+1]
    int checkUpwards(vector<vector<char>>& matrix, int r, int c, int h) {
        if (h <= 0) return 0;
        if (heightCache[r][c] >= h) return h;
        return heightCache[r][c];
    }

    //checks leftwards from current cell, [c, c-w+1]
    int checkLeftwards(vector<vector<char>>& matrix, int r, int c, int w) {
        if (w <= 0) return 0;
        if (widthCache[r][c] >= w) return w;
        return widthCache[r][c];
    }

    //picks best rectangles, and updates maxarea if needed
    void recordBestCandidates(int& maxarea, vector<RectStat>& answers, vector<RectStat>& candidates) {
        if (candidates.empty()) return;

        vector<pair<int, RectStat>> cands;

        //get areas from candidates
        std::transform(candidates.begin(), candidates.end(), back_inserter(cands), [] (const RectStat& rs) -> pair<int, RectStat> {
            return (make_pair(rs.first * rs.second, rs));
        });

        //remove duplicates of same candidates
        std::sort(cands.begin(), cands.end(), [] (const pair<int, RectStat>& lhs, const pair<int, RectStat>& rhs) -> bool {
            if  (lhs.second.first != rhs.second.first) {
                return (lhs.second.first > rhs.second.first);
            } else {
                return (lhs.second.second > rhs.second.second);
            }
        });
        auto it = std::unique(cands.begin(), cands.end(), [] (const pair<int, RectStat>& lhs, const pair<int, RectStat>& rhs) -> bool {
            return (lhs.first == rhs.first && lhs.second == rhs.second);
        });
        cands.erase(it, cands.end());

        //sort candidates by maxarea, and take only those that have same largest area
        std::sort(cands.begin(), cands.end(), [] (const pair<int, RectStat>& lhs, const pair<int, RectStat>& rhs) -> bool {
            return (lhs.first > rhs.first);
        });
        int localmax = cands[0].first; //max area of these cands
        if (localmax > maxarea) maxarea = localmax;
        for (int i=0; i<cands.size(); i++) {
            if (cands[i].first < localmax) break;
            answers.push_back(cands[i].second);
        }
    }

    void handleTrioOfCases(int& maxarea, vector<pair<int, int>>& answers, vector<vector<char>>& matrix, int r, int c,  
                           const vector<RectStat>& rm1cm1v, const vector<RectStat>& rcm1v, const vector<RectStat>& rm1cv) {
        vector<RectStat> candidates;
        for (const RectStat& readrm1cm1 : rm1cm1v) { //recurrence for [r-1][c-1]
            if (readrm1cm1.first == 0 || readrm1cm1.second == 0) continue;
            int rm1cm1Vert  = checkUpwards(matrix,   r-1, c,   readrm1cm1.first);
            int rm1cm1Horiz = checkLeftwards(matrix, r,   c-1, readrm1cm1.second);
            if (rm1cm1Vert == 0 || rm1cm1Horiz == 0) continue;
            candidates.push_back(make_pair(1 + rm1cm1Vert, 1 + rm1cm1Horiz));
        }
        for (const RectStat& readrm1c : rm1cv) {    //recurrence for [r-1][c]
            if (readrm1c.first == 0 || readrm1c.second == 0) continue;
            int rm1c        = checkLeftwards(matrix, r,   c,   readrm1c.second);
            candidates.push_back(make_pair(1 + readrm1c.first, rm1c));
        }
        for (const RectStat& readrcm1 : rcm1v) {    //recurrence for [r][c-1]
            if (readrcm1.first == 0 || readrcm1.second == 0) continue;
            int rcm1        = checkUpwards(matrix,   r,   c,   readrcm1.first);
            candidates.push_back(make_pair(rcm1, 1 + readrcm1.second));
        }
        candidates.push_back(make_pair(1, widthCache[r][c])); //max horizontal strip, rooted at [r][c], height 1
        candidates.push_back(make_pair(heightCache[r][c], 1));//max vertical strip, rooted at [r][c], width 1
        recordBestCandidates(maxarea, answers, candidates);
    }

    void precomputeHeightWidthCaches(vector<vector<char>>& matrix, int nrows, int ncols) {
        heightCache = vector<vector<int>>(nrows, vector<int>(ncols, 0));
        widthCache = vector<vector<int>>(nrows, vector<int>(ncols, 0));

        for (int r=0; r<nrows; r++) {
            int runningtotal=0;
            for (int c=0; c<ncols; c++) {
                if (matrix[r][c] == '1') {
                    runningtotal += 1;
                } else {
                    runningtotal = 0;
                }
                widthCache[r][c] = runningtotal;
            }
        }
        for (int c=0; c<ncols; c++) {
            int runningtotal=0;
            for (int r=0; r<nrows; r++) {
                if (matrix[r][c] == '1') {
                    runningtotal += 1;
                } else {
                    runningtotal = 0;
                }
                heightCache[r][c] = runningtotal;
            }
        }
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
        const int nrows = matrix.size();
        const int ncols = matrix[0].size();

        precomputeHeightWidthCaches(matrix, nrows, ncols);

        //dynamic programming cache (init everything to no-rectangle)
        cache = vector<vector<vector<RectStat>>>(nrows, vector<vector<RectStat>>(ncols, vector<RectStat>()));

        //base cases
        if (matrix[0][0] == '1') {
            cache[0][0].push_back(make_pair(1, 1));
        } else {
            cache[0][0].push_back(make_pair(0, 0));        
        }
        int maxarea = matrix[0][0] == '1' ? 1 : 0;
        for (int r=1; r<nrows; r++) {
            if (matrix[r][0] == '0') {
                cache[r][0].push_back(make_pair(0, 0));
                continue;
            }
            int height = 1 + cache[r-1][0][0].first;
            cache[r][0].push_back(make_pair(height, 1));
            if (height > maxarea) maxarea = height;
        }
        for (int c=1; c<ncols; c++) {
            if (matrix[0][c] == '0') {
                cache[0][c].push_back(make_pair(0, 0));
                continue;
            }
            int width = 1 + cache[0][c-1][0].second;
            cache[0][c].push_back(make_pair(1, width));
            if (width > maxarea) maxarea = width;
        }

        //recurrence
        for (int r=1; r<nrows; r++) {
            for (int c=1; c<ncols; c++) {
                if (matrix[r][c] == '0') {
                    cache[r][c].push_back(make_pair(0, 0));
                    continue;
                }
                vector<pair<int, int>> answers;
                handleTrioOfCases(maxarea, answers, matrix, r, c, cache[r-1][c-1], cache[r][c-1], cache[r-1][c]);
                cache[r][c] = answers;
            }
        }

        return maxarea;
    }
};

vector<vector<char>> convMatrix(const vector<string>& mat) {
    vector<vector<char>> retval = vector<vector<char>>(mat.size(), vector<char>(mat[0].size(), '0'));
    for (int r=0; r<mat.size(); r++) {
        for (int c=0; c<mat[0].size(); c++) {
            retval[r][c] = mat[r][c];
        }
    }
    return retval;
}

int main() 
{
    vector<vector<char>> matrix_small = {{'0', '0', '0', '1', '0', '1', '0'},
                                         {'0', '1', '0', '0', '0', '0', '0'},
                                         {'0', '1', '0', '1', '0', '0', '1'},
                                         {'0', '0', '1', '1', '0', '0', '1'},
                                         {'1', '1', '1', '1', '1', '1', '0'},
                                         {'1', '0', '0', '1', '0', '1', '1'},
                                         {'0', '1', '0', '0', '1', '0', '1'},
                                         {'1', '1', '0', '1', '1', '1', '0'},
                                         {'1', '0', '1', '0', '1', '0', '1'},
                                         {'1', '1', '1', '0', '0', '0', '0'}};
    vector<string> matrix_str = {
        "1111111111111101001111111100111011111111",
        "1111011011111111101101111101111111111111",
        "0111101011111101101101101111111111111111",
        "0101101011111111111101111111010110111111",
        "1111111111110111110110010111111111111111",
        "1111111110110101111111111101011111101111",
        "0110110101110011111111111111110111110101",
        "0111111111111100111111100110011011010101",
        "1111011110111111111011011011110101101011",
        "1111111110111111111101101101110111101111",
        "1110110011111111111100111111111111111111",
        "1011111110111101111001110111111111111111",
        "0110111111111111101111110111011111011111",
        "1111111111111111011111111111110111111011",
        "1111100111111110101100111111111111101111",
        "1111101111111110111111011111111111011111",
        "1111101111111111111111011001111110011111",
        "1111110111111111011111111111110111110111",
        "1011111111111111010111110010111110111111",
        "1111110011111111111110111111111111111011",
        "1111111111111111110111011111011111011011",
        "1100011011111111111111011111011111111111",
        "1111101011111111111101100101110011111111",
        "1110010111111111111011011110111101111101",
        "1111111111111101101111111111101111111111",
        "1111111011111101111011111111111110111111",
        "1110011111111110111011111111110111110111",
        "1111111111111100111111010111111111110111",
        "1111111111111111111111000111111111011101",
        "1111110111111111111111111101100111011011",
        "1111011011111101101101111110111111101111",
        "1111111111011111111111111111111111111111",
        "1111111111111111111111111111111111111111",
        "1100011111111110111111111111101111111011",
        "1111101111111101111010111111111111111111",
        "0111111111110011111111110101011011111111",
        "1011011111101111111111101111111111110011",
        "1010111111111111111111111111111110011111",
        "0111101111011111111111111111110111111111",
        "0111111011111111011101111011101111111111",
        "0111111111110101111011111101011001111011",
        "1111111111111011110111111101111111101110",
        "1111101111111100111111111110111111001111",
        "1101101111110101111101111111100111010100",
        "0110111111100111110010111110111011011101"
    };
    vector<string> matrix_med = {
        "0110111111111111110",
        "1011111111111111111",
        "1101111111110111111",
        "1111111111111011111",
        "1111111111111101111",
        "1110111011111111101",
        "1011111111111101111",
        "1111111111111110110",
        "0011111111111110111",
        "1101111111011111111",
        "1111111110111111111",
        "0110111011111111111",
        "1111011111111101111",
        "1111111111111111111",
        "1111111111111111111",
        "1111111111111111101",
        "1111111101101101111",
        "1111110111111110111"
    };
    vector<string> matrix_tiny = {
        "11111",
        "11111",
        "11101",
        "11101",
        "11011",
    };
    Solution sln;
    vector<vector<char>> matrix = convMatrix(matrix_med);
    int ans = sln.maximalRectangle(matrix);
    std::cout << "Answer = " << ans << std::endl;
}


