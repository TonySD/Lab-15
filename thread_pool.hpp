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
        std::mutex output_mutex;

        void run() {
            while (!finished) {
                std::unique_lock<std::mutex> queue_lock(queue_mutex);
                if (!task_queue.empty()) {
                    task workingTask = std::move(task_queue.front());
                    task_queue.pop();
                    queue_lock.unlock();

                    auto bytes = getBytesFromFile(workingTask.filename);
                    std::string result = HashFactory::hash(bytes.data(), bytes.size(), workingTask.algorithm);

                    output_mutex.lock();
                    if (workingTask.expected_hash == "") {
                        std::cout << "File " << workingTask.filename << " hash (" << algorithmToText(workingTask.algorithm) << "): " << std::endl;
                        std::cout << result << std::endl << std::endl;
                    } else if (workingTask.expected_hash == result) {
                        std::cout << "File " << workingTask.filename << " is complete! (" << algorithmToText(workingTask.algorithm) << ")" << std::endl << std::endl;
                    } else {
                        std::cout << "File " << workingTask.filename << " is corrupted! (" << algorithmToText(workingTask.algorithm) << ")" << std::endl;
                        std::cout << "Expected hash: " << workingTask.expected_hash << std::endl;
                        std::cout << "Got hash: " << result << std::endl << std::endl;
                    }
                    output_mutex.unlock();
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
                while (!task_queue.empty()) {}
                finished = true;
                for (auto& i : threads) {
                    i.join();
                }
            }

            void addTask(task new_task) {
                queue_mutex.lock();
                task_queue.push(new_task);
                queue_mutex.unlock();
            }
};