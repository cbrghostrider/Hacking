class Solution {
    // Start from the right.
    // An asteroid moving right is:
    //    1. Put on the stack if nothing is on it, or an asteroid moving right is on it.
    //    2. Collides repeatedly with stack top if an asteoid moving left is on it.
    //          if all stack is destroyed, it is put on the stack (moving right)
    //
    // An astroid moving left can never collide with anything on stack, so it is put on stack.
    
public:
    vector<int> asteroidCollision(vector<int>& asteroid) {
        vector<int> stack;
        for (int i=asteroid.size()-1; i>=0; i--) {
            
            if (asteroid[i] > 0) {  // moving right
                if (stack.empty() || stack.back() > 0) {
                    stack.push_back(asteroid[i]);                
                } else {
                    bool keep=true;
                    while (!stack.empty() && stack.back() < 0) {
                        if (asteroid[i] == std::abs(stack.back())) {
                            keep = false;
                            stack.pop_back();
                            break;
                        } else if (asteroid[i] > std::abs(stack.back())) {
                            stack.pop_back();
                        } else {
                            keep = false;
                            break;
                        }
                    }
                    if (keep) {stack.push_back(asteroid[i]);}
                }
            } else {  // moving left
                stack.push_back(asteroid[i]);
            }            
        }
        std::reverse(stack.begin(), stack.end());
        return stack;
    }
};
