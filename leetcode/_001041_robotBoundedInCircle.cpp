class Solution {
    string inst;
    unordered_map<string, int> sig_tags;
    vector<int> tags;
    int next_tag=0;
    
    enum Dir {N=0, S, E, W};
    enum Way {Left=0, Right};
    
    vector<vector<Dir>> turns;
    //
    // This will be cached in signature form, and is the key.
    //
    // Basically, we are trying to determine whether the robot arrives at
    // the same position, with the same orientation, with the same future 
    // set of instructions.
    //
    // Note that the "tag", which is determined early on, is a proxy for
    // the "future set of instructions". In effect, looking ahead the entire
    // length of instructions (concat to itself) of length instructions.size()
    // the indices having the same string have the same tag value.
    // if that makes sense...
    //
    struct Info {
        int r=0;     // this cell r
        int c=0;     // this cell c
        Dir facing;  // the dir I'm facing when I enter this cell
        int tag=-1;  // my tag for this index in instructions
    };
    
    string toString(Dir dir) {
        if (dir == N) return "N";
        if (dir == S) return "S";
        if (dir == E) return "E";
        if (dir == W) return "W";
        return "?";
    }
    
    string signature(const Info& info) {
        string ret;
        ret += "(" + to_string(info.r) + "," + to_string(info.c) + ") ";
        ret += toString(info.facing);
        ret += " [" + to_string(info.tag) + "]";
        return ret;
    }
    
    void init() {
        turns = vector<vector<Dir>>(4, vector<Dir>(2, N));
        turns[N][Left]  = W;
        turns[W][Left]  = S;
        turns[S][Left]  = E;
        turns[E][Left]  = N;
        turns[N][Right] = E;
        turns[W][Right] = N;
        turns[S][Right] = W;
        turns[E][Right] = S;
    }
    
public:
    // O(n) time, O(n) space.
    bool isRobotBounded(string instructions) {
        inst = instructions;
        for (int i=0; i<inst.size(); i++) {
            string my_inst = (inst+inst).substr(i, inst.size());
            if (sig_tags.find(my_inst) == sig_tags.end()) {
                sig_tags[my_inst] = next_tag++;
            }
            tags.push_back(sig_tags[my_inst]);
        }
        
        init();
        
        int r=0, c=0;
        Dir dir=N;
        int tag = tags[0];
        unordered_set<string> visited;
        Info initial = {r, c, dir, tag};
        visited.insert(signature(initial));        
       
        // We only need to check for 4 iterations in the outer loop.
	// The example given in the problem is the worst case for outer loop.
	// Otherwise the path diverges so much that it is impossible to reach
	// the same state.	
        for (int rep=0; rep<4; rep++) {
            for (int i=0; i<instructions.size(); i++) {
                
                if (instructions[i] == 'L' || instructions[i] == 'R') {
                    dir = turns[dir][instructions[i] == 'L' ? Left : Right];                    
                } else {
                    int dr=0, dc=0;
                    if (dir == N) {dr = -1;}
                    if (dir == S) {dr =  1;}
                    if (dir == W) {dc = -1;}
                    if (dir == E) {dc =  1;}
                    r += dr; c += dc;
                }
                tag = tags[i+1 == instructions.size() ? 0 : i+1];
                
                Info info = {r, c, dir, tag};
                string sig = signature(info);
                if (visited.find(sig) != visited.end()) {
                    return true;
                }
                visited.insert(sig);                
            }
        }
        return false;
    }
};
