class Solution {    
    unordered_map<char, unordered_map<char, char>> graph;
    
    void buildGraph() {
        graph['a']['b'] = 'R'; graph['a']['f'] = 'D';
        graph['b']['a'] = 'L'; graph['b']['g'] = 'D'; graph['b']['c'] = 'R';
        graph['c']['b'] = 'L'; graph['c']['h'] = 'D'; graph['c']['d'] = 'R';
        graph['d']['c'] = 'L'; graph['d']['i'] = 'D'; graph['d']['e'] = 'R';
        graph['e']['d'] = 'L'; graph['e']['j'] = 'D';
        graph['f']['a'] = 'U'; graph['f']['g'] = 'R'; graph['f']['k'] = 'D';
        graph['g']['f'] = 'L'; graph['g']['b'] = 'U'; graph['g']['h'] = 'R'; graph['g']['l'] = 'D';
        graph['h']['g'] = 'L'; graph['h']['c'] = 'U'; graph['h']['i'] = 'R'; graph['h']['m'] = 'D';
        graph['i']['h'] = 'L'; graph['i']['d'] = 'U'; graph['i']['j'] = 'R'; graph['i']['n'] = 'D';
        graph['j']['i'] = 'L'; graph['j']['e'] = 'U'; graph['j']['o'] = 'D';
        graph['k']['f'] = 'U'; graph['k']['l'] = 'R'; graph['k']['p'] = 'D';
        graph['l']['k'] = 'L'; graph['l']['g'] = 'U'; graph['l']['m'] = 'R'; graph['l']['q'] = 'D';
        graph['m']['l'] = 'L'; graph['m']['h'] = 'U'; graph['m']['n'] = 'R'; graph['m']['r'] = 'D';
        graph['n']['m'] = 'L'; graph['n']['i'] = 'U'; graph['n']['o'] = 'R'; graph['n']['s'] = 'D';
        graph['o']['n'] = 'L'; graph['o']['j'] = 'U'; graph['o']['t'] = 'D';
        graph['p']['k'] = 'U'; graph['p']['q'] = 'R'; graph['p']['u'] = 'D';
        graph['q']['p'] = 'L'; graph['q']['l'] = 'U'; graph['q']['r'] = 'R'; graph['q']['v'] = 'D';
        graph['r']['q'] = 'L'; graph['r']['m'] = 'U'; graph['r']['s'] = 'R'; graph['r']['w'] = 'D';
        graph['s']['r'] = 'L'; graph['s']['n'] = 'U'; graph['s']['t'] = 'R'; graph['s']['x'] = 'D';
        graph['t']['s'] = 'L'; graph['t']['o'] = 'U'; graph['t']['y'] = 'D';
        graph['u']['p'] = 'U'; graph['u']['v'] = 'R'; graph['u']['z'] = 'D';
        graph['v']['u'] = 'L'; graph['v']['q'] = 'U'; graph['v']['w'] = 'R';
        graph['w']['v'] = 'L'; graph['w']['r'] = 'U'; graph['w']['x'] = 'R';
        graph['x']['w'] = 'L'; graph['x']['s'] = 'U'; graph['x']['y'] = 'R';
        graph['y']['x'] = 'L'; graph['y']['t'] = 'U';
        graph['z']['u'] = 'U'; 
    }
   
    // O(1) time, because the board is finite. 
    string traverse(char from, char to) {
        if (from == to) return "!";
        
        std::queue<pair<char, string>> q;
        q.push({from, ""});
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();            
            if (elem.first == to) {return (elem.second + "!");}
            
            for (const auto& kv : graph[elem.first]) {
                q.push({kv.first, elem.second + string(1, kv.second)});
            }
        }
        return "!";  // should not get here
    }
    
public:
    // O(n) time, O(1) space.
    string alphabetBoardPath(string target) {
        buildGraph(); 
        string ret;
        target = "a" + target;  // start at (0, 0)
        for (int i=0; i<target.size()-1; i++) {
            string t = traverse(target[i], target[i+1]);
            ret += t;
        }
        return ret;
    }
};
