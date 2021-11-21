class Foo {
    std::mutex foo;
    int done=0;
public:
    Foo() {}

    void first(function<void()> printFirst) {
        foo.lock();
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        done++;
        foo.unlock();
    }

    void second(function<void()> printSecond) {
        foo.lock();
        while (done < 1) {
            foo.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            foo.lock();
        }
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        done++;
        foo.unlock();
    }

    void third(function<void()> printThird) {
        foo.lock();
        while (done < 2) {
            foo.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            foo.lock();
        }        
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        done++;
        foo.unlock();
    }
};
