/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
//Amortized data structure for O(1) average time, and O(h) memory
//
//The iterator maintains an inner vector of ptrs, of O(h) size for the next O(h) minimums
//Every hasNext() is O(1)
//First h next() are O(1) time, because they are read directly from vector
//The next h-th next() call causes re-population, so it is O(h) time
//however, amortized over (h+1) next() calls, every next() call is AVERAGE O(1) time!

class BSTIterator {
private:
    enum ReadOrder {LEFT, MID_FROM_LEFT, MID_FROM_RIGHT}; 
    
    const TreeNode *myRoot_;    //root of the tree
    const unsigned int height_; //height of the tree
    vector<TreeNode*> nodes_;   //ptrs to nodes in order stored here [This is the O(h) space requirement]
    int cacheContains_;         //how many entries in nodes_ are used i.e. from [0, cacheContains-1]
    int nodePtr_;               //used to keep track of last index written during populating phase
                                //used to keep track of next index to read during next() operation phase
    TreeNode *nextToRead_;      //node that needs to be read next to populate nodes_
                                //only used during populating phase; and maintained during operation phase
    ReadOrder ord_;             //from nextToRead_, says where we go
    
    unsigned int treeHeight_(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        unsigned int lhs = treeHeight_(root->left);
        unsigned int rhs = treeHeight_(root->right);
        return (1 + (lhs > rhs ? lhs : rhs));
    }
    
    TreeNode* getParent_(TreeNode* forMe) {
        TreeNode *parent = NULL;
        TreeNode *cand = const_cast<TreeNode*>(myRoot_);

        while (cand && cand != forMe) {
            parent = cand;
            if (forMe->val > cand->val) {
                cand = cand->right;
            } else {
                cand = cand->left;
            }
        }
        assert(cand == forMe);
        return parent;
    }
    
    void writeCache_(TreeNode* node) {
        nodePtr_++;
        cacheContains_++;
        nodes_[nodePtr_] = nextToRead_;
    }
    
    //traversing left side
    void handleCaseLeft_() {
        if (nextToRead_->left) {//left subtree exists
            nextToRead_ = nextToRead_->left;
        } else {                // no left subtree
            ord_ = MID_FROM_LEFT;
        }
        populateNodes_();
        return;
    }
    
    //coming to mid from left child; record mid, and traverse right side
    void handleCaseMidFromLeft_() {
        //RECORD MID: this is the only place that pointers are cached!
        //happens for leaves as well as middle nodes
        writeCache_(nextToRead_);
        
        if (nextToRead_->right) {
            nextToRead_ = nextToRead_->right;
            ord_ = LEFT;        // after moving down to right, keep traversing left
            populateNodes_();
            return;
        } else {
            // because both L and R subtrees, and myself, are done
            handleCaseMidFromRight_(); //calling common code
            return;
        }
    }
    
    void handleCaseMidFromRight_() {
        //my entire L, R subtrees, and myself are all done, so move up
        TreeNode* parent = getParent_(nextToRead_);
        if (parent == NULL) {
            nextToRead_ = parent;
            nodePtr_ = 0;   //will start reading here
            return;
        }
        if (parent->left == nextToRead_) {  //I was my parents left child
            ord_ = MID_FROM_LEFT;
        } else {                            //I was my parents right child
            ord_ = MID_FROM_RIGHT;
        }
        nextToRead_ = parent;
        populateNodes_();
        return;
    }
    
    // populate the next height_ nodes in nodes_, one node per call
    void populateNodes_() { 
        // finished iterating through entire tree, or finished populating
        if (nextToRead_ == NULL || cacheContains_ == height_) {
            nodePtr_ = 0;       //will start reading here
            return;             
        }
        switch (ord_) {
            case LEFT:  {
                handleCaseLeft_();
                return;
            }
            case MID_FROM_LEFT: {
                handleCaseMidFromLeft_();
                return;
            }
            case MID_FROM_RIGHT: {
                handleCaseMidFromRight_();
                return;
            }
            default: assert(0);
        }
    }
    
public:
    BSTIterator(TreeNode *root) 
    : myRoot_(root), height_(treeHeight_(root)), nodes_(height_, NULL), cacheContains_(0), nodePtr_(-1), nextToRead_(root), ord_(LEFT) {
        populateNodes_();   //populate for the very first time
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return (!(nextToRead_ == NULL && nodePtr_ == cacheContains_));
    }

    /** @return the next smallest number */
    int next() {
        assert(hasNext());
        int retval = nodes_[nodePtr_]->val;
        nodePtr_++;
        if (nodePtr_ == cacheContains_) {   //start re-populating
            nodePtr_ = -1;                  //last index written init to -1
            cacheContains_ = 0;             //and cache is empty
            populateNodes_();
        }
        return retval;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
