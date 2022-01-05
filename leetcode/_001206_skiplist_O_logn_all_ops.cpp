
#include <vector>
#include <iostream>
#include <utility>

using std::vector;
using std::pair;

class Skiplist {
    struct Node {
        bool is_sentinel=false;  // special node to mark the start/end at any level
        int val=0;
        int freq=0;
        Node* next=nullptr;  // next link at the same level
        Node* up=nullptr;    // link to less populated upper level
        Node* down=nullptr;  // link to more populated lower level
    };
    
    vector<Node*> skiplist;    
    const double PROB = 0.5;  // The probability that it is added to the skiplist above
    const unsigned int SEED=0xdeadbeef;
    
    // Whether this node has an uplink or a downlink
    bool isCrossLink(Node* node) {
        return (node->down != nullptr || node->up != nullptr);
    }
    
    // Adds an empty skiplist level to the skiplist.
    // returns a pointer to the start sentinel
    Node* addVoidSkiplist() {
        Node* start_sentinel=new Node();
        Node* end_sentinel = new Node();
        start_sentinel->is_sentinel = end_sentinel->is_sentinel = true;
        start_sentinel->next = end_sentinel;
        skiplist.push_back(start_sentinel);
        
        // create the cross links
        if (skiplist.size() != 1) {
            Node* start_lower = skiplist[skiplist.size()-2];
            Node* end_lower = start_lower->next;
            while (!end_lower->is_sentinel) {
                end_lower = end_lower->next;
            }
            start_sentinel->down = start_lower;
            start_lower->up = start_sentinel;
            end_sentinel->down = end_lower;
            end_lower->up = end_sentinel;
        }
        
        return start_sentinel;
    }
    
    // Adds a new node for num in the skiplist at level
    // Node is the node within this level *after* which we search for a suitable position
    // downlink is the same value node from lower level
    // if level >= skiplist.size(), then we add a brand new skiplist level (and stop there)
    void recursiveAddUpwards(int level, int num, Node* node, Node* downlink) {        
        bool final_level=false;
        if (level >= skiplist.size()) {
            addVoidSkiplist();
            final_level=true;
        }
        
        if (node == nullptr) {
            node = skiplist[level];
        }
        
        Node* last=node;  // Last node with up/down link
	    Node* prev=node;  // prev node in linked list
        node = node->next;
        while (!node->is_sentinel && node->val < num) {
            if (isCrossLink(node)) last = node;
			prev = node;
            node = node->next;
        }
        if (node->is_sentinel || node->val >= num) {node = prev;}
        
        Node* add_me = new Node();
        add_me->val=num; add_me->freq=1;
        add_me->down = downlink;
        if (downlink) downlink->up = add_me;
        add_me->next = node->next;
        node->next = add_me;        
        
        int rng = rand() % 100;
        
        // recursive add terminated with 50% probability
        if (!final_level && rng >= 100*PROB) recursiveAddUpwards(level+1, num, last->up, add_me);
    }
   
    // Recursively deletes nodes with value num in all skiplist levels, starting from the top.
    void recursiveDeleteDownwards(int num) {
        vector<pair<Node*, int>> stack;
		stack.push_back({skiplist.back(), skiplist.size()-1});  // beginning sentinel in topmost level

		bool done = false;  // will be done when num is eliminated in the lowest level
		                    // may or may not also be elim in one or more upper levels
		while (!done) {
			auto elem = stack.back(); stack.pop_back();
			Node* node = elem.first;
			if (node->down) {
				stack.push_back({node->down, elem.second-1});
			}
			
			Node* prev=node;
			node = node->next;
			
			while (!node->is_sentinel && node->val < num) {
				if (node->down) stack.push_back({node->down, elem.second-1});
				prev = node;
				node = node->next;
			}
			if (node->is_sentinel || node->val > num) continue;  
			if (node->val == num) {
				prev->next = node->next;
				delete node;
				if (elem.second == 0) return;
			}
		}
    }
    
    // node is the closest smaller node in the lowermost level, that also has an uplink
    // num is guaranteed to not exist in the skiplist when called
    void add(int num, Node* node) {
        recursiveAddUpwards(0, num, node, nullptr);
    }
    
    // will be called from the uppermost populated level
    void updateFreq(Node* node, int val) {
        if (node == nullptr) return;
        node->freq += val;
        updateFreq(node->down, val);
    }
    
    // returns a pair of node ptr and bool
    // If found, 
    //    bool is true, and node ptr points to element in the uppermost skiplist
    // If not found, 
    //    bool is false, and node ptr points to closest smaller element in the lowest skiplist that has an uplink
    pair<Node*, bool> search(int level, int num, Node* node) {                
        Node* last=node;  // Last node with up/down link
	    Node* prev=node;  // prev node in linked list		
        node = node->next;
        while (!node->is_sentinel && node->val < num) {
            if (isCrossLink(node)) last = node;
			prev = node;
            node = node->next;            
        }
        if (!node->is_sentinel && node->val == num && node->freq >= 1) return {node, true};        

        if (node->is_sentinel || node->val > num) {node = prev;}

        if (level == 0) return {last, false};
        return search(level-1, num, last->down);
    }
    
public:
    Skiplist() {
        std::srand(SEED);
        addVoidSkiplist();
    }    

    void dump() {
		std::cout << "------------------------------------------------------------" << std::endl;
        for (int i=skiplist.size()-1; i>=0; i--) {
			std::cout << "L: " << i; ": ";
			Node* node=skiplist[i];
			while(node) {
				if (node->is_sentinel) {
					std::cout << "-> SENT";
				} else {
  				    std::cout << "-> " << node->val;
				}
				std::cout << "[";				
				if (node->up) {std::cout << "U(" << node->up->val << ")";} else {std::cout << "   ";}
				if (node->down) {std::cout << "D(" << node->down->val << ")";} else {std::cout << "   ";}
				std::cout << "]";
				node = node->next;
			}
			std::cout << std::endl;
		}
		std::cout << "------------------------------------------------------------" << std::endl;
    }
    
    
    // O(log n) time.	
    bool search(int target) {
        auto elem = search(skiplist.size()-1, target, skiplist.back());
        return elem.second;
    }
    
    // O(log n) time.	
    void add(int num) {
        auto elem = search(skiplist.size()-1, num, skiplist.back());
        if (elem.second) {
            updateFreq(elem.first, 1);
            return;
        }
		// std::cout << "Search returned: " << elem.first->val << std::endl;
        add(num, elem.first);
    }
   
    // O(log n) time.	
    bool erase(int num) {
        auto elem = search(skiplist.size()-1, num, skiplist.back());
        if (elem.second && elem.first->freq > 1) {
            updateFreq(elem.first, -1);
            return true;
        }
        if (elem.second == false) {
            return false;
        }
		recursiveDeleteDownwards(num);
        return true;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */

void sl_search(Skiplist* sl, int num) {
	std::cout << "Searching for " << num << std::endl;
	if (sl->search(num)) {
		std::cout << "Found " << num << std::endl;
	} else {
		std::cout << "Not Found " << num << std::endl;
	}
}

int main() {
	Skiplist *sl = new Skiplist();
	sl->add(1); sl->dump();
	sl->add(2); sl->dump();
	sl->add(3); sl->dump();
	sl_search(sl, 0);
	sl->add(4); sl->dump();
	sl_search(sl, 1);
	sl->add(5); sl->dump();
	sl_search(sl, 3);
	sl_search(sl, 6);
	sl->erase(2); sl->dump();
	sl->add(2); sl->dump();
	sl->add(2); sl->dump();
	sl->erase(2); sl->dump();
	sl->erase(2); sl->dump();
}
