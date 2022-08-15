/**
 * @file IThreadPool.hpp
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THREADPOOLLIB_ITHREADPOOL
#define THREADPOOLLIB_ITHREADPOOL

#include "../Tasks/ITask.hpp"
#include "../Threads/IThread.hpp"

#include <vector>

namespace ThreadUtil
{
    class IThreadPool
    {
        public:
            IThreadPool(int iNumberOfThreads = 1);
            virtual ~IThreadPool();

            // Functions for basic Initialize and Finalize funtionalities.
            bool Initialize();
            bool Run();
            bool Finalize();
            
            // This function is used to tell the ThreadPool that 
            // there are no more tasks to process. Complete the 
            // current set of tasks and stop.
            void SetNoMoreTasks();

            // To add a single tasks to the ThreadPool task list
            // In this function we do locking and unlocking specific 
            // to the type of threads we are using.
            // Hence, this function is overriden in child class
            // accordingly.
            virtual bool AddTask(const std::shared_ptr<ITask>& spTask) = 0;

            // To add list of tasks to the ThreadPool list.
            bool AddTasks(std::vector<std::shared_ptr<ITask>>& vecTasks);

        protected:
            // Initializes all threads in the ThreadPool
            // Specific type of threads are initialized
            virtual bool InitializeThreads() = 0;

            // Fetches one task from the task list and executes it.
            // In this function we do locking and unlocking specific 
            // to the type of threads we are using.
            // Hence, this function is overriden in child class
            // accordingly.
            virtual bool AssignATask() = 0;

            // Finalizes all the threads and cleans them.
            bool FinalizeThreads(); 

            // Is there any free thread for executing task
            bool GetFreeThreadForTaskExecution(std::shared_ptr<IThread>& spThread);

            // get next task for execution
            bool GetNextTaskToAssign(std::shared_ptr<ITask>& spTask);

        protected:
            // Variable to wait for more tasks.
            bool m_bNoMoreTasks = false;

            // List of tasks.
            std::vector<std::shared_ptr<ITask>> m_vecTasks;

            // List of Threads.
            std::vector<std::shared_ptr<IThread>> m_vecThreads;

            // thread count
            int m_iNumberOfThreads = 0;

            // Next task index
            int m_iNextTaskToExecute = 0;

            // all task completed
            bool m_bIsAllTasksCompleted = false;
    };
}

#endif