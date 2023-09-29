// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

class TwoSum {
    unordered_map<int, int> numFreq;
public:
	void add(int number) {
	    //if (numFreq.find(number) == numFreq.end()) {
	     //   numFreq.insert(make_pair(number, 1));
	    //} else {
	        numFreq[number]++;
	    //}
	}

	bool find(int value) {
	    for (const pair<int, int>& nfp : numFreq) {
	        int num = nfp.first;
	        auto it = numFreq.find(value - num);
	        if (it == numFreq.end()) continue;
	        if (it->first != num) return true;
	        if (it->second > 1) return true;
	    }
	    return false;
	}
};
