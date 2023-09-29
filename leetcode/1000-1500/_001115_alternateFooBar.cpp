class FooBar {
private:
    int n;
    bool foo_turn=true;
    std::mutex m;
    std::condition_variable cv;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        std::unique_lock<std::mutex> lck(m);
        for (int i = 0; i < n; i++) {
            cv.wait_for(lck, 60s, [this]() -> bool { return foo_turn;});
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            foo_turn = !foo_turn;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        std::unique_lock<std::mutex> lck(m);
        for (int i = 0; i < n; i++) {
            cv.wait_for(lck, 60s, [this]() -> bool { return !foo_turn;});             
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            foo_turn = !foo_turn;
            cv.notify_all();
        }
    }
};
