/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

// The tree is serialized as follows:
// 
// Null tree: "N;"
// Tree with one node, no children: "v;0;"  where v is value
// In general, tree with K children: "v;k;<subtrees>" v, k are numbers
//
// Note that there may be "holes" in the children, if for example a tree has 
// 3 children, the middle of which is null
// That's OK, since our format has "N;" for null, we can represent it
//
// So in general, only null tree is represented by "N;"
// Rest are all at least 2 numbers: "v;k;" followed by <subtrees>
//
class Codec {
    
    int getNum(const string& data, int& ptr) {
        int pos = data.find_first_of(";", ptr);
        if (pos == string::npos) {
            ptr = data.size();
            return -1;  // error really, but...
        }
        
        int val = stoi(data.substr(ptr, pos-ptr));        
        ptr = pos+1;
        return val;
    }
    
    // same as the other deserialize, but keeps a running pointer that is continuously updated
    Node* deserialize_(const string& data, int& ptr) {
        if (ptr >= data.size()) return nullptr;  // error really, but...
        
        if (data[ptr] == 'N') {
            ptr += 2;
            return nullptr;
        }
        int val = getNum(data, ptr);
        Node* ret = new Node(val);
        int num_children = getNum(data, ptr);
        for (int i=0; i<num_children; i++) {
            if (data[ptr] == 'N') {
                ptr += 2;
                ret->children.push_back(nullptr);
            } else {
                Node* child = deserialize_(data, ptr);
                ret->children.push_back(child);
            }
        }
        return ret;
    }
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if (root == nullptr) return "N;";
        string ret = to_string(root->val) + ";";
        ret += to_string(root->children.size()) + ";";
        for (Node* child : root->children) {
            ret += serialize(child);
        }
        return ret;
    }
	
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        int ptr=0;
        return deserialize_(data, ptr);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
