// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
    class LRUCache{
        typedef pair<int, int> KVPair;
        typedef list<KVPair>::iterator LIT;
        list<KVPair> data;
        unordered_map<int, LIT> htable;
        
        const int CAPACITY;
        int size;
        
        void bump(int key) {
            auto cit = (htable.find(key));
            if (cit == htable.end()) return;
            
            auto dit = cit->second;
            int val = dit->second;
            data.erase(dit);
            data.push_front(make_pair(key, val));
            auto nit = data.begin();
            htable[key] = nit;
        }
        
    public:
        LRUCache(int capacity) 
        : htable(), data(), CAPACITY(capacity), size(0) {
        }
        
        int get(int key) {
            auto cit = htable.find(key);
            if (cit == htable.end()) return -1;
            int retval = (cit->second)->second;
            bump(key);
            return retval;
        }
        
        void set(int key, int value) {
            auto cit = htable.find(key);
            if (cit != htable.end()) {
                cit->second->second = value;
                bump(key);
                return;
            }
            if (size < CAPACITY) {
                size++;
                data.push_front(make_pair(key, value));
                htable.insert(make_pair(key, data.begin()));
                return;
            }
            auto lastit = data.rbegin();
            int lastkey = lastit->first;
            htable.erase(lastkey);
            data.pop_back();
            data.push_front(make_pair(key, value));
            htable.insert(make_pair(key, data.begin()));
        }
    };
