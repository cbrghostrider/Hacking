class MyCircularQueue {
    vector<int> queue;
    int front=0;     // index of oldest inserted element
    int back=0;      // index of newest inserted element
    int capacity=0;  // total size of queue (static) with/without elements
    int size=0;      // number of elements present in queue
public:
    MyCircularQueue(int k) {
        capacity = k;
        queue = vector<int>(k, 0);
    }
    
    bool enQueue(int value) {
        if (size == capacity) return false;
        if (size == 0) {
            front = back = 0;
        } else {
            back = (back+1)%capacity;
        }
        queue[back] = value;
        size++;
        return true;
    }
    
    bool deQueue() {
        if (size == 0) return false;
        front = (front+1)%capacity;
        size--;
        return true;
    }
    
    int Front() {
        if (size == 0) return -1;
        return queue[front];
    }
    
    int Rear() {
        if (size == 0) return -1;
        return queue[back];
    }
    
    bool isEmpty() {
        return (size == 0);
    }
    
    bool isFull() {
        return (size == capacity);
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
