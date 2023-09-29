class BoundedBlockingQueue {
    std::queue<int> elements;
    int CAP;
    
    // For sync between producers/consumers.
    std::mutex mut;
    std::condition_variable cv_prod, cv_cons;
    
    // For recording state.
    std::mutex sz_mut;
    int sz=0;
    
public:
    BoundedBlockingQueue(int capacity) {
        CAP=capacity;
    }
    
    void enqueue(int element) {
        std::unique_lock<std::mutex> lck(mut);
        while (elements.size() == CAP) cv_prod.wait(lck);
        elements.push(element);
        {
            std::lock_guard<std::mutex> l(sz_mut);
            sz = elements.size();
        }
        cv_cons.notify_all();
    }
    
    int dequeue() {
        std::unique_lock<std::mutex> lck(mut);
        while (elements.size() == 0) cv_cons.wait(lck);
        int ret = elements.front();
        elements.pop();
        {
            std::lock_guard<std::mutex> l(sz_mut);
            sz = elements.size();
        }
        cv_prod.notify_all();
        return ret;
    }
    
    int size() {
        std::lock_guard<std::mutex> l(sz_mut);
        return sz;
    }
};
