class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        std::sort(boxTypes.begin(), boxTypes.end(), 
                  [](const vector<int>& left, const vector<int>& right) -> bool {
            if (left[1] != right[1]) {return (left[1] > right [1]);}
            return (left[0] > right[0]);         
        });
        int units = 0;
        int index = 0;
        while (truckSize > 0 && index < boxTypes.size()) {
            int boxes = std::min(truckSize, boxTypes[index][0]);
            units += (boxes * boxTypes[index][1]);
            if (boxes == boxTypes[index][0]) index++;
            truckSize -= boxes;
        }
        return units;
    }
};
