class Solution {
public:
    bool squareIsWhite(string coordinates) {
        return (((coordinates[0]-'a'+1) + (coordinates[1]-'1'+1))%2 != 0);
    }
};
