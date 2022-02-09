
#include <stdlib.h>
#include <time.h>

#include <cstdio>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

using std::vector;
using std::string;

constexpr int kMaxMS = 20;

int randomN() {
    int rn = std::rand() % kMaxMS;
    return rn+1;
}

template<typename T>
class Queue {
    vector<T> buffer;
    int head;  // points to the next place to dump
    int tail;  // points to the oldest item
    int size, capacity;
    mutable std::mutex mut;
  public:
    Queue(int cap) : capacity(cap) {
        buffer = vector<T>(capacity, T());
        head = 0;
        tail = 0;
        size = 0;
    }

    bool isFull() const {
        std::lock_guard<std::mutex> lg(mut);
        return size == capacity;
    }

    bool isEmpty() const {
        std::lock_guard<std::mutex> lg(mut);
        return size == 0;
    }
    
    bool addElem(const T& elem) {
        std::lock_guard<std::mutex> lg(mut);
        if (size == capacity) return false;

        buffer[head] = elem;
        head = (head+1) % capacity;
        size++;
        return true;        
    }

    bool getElem(T& elem) {
        std::lock_guard<std::mutex> lg(mut);
        if (size == 0) return false;
    
        elem = buffer[tail];
        tail = (tail+1) % capacity;
        size--;
        return true;
    }
};

template <typename T>
class Producer {
    int id=0;
    Queue<T>& queue;
    int limit=0;
  public:

    Producer(Queue<T>& q, int i, int lim) : queue(q), id(i), limit(lim) {
    }

    bool operator()() {
        for (int i=1; i<=limit;) {
            string item = "[P " + std::to_string(id) + "; Item " + std::to_string(i) + "]";
            std::this_thread::sleep_for(std::chrono::milliseconds(randomN()));
            if (queue.addElem(item)) {
                std::cout << "Enqueing: " << item << std::endl;
                i++;
            }
        }
        return true;
    }
};

template <typename T>
class Consumer {
    int id=0;
    Queue<T>& queue;
    int limit=0;
  public:

    Consumer(Queue<T>& q, int i, int lim) : queue(q), id(i), limit(lim) {
    }

    bool operator()() {
        for (int i=1; i<=limit; ) {
            string item;
            std::this_thread::sleep_for(std::chrono::milliseconds(randomN()));
            if (queue.getElem(item)) {
                std::cout << "        C: " << id <<  "; Dequeing: " << item << std::endl;
                i++;
            }
        }
        return true;
    }
};


int main() {
    Queue<string> buf(10);
    int kNumProducers = 5;
    int kNumConsumers = 5;
    int kLimit=10;

    std::vector<std::thread> producers, consumers;
    for (int i=0; i<kNumProducers; i++) {
        producers.push_back(std::thread(Producer<string>(std::ref(buf), i+1, kLimit)));
    }
    for (int i=0; i<kNumConsumers; i++) {
        consumers.push_back(std::thread(Consumer<string>(std::ref(buf), i+1, kLimit)));
    }
    for (auto& t : producers) {
       t.join();
    }
    for (auto& t : consumers) {
       t.join();
    }
}


