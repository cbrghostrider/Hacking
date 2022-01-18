class ProductOfNumbers {
    const int SIZE=200;
    vector<int> prod_chunks;
    vector<int> nums;
    
public:
    ProductOfNumbers() {}       
    
    void add(int num) {
        nums.push_back(num);
        if (nums.size() % SIZE == 0) {
            int prod=1;
            int nsz = nums.size();
            for (int i=nsz-1; i>=nsz-SIZE; i--) {
                prod *= nums[i];
            }
            prod_chunks.push_back(prod);
        }
    }
    
    // O(min(k, sqrt(n))) time, O(n) space.
    int getProduct(int k) {
        if (k <= 0) return 0;
        if (k > nums.size()) {k = nums.size();}
        
        // solos are the nums at the end that aren't accounted for in prod_chunks
        int solos = nums.size() % SIZE;
        int prod=1;
        for (int i=0; i<std::min(k, solos); i++) {
            prod *= nums[nums.size()-1 - i];
        }
        if (k <= solos) {
            return prod;
        }
        k -= solos;  // already got these                        
        int chunks = k/SIZE;
        int last_few = k%SIZE;
        
        for (int c=0; c<chunks; c++) {
            prod *= prod_chunks[prod_chunks.size()-1-c];
            k -= SIZE;
        }
        
        int index = nums.size()-solos-chunks*SIZE - 1;
        while (k > 0) {
            prod *= nums[index--];
            k--;
        }
        
        return prod;
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
