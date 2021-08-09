#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

template <typename T> class SynchronizedQueue {
private:
  typedef lock_guard<mutex> lock;
  typedef unique_lock<mutex> ulock;

  queue<T> q;
  mutex mut;
  condition_variable cv;

public:
  void push(T const &val) {
    lock l(mut);
    bool wake = q.empty();
    q.push(val);
    if (wake) {
      cv.notify_one();
    }
  }

  T pop() {
    ulock u(mut);
    while (q.empty()) {
      cv.wait(u);
    }

    T retval = q.front();
    q.pop();
    return retval;
  }

  unsigned int size() {
    lock l(mut);
    return q.size();
  }
  bool empty() {
    lock l(mut);
    return q.empty();
  }
};
