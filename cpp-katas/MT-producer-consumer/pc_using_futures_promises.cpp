
#include <stdlib.h>
#include <time.h>

#include <cstdio>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <condition_variable>
#include <future>

using std::vector;
using std::string;
using std::condition_variable;
using std::future;
using std::promise;

constexpr int kMaxMS = 20;

int randomN() {
    int rn = std::rand() % kMaxMS;
    return rn+1;
}

template <typename T>
T createItem(int& id, int& i, T dummy);

template <>
string createItem(int& id, int& i, string str) {
    string item = "[P " + std::to_string(id) + "; Item " + std::to_string(i) + "]";
    return item;
}

template<typename T>
class Queue {
    vector<future<T>> buffer;
    int head;  // points to the next place to dump
    int tail;  // points to the oldest item
    int size, capacity;

    // protects access to common state above.
    mutable std::mutex mut;

    // signaled when queue went from being full to non-full, to unblock waiting producers.
    condition_variable cv_on_consumer;

    // signaled when queue went from empty to non-empty, to unblock waiting consumers.
    condition_variable cv_on_producer;

  public:
    Queue(int cap) : capacity(cap) {
        buffer = vector<future<T>>(capacity);
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
    
    void addElem(std::future<T> elem) {
        bool should_notify = false;
        {
            std::unique_lock<std::mutex> ul(mut);
            while (size == capacity) {
                std::cout << "*** Thread: " << std::this_thread::get_id() << " waiting on consumer." << std::endl;
                cv_on_consumer.wait(ul);
            }

            buffer[head] = std::move(elem);
            head = (head+1) % capacity;
            if (size == 0) should_notify = true;
            size++;
        }
        if (should_notify) cv_on_producer.notify_one();
    }

    std::future<T> getElem() {
        bool should_notify = false;
        std::future<T> ret;
        {
            std::unique_lock<std::mutex> ul(mut);
            while (size == 0) {
                std::cout << "*** Thread: " << std::this_thread::get_id() << " waiting on producer." << std::endl;
                cv_on_producer.wait(ul);
            }
    
            ret = std::move(buffer[tail]);
            tail = (tail+1) % capacity;
            if (size == capacity) should_notify = true;
            size--;
        }
        if (should_notify) cv_on_consumer.notify_one();
        return std::move(ret);
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
        for (int i=1; i<=limit; i++) {
            std::promise<T> product;
            queue.addElem(std::move(product.get_future()));

            // sleep simulates time to produce the item
            std::this_thread::sleep_for(std::chrono::milliseconds(randomN()));
            T item = createItem(id, i, T());
            product.set_value(item);
            std::cout << "Enqueing: " << item << std::endl;
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
        for (int i=1; i<=limit; i++) {
            auto qelem = queue.getElem();
            T item = qelem.get();
            std::cout << "        C: " << id <<  "; Dequeing: " << item << std::endl;

            // sleep simulates doing something with the item
            std::this_thread::sleep_for(std::chrono::milliseconds(randomN()));
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


