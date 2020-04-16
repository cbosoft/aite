#pragma once
#include <mutex>
#include <queue>
#include <memory>


// https://codereview.stackexchange.com/questions/149676/writing-a-thread-safe-queue-in-c

template<class T>
class SafeQueue {

  private:

    std::queue<std::shared_ptr<T>> q;
    std::mutex m;

  public:

    SafeQueue() {}

    void push(std::shared_ptr<T> elem)
    {
      if(elem == nullptr)
        return;

      std::lock_guard<std::mutex> l(this->m);
      q.push(elem);
    }

    std::shared_ptr<T> pop()
    {

      std::shared_ptr<T> elem = nullptr;

      {
        std::lock_guard<std::mutex> l(this->m);
        if(!q.empty()) {
          elem = q.front();
          q.pop();
        }
      }

      return elem;

    }

    void clear()
    {
      this->q = std::queue<std::shared_ptr<T>>();
    }

    size_t size()
    {
      return this->q.size();
    }

};

