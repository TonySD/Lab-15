#include <atomic>
#include <future>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include "hash.hpp"
#include "all_structures.hpp"



class ThreadPool {
    private:
        std::atomic_bool finished;
        unsigned int available_threads;
        std::vector<std::thread> threads;
        std::queue<task> task_queue;
        std::mutex queue_mutex;

        void run() {
            while (!finished) {
                std::unique_lock<std::mutex> queue_lock(queue_mutex);
                if (!task_queue.empty()) {
                    task workingTask = std::move(task_queue.front());
                    task_queue.pop();
                    queue_lock.unlock();

                    auto bytes = getBytesFromFile(workingTask.filename);
                    std::string result = HashFactory::hash(bytes.data(), bytes.size(), workingTask.algorithm);
                    workingTask.prom.set_value(result);
                }
            }
        }

        public:
            ThreadPool(): finished(false) {
                available_threads = std::thread::hardware_concurrency();
                threads.reserve(available_threads);
                for (unsigned int i = 0; i < available_threads; ++i) {
                    threads.emplace_back(&ThreadPool::run, this);
                }
            }
            ThreadPool(unsigned int number_of_threads): finished(false), available_threads(number_of_threads) {
                threads.reserve(available_threads);
                for (unsigned int i = 0; i < available_threads; ++i) {
                    threads.emplace_back(&ThreadPool::run, this);
                }
            }
            ThreadPool(const ThreadPool &) = delete;
            ThreadPool(ThreadPool &&) = delete;
            ~ThreadPool() {
                finished = true;
                for (auto& i : threads) {
                    i.join();
                }
            }

            std::future<std::string> addTask(task new_task) {
                queue_mutex.lock();
                task_queue.push(new_task);
                queue_mutex.unlock();
                return new_task.prom.get_future();
            }
};