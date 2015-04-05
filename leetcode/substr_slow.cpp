// inefficient solution :(

class Solution {
public:
#define SIZEOFBYTE = (8);
    
    class Cache {
      public:
        enum Status {Not_Computed=0, Comp_False, Comp_True};
        
        Cache(unsigned int size) : size_(size), bits_(0), init_(0) 
        {
            unsigned long long sizeSqr = size * size;
            unsigned long long divisor = 64;//(SIZEOFBYTE * sizeof (unsigned long long));
            unsigned int rem = ((sizeSqr) % divisor);
            unsigned int quot = ((sizeSqr) / divisor);
            unsigned int wrapme    = ( rem != 0 ? 1 : 0); 
            unsigned int sizeCache =  ( quot + wrapme);
            bits_ = new unsigned long long [sizeCache];
            init_ = new unsigned long long [sizeCache];
            memset(bits_, 0, sizeCache);
            memset(init_, 0, sizeCache);
        }
        
        ~Cache() {delete [] bits_; delete [] init_;}
        
        void Set(unsigned int x, unsigned int y, Status value) {
            SetBit(GetIndex(x, y), value);
        }
        
        Status Get(unsigned int x, unsigned int y) const {
            return GetBit(GetIndex(x, y));
        }
      private:
        typedef std::pair<unsigned int, unsigned int> MyIndex_t;
        
        //converts x, y indices into a pair of indices within my cache
        //ret.fst is the actual index I need to go to first
        //ret.snd is the bit within that unsigned long long I get next
        MyIndex_t GetIndex(unsigned int x, unsigned int y) const {
            unsigned int size   = y*size_ + x;
            unsigned int first  = size / 64;//(SIZEOF_BYTE * sizeof (unsigned long long));
            unsigned int second = size % 64;//(SIZEOF_BYTE * sizeof (unsigned long long));
            return make_pair(first, second);
        }
        
        void SetBit(MyIndex_t ind, Status stat) {
            unsigned long long& bit  = bits_[ind.first];
            unsigned long long& init = init_[ind.first];
            unsigned long long mask  = ((unsigned long long)(1)) << (ind.second);
            unsigned long long cmask = ~(mask);
            switch (stat) {
              case Not_Computed : 
                bit  = bit & cmask;
                init = init & cmask;
                break;
              case Comp_False :
                bit  = bit & cmask;
                init = init | mask;
                break;
              case Comp_True :
                bit  = bit | mask;
                init = init | mask;
                break;
              default :
                assert(0);
            }
        }
        
        Status GetBit(MyIndex_t ind) const {
            unsigned long long bit  = bits_[ind.first];
            unsigned long long init = init_[ind.first];
            unsigned long long mask  = ((unsigned long long)(1)) << (ind.second);
            if ((init & mask) == 0) {
                return Not_Computed;
            }
            if ((bit & mask) == 0) {
                return Comp_False;
            }
            return Comp_True;
        }
        
        
        unsigned int size_;
        unsigned long long *bits_; //if initialized, says whether this value is true or false
        unsigned long long *init_; //if true, corresponding bits_ value has been computed, if not it hasn't
        //together bits_ and init_ corresponding positions represent a 2-bit value
        // bits_ init_
        // x     0      - Not_Computed
        // 0     1      - computed as false
        // 1     1      - computed as true
    };

    
    bool noDuplicates(Cache& cache, const string& s, int unsigned from, int unsigned to) {
        if (from > to) {
            assert(0);
        } else if (from == to) {
            //base case
            cache.Set(from, to, Cache::Comp_True);
            return true;
        }
        
        //cache lookup first
        Cache::Status stat = cache.Get(from, to);
        if (stat != Cache::Not_Computed) {
            if (stat == Cache::Comp_False) {
                return false;
            } else {
                return true;
            }
        }
        
        //inductive case
        unsigned int size = to - from + 1; //[from, to] both inclusive
        unsigned int lhs_from = from,          lhs_to = from + size/2 - 1;
        unsigned int rhs_from = from + size/2, rhs_to = to;
        
        bool lhs_no_dup = noDuplicates(cache, s, lhs_from, lhs_to);
        bool rhs_no_dup = noDuplicates(cache, s, rhs_from, rhs_to);
        bool cross_dup = false;
        
        //easy case, left or right parts had duplicates
        if (lhs_no_dup == false || rhs_no_dup == false) {
            //found duplicates in left or right half
            cache.Set(from, to, Cache::Comp_False);
            return false;
        }
        
        //find cross lhs rhs duplicates
        //FIXME: May be able to sort and use merge subroutine to do this faster
        for (unsigned int li = lhs_from; li <= lhs_to; li++) {
            for (unsigned int ri = rhs_from; ri <= rhs_to; ri++) {
                if (s[li] == s[ri]) {
                    cross_dup = true;
                    break;
                }
            }
            if (cross_dup) {
                break;
            }
        }
        
        if (cross_dup) {
            cache.Set(from, to, Cache::Comp_False);
        } else {
            cache.Set(from, to, Cache::Comp_True);
        }
        
        return (!(cross_dup));
    }

    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) {
            return 0;
        }
        
        Cache cache(s.size());
        
        unsigned int size = s.size();
        for (unsigned int csize = size, nstr=1; csize >= 1; csize--, nstr++) {
            for (unsigned int start=0; start < nstr; start++) {
                if (noDuplicates(cache, s, start, start + csize - 1)) {
                    return (csize);
                }
                
                /*string ss = s.substr(start, csize);
                std::unordered_map<char, int> myMap;
                bool bad = false;
                for(auto it = ss.begin(); it != ss.end(); it++){
                    if (myMap.find(*it) == myMap.end()) {
                        myMap[*it] = 1;
                    } else {
                        bad = true; //entered duplicate character
                        break;
                    }
                }
                if (!bad) {
                    return ss.size();
                }*/
            }
        }
        return 0;
    }
};
