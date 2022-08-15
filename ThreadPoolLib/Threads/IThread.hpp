/**
 * @file IThread.hpp
 * *
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief Thread Utility
 * @version 0.1
 * @date 2022-08-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THREADPOOLLIB_ITHREAD
#define THREADPOOLLIB_ITHREAD

#include "../Common/Common.hpp"
#include "../Tasks/ITask.hpp"

namespace ThreadUtil
{
    #define MAX_IDLE_WAIT_COUNT_FOR_THREADS     10
    #define THREAD_IDLE_SLEEP_TIME              10
    #define TASK_ASSIGNMENT_OVERHEAD            1

    enum ThreadStatus
    {
        ThreadStatus_READY,
        ThreadStatus_RUNNING,
        ThreadStatus_COMPLETED,
        ThreadStatus_TERMINATED,
        ThreadStatus_UNKNOWN
    };

    // Thread Base class.
    class IThread
    {
        public:

            // Constructor(s) and Destructor
            IThread();
            virtual ~IThread();

            // Basic functions
            virtual bool Intialize();
            bool Start();
            virtual bool Finalize();

            // --- Tasks related functions ---
            //// Function to set task
            virtual bool SetTask(std::shared_ptr<ITask>& spTask);
            //// Function to check if all task completed
            bool AreAllTasksCompleted();
            //// Function to check if there is any task to execute
            bool IsTaskAvailable();
            //// Function to set bool indicating all tasks completed
            void SetAllTasksCompleted();
            //// Function to execute a task
            bool ExecuteTask();
            //// Function to clear the task
            void ClearTask();
            //// Function to check if thread available for next task
            bool IsThreadAvailableForNextTask();
            //// Function for handling task completion/failure
            bool OnTaskComplete(TaskStatus eTaskStatus);

            // -- thread utility --
            //// To set thread status
            void SetThreadStatus(bool bThreadStatus);
            //// To get thread status
            ThreadStatus GetThreadStatus();

            // Helping functions
            void IncNoTaskAvailabilityIterationCount();
            int GetNoTaskAvailabilityIterationCount();

            // ** IMPORTANT **
            // Static function that will be executed when the thread starts.
            // Spawned thread should call this function as a starting point.
            static void ThreadTaskExecution(IThread*& spThread);

            // Static sleep function which depends on thread lib
            // **IMP: Override this function as per your thread lib function.
            virtual void Sleep(unsigned long long ullSleepTime /* In milli-seconds */) = 0;

            virtual bool Join() = 0;

        protected:

            bool Run();
            // Termination handling function
            bool Terminate();

            virtual bool OnRun();
            virtual bool OnTerminate();

        protected:
            // self reference pointer
            IThread* m_pThread = NULL;

        private:
            bool m_bNoMoreTasks = false;
            std::shared_ptr<ITask> m_spTask = NULL;
            bool m_bThreadStatus = ThreadStatus_READY;
            int m_iNoTaskAvailableForLastNIteration = 0;
    };
}

#endif