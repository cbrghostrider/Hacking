// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/////////////////////////////////////////////////////////////////////////
//        Section for quick sort
/////////////////////////////////////////////////////////////////////////

class QuickSort {
private:
    vector<int> nums;
    void printArray();
    int sort(int start, int end);
    int partition(int start, int end, int& shifts);
public:
    QuickSort(vector<int>& n);
    int sort();
    ~QuickSort();
};

QuickSort::QuickSort(vector<int>& n)
: nums(n) {
}

QuickSort::~QuickSort() {

}
vector<int> readInput() {
    int n, k;
    vector<int> nums;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        std::cin >> k;
        nums.push_back(k);
    }
    return nums;
}

void QuickSort::printArray() {
    for (const int& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int QuickSort::partition(int start, int end, int& shifts) {
    int& pivot = nums[end];
    int copyto=start;
    for (int examine=start; examine<end; examine++) {
        if (nums[examine] < pivot) {
            shifts++;
            std::swap(nums[examine], nums[copyto++]);
        }
    }
    shifts++;
    std::swap(pivot, nums[copyto]);
    return copyto;
}

int QuickSort::sort(int start, int end) {
    if (start == end) return 0;
    int shifts=0;
    int ind = partition(start, end, shifts);
    if (ind != start) shifts += sort(start, ind-1);
    if (ind != end)   shifts += sort(ind+1, end);
    return shifts;
}

int QuickSort::sort() {
    if (nums.size() == 0) return 0;
    return sort(0, nums.size()-1);
}

/////////////////////////////////////////////////////////////////////////
//        Section for insertion sort
/////////////////////////////////////////////////////////////////////////

class InsertionSort {
private:
    vector<int> nums;
    void insertionSort_(int pos, int& shifts);
public:  
    InsertionSort(vector<int>& n);
    int sort();
};

InsertionSort::InsertionSort(vector<int>& n)
: nums(n) {        
}

//everything to the left of end of pos is sorted
void InsertionSort::insertionSort_(int pos, int& shifts) {
    int value = nums[pos];
    for (int i=pos-1; i>=0; i--) {       
        if (nums[i]>value) {
            shifts++;
            nums[i+1] = nums[i];           
        } else {
            nums[i+1] = value;        
            return;
        }
    }
    nums[0] = value;
}

int InsertionSort::sort() {
    int shifts = 0;
    for (int pos=1; pos<nums.size(); pos++) {
        insertionSort_(pos, shifts);
    }
    return shifts;
}

/////////////////////////////////////////////////////////////////////////
//                            Main program
/////////////////////////////////////////////////////////////////////////

int main() {
    vector<int> nums = readInput();
    
    QuickSort qs(nums);
    int qsswaps = qs.sort();
    
    InsertionSort is(nums);
    int isshifts = is.sort();
    
    std::cout << (isshifts - qsswaps) << std::endl;
}
