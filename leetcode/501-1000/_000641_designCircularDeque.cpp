class MyCircularDeque {
    vector<int> cont;
    int front=0;     // points to last valid thing in front (only for contains != 0)
    int back=0;      // points to last valid thing in back  (only for contains != 0)
    int contains=0;  // how many things are valid in the container
public:
    MyCircularDeque(int k) {
        cont = vector<int>(k, 0);
    }
    
    bool insertFront(int value) {
        if (isFull()) return false;
        if (contains != 0) {
            front++; 
            if (front == cont.size()) {front = 0;}
        } else {
            back = front = 0;
        }
        cont[front] = value;
        contains++;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;
        if (contains != 0) {
            back--; 
            if (back == -1) {back = cont.size()-1;}
        } else {
            back = front = 0;
        }
        cont[back] = value;
        contains++; 
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;
        front--;
        if (front == -1) {front = cont.size()-1;}
        contains--;
        if (contains == 0) {front = back = 0;}
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;
        back++;
        if (back == cont.size()) {back = 0;}
        contains--;
        if (contains == 0) {front = back = 0;}
        return true;
    }
    
    int getFront() {
        if (isEmpty()) return -1;
        return cont[front];
    }
    
    int getRear() {
        if (isEmpty()) return -1;
        return cont[back];
    }
    
    bool isEmpty() {
        return (contains == 0);
    }
    
    bool isFull() {
        return (contains == cont.size());
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
