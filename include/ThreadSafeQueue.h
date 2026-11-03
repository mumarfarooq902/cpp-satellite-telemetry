#pragma once

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

// A bounded, thread-safe queue for passing telemetry packets from the
// producer (generator) thread to the consumer (processor) thread.
// Demonstrates a classic producer-consumer synchronisation pattern using
// std::mutex and std::condition_variable.
template <typename T>
class ThreadSafeQueue {
public:
    explicit ThreadSafeQueue(std::size_t maxSize = 128) : maxSize_(maxSize) {}

    // Blocks while the queue is full, then pushes the item.
    void push(T item) {
        std::unique_lock<std::mutex> lock(mutex_);
        notFull_.wait(lock, [this] { return queue_.size() < maxSize_ || closed_; });
        if (closed_) return;
        queue_.push(std::move(item));
        lock.unlock();
        notEmpty_.notify_one();
    }

    // Blocks until an item is available. Returns std::nullopt once the queue
    // is closed and drained, so the consumer knows to stop.
    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        notEmpty_.wait(lock, [this] { return !queue_.empty() || closed_; });
        if (queue_.empty()) return std::nullopt;  // closed and drained
        T item = std::move(queue_.front());
        queue_.pop();
        lock.unlock();
        notFull_.notify_one();
        return item;
    }

    // Signals that no more items will be pushed; wakes any waiting threads.
    void close() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            closed_ = true;
        }
        notEmpty_.notify_all();
        notFull_.notify_all();
    }

private:
    std::queue<T>           queue_;
    std::size_t             maxSize_;
    bool                    closed_ = false;
    std::mutex              mutex_;
    std::condition_variable notEmpty_;
    std::condition_variable notFull_;
};
