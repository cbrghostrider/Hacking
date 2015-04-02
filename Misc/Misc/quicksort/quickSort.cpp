
#include <vector>
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <fstream>

enum Strategy {PivotFirst=0, PivotLast, PivotMed};

int GetPivot(std::vector<int>& arr, int l, int r, Strategy pivotType) 
{
    int ret = -1;
    switch (pivotType) {
	case PivotFirst:
	  ret = l;
	  break;
	case PivotLast:
	  ret = r;
	  break;
	case PivotMed:
	  {
	      int m = l + (r-l) / 2;
	      if ((arr[l] <= arr[m] && arr[m] <= arr[r]) || (arr[r] <= arr[m] && arr[m] <= arr[l])) {
		  ret = m;
	      } else if ((arr[m] <= arr[r] && arr[r] <= arr[l]) || (arr[l] <= arr[r] && arr[r] <= arr[m])) {
		  ret = r;
	      } else {
		  ret = l;
	      }
	  }
	  break;
	default:
	  printf("Unhandled case!\n");
	  assert(0);
    }
    return ret;
}

void swapElems(std::vector<int>& arr, int lhs, int rhs)
{
    int tmp = arr[lhs];
    arr[lhs] = arr[rhs];
    arr[rhs] = tmp;
}


//l and r are both inclusive
int qsort(std::vector<int>& arr, int l, int r, Strategy pivotType)
{
    if (r == l  || r < l) {
	return 0;
    }

    int pivotIndex = GetPivot(arr, l, r, pivotType);
    swapElems(arr, l, pivotIndex);

    int pivot = arr[l];
    int i = l+1;
    for (int j=l+1; j<=r; j++) {
	if (arr[j] < pivot) {
	    swapElems(arr, j, i);
	    i++;
	}
    }
    swapElems(arr, l, i-1);

    int lhalf = qsort(arr, l, i-2, pivotType);
    int rhalf = qsort(arr, i, r, pivotType);

    return (r-l + lhalf + rhalf);
}

int main(int argc, char* argv[]) 
{
    std::ifstream inputFile;
    inputFile.open(argv[1]);

    std::vector<int> numbers;

    if (inputFile.is_open()) {
	int ip;
	while (inputFile>>ip) {
	    numbers.push_back(ip);
	}
    }
    std::vector<int> numbers2 = numbers;
    std::vector<int> numbers3 = numbers;

    int compF = qsort(numbers, 0,  numbers.size() - 1,  PivotFirst);
    int compL = qsort(numbers2, 0, numbers2.size() - 1, PivotLast);
    int compM = qsort(numbers3, 0, numbers3.size() - 1, PivotMed);

    printf("Comparisons: F = %d; L = %d; M = %d\n", compF, compL, compM);

    /*for (int i=0; i<numbers.size(); i++) {
	printf("%d\n", numbers[i]);
    }*/
}

