// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>

using std::vector;
using std::unordered_map;
using std::max;
using std::make_pair;

typedef int AnsType;

//converts to the key for the memoization cache
//uses domain knowledge, that indices for G/S/B lie within [0, 9]
//and stones index lies within [0, 29]
class CacheKey {
private:
    unsigned int key;
public:
    CacheKey(int bs, int be, int ss, int se, int gs, int ge, int sind);
    unsigned int getKey() const;
};

CacheKey::CacheKey(int bs, int be, int ss, int se, int gs, int ge, int sind) 
: key (0) {
    key |= ((0xF) & bs); key <<= 4;
    key |= ((0xF) & be); key <<= 4;
    key |= ((0xF) & ss); key <<= 4;
    key |= ((0xF) & se); key <<= 4;
    key |= ((0xF) & gs); key <<= 4;
    key |= ((0xF) & ge); key <<= 5;
    key |= ((0x1F) & sind);
}

unsigned int CacheKey::getKey() const {
    return key;
}

class GiftScrolls {
private:
    vector<int> bronze;
    vector<int> silver;
    vector<int> gold;
    vector<int> stones;

    //Dynamic Programming memoization cache
    unordered_map<unsigned int, AnsType> cache;
    void readInput();
    AnsType maxPowerPrime(int bs, int be, int ss, int se, int gs, int ge, int sind);
public:
    GiftScrolls();
    AnsType maxPower();
};

GiftScrolls::GiftScrolls() 
: bronze(), silver(), gold(), stones(), cache(){
    readInput();
}

void GiftScrolls::readInput() {
    int b, s, g, num=0;
    std::cin >> b >> s >> g;
    bronze.push_back(0); silver.push_back(0); gold.push_back(0); //sentinels
    for (int i=0; i<b; i++) { std::cin >> num; bronze.push_back(num); }
    for (int i=0; i<s; i++) { std::cin >> num; silver.push_back(num); }
    for (int i=0; i<g; i++) { std::cin >> num;   gold.push_back(num); }
    bronze.push_back(0); silver.push_back(0); gold.push_back(0); //sentinels
    for (int i=0; i<b+s+g; i++) { std::cin >> num; stones.push_back(num); }
}

AnsType GiftScrolls::maxPowerPrime(int bs, int be, int ss, int se, int gs, int ge, int sind) {
    CacheKey ck(bs, be, ss, se, gs, ge, sind);
    unsigned int key = ck.getKey();

    if (sind == stones.size()) {
        cache.insert(make_pair(key, 0));
        //std::cout << "here " << bs << " " << be << " " << ss << " " << se << " "  << gs << " " << ge  << " " << sind << std::endl;
        return 0;
    }

    //check memoization cache
    auto mit = cache.find(key);
    if (mit != cache.end()) 
        return mit->second;

    //dynamic programming algorithm 
    AnsType candbs = (bs+1 < be) ? maxPowerPrime(bs+1, be, ss, se, gs, ge, sind+1) + stones[sind]*bronze[bs+1] : 0; 
    AnsType candbe = (bs < be-1) ? maxPowerPrime(bs, be-1, ss, se, gs, ge, sind+1) + stones[sind]*bronze[be-1] : 0; 
    AnsType candss = (ss+1 < se) ? maxPowerPrime(bs, be, ss+1, se, gs, ge, sind+1) + stones[sind]*silver[ss+1] : 0; 
    AnsType candse = (ss < se-1) ? maxPowerPrime(bs, be, ss, se-1, gs, ge, sind+1) + stones[sind]*silver[se-1] : 0; 
    AnsType candgs = (gs+1 < ge) ? maxPowerPrime(bs, be, ss, se, gs+1, ge, sind+1) + stones[sind]*gold[gs+1]   : 0; 
    AnsType candge = (gs < ge-1) ? maxPowerPrime(bs, be, ss, se, gs, ge-1, sind+1) + stones[sind]*gold[ge-1]   : 0; 

    vector<AnsType> cands = {candbs, candbe, candss, candse, candgs, candge};
    std::sort(cands.begin(), cands.end(), std::greater<AnsType>());
    AnsType powerval = cands[0];

    //enter value into memoization cache
    cache.insert(make_pair(key, powerval));
    return powerval;
}

AnsType GiftScrolls::maxPower() {
    return maxPowerPrime(0, bronze.size()-1, 0, silver.size()-1, 0, gold.size()-1, 0);
}

int main() {
    GiftScrolls gs;
    AnsType ans = gs.maxPower();
    std::cout << ans << std::endl;
}
