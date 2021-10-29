/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

class Solution {
    std::unordered_map<int, const Employee*> id_map;
    
    long totalImportance(int id) {
        long total = id_map[id]->importance;
        for (const int i: id_map[id]->subordinates) {
            total += totalImportance(i);
        }
        return total;
    }
    
public:
    int getImportance(vector<Employee*> employees, int id) {
        for (const Employee* e : employees) {
            id_map[e->id] = e;
        }
        
        long total = totalImportance(id);
        return total;
    }
};
