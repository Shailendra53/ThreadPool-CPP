/**
 * @file CThreadPool.hpp
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THREADPOOLLIB_CTHREADPOOL
#define THREADPOOLLIB_CTHREADPOOL

#include "IThreadPool.hpp"

#include <mutex>

namespace ThreadUtil
{
    class CThreadPool: public IThreadPool
    {
        private:
            typedef IThreadPool Inherited;

        public:
            CThreadPool(int iNumberOfThreads = 1);
            ~CThreadPool();

            // To add a single tasks to the ThreadPool task list
            // In this function we do locking and unlocking specific 
            // to the type of threads we are using.
            // Hence, this function is overriden in child class
            // accordingly.
            virtual bool AddTask(const std::shared_ptr<ITask>& spTask) override;

        protected:

            // Initializes all threads in the ThreadPool
            // Specific type of threads are initialized
            virtual bool InitializeThreads() override;

            // Fetches one task from the task list and executes it.
            // In this function we do locking and unlocking specific 
            // to the type of threads we are using.
            // Hence, this function is overriden in child class
            // accordingly.
            virtual bool AssignATask() override;

        protected:

            // mutex for locking
            std::mutex m_mtxTaskQueueLock;
    };
}

#endif