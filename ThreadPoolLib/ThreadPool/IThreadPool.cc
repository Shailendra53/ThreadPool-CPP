/**
 * @file IThreadPool.cc
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "IThreadPool.hpp"

namespace ThreadUtil
{
    // By default thread pool has 1 thread.
    IThreadPool::IThreadPool(int iNumberOfThreads /* = 1 */)
    {
        // Constructor
        m_iNumberOfThreads = iNumberOfThreads;
    }

    IThreadPool::~IThreadPool()
    {
        // Destructor
    }

    bool IThreadPool::Initialize()
    {
        // Initialize the threads.
        bool bRet = true;
        bRet = InitializeThreads();

        return bRet;
    }

    // Run function.
    // Desc: 
    // 1. If no threads return directly
    // 2. Start all the initialized threads
    //      Assign all tasks in loop. Once all tasks are done
    //      wait for all threads to join.
    bool IThreadPool::Run()
    {
        bool bRet = true;

        CONSOLE_OUTPUT("Starting all threads...")

        if(m_iNumberOfThreads <= 0)
        {
            std::cout << "Number of threads requested is [" 
                        << m_iNumberOfThreads 
                        << "] is not sufficient to execute tasks."
                        << std::endl;

            return true;
        }

        for(int i=0; i<m_iNumberOfThreads; i++)
        {
            bRet = m_vecThreads[i]->Start();
            if(!bRet)
            {
                std::cout << "ERROR: Start() returned error !! Terminating further execution..." << std::endl;
                return bRet;
            }
        }

        while(!m_bNoMoreTasks || !m_bIsAllTasksCompleted)
        {
            // Fetch a task from the list and execute it.
            bool bRet = AssignATask();

            if(!bRet)
            {
                CONSOLE_OUTPUT("ERROR! AssignTask() Failed")
                continue;
            }

            m_iNextTaskToExecute++;

            if((size_t)m_iNextTaskToExecute == m_vecTasks.size())
            {
                m_bIsAllTasksCompleted = true;
            }
        }

        for(int i=0; i<m_iNumberOfThreads; i++)
        {
            m_vecThreads[i]->SetAllTasksCompleted();
        }

        for(int i=0; i<m_iNumberOfThreads; i++)
        {
            m_vecThreads[i]->Join();
        }

        return bRet;
    }

    // finalize
    bool IThreadPool::Finalize()
    {
        // Finalize the threads.
        bool bRet = true;
        bRet = FinalizeThreads();

        return bRet;
    }
    
    // To set no more tasks available.
    // It helps in stopping the run function
    // This should be set when all the tasks are added 
    // to the threadpool tasks list.
    void IThreadPool::SetNoMoreTasks()
    {
        m_bNoMoreTasks = true;
    }

    // Function to add multiple tasks to together in the task list
    bool IThreadPool::AddTasks(std::vector<std::shared_ptr<ITask>>& vecTasks)
    {
        {   
            for(const std::shared_ptr<ITask>& spTask: vecTasks)
            {
                bool bRet = AddTask(spTask);
                if(!bRet)
                {
                    CONSOLE_OUTPUT("Failed to add task");
                }
            }
        }

        return true;
    }

    // Get a free thread for executing next task.
    bool IThreadPool::GetFreeThreadForTaskExecution(std::shared_ptr<IThread>& spThread)
    {
        while(spThread == NULL)
        {
            for(int i=0; i<m_iNumberOfThreads; i++)
            {
                if(m_vecThreads[i]->IsThreadAvailableForNextTask())
                {
                    spThread = m_vecThreads[i];
                    break;
                }
            }
        }

        return true;
    }

    // get next available task for execuation.
    bool IThreadPool::GetNextTaskToAssign(std::shared_ptr<ITask>& spTask)
    {
        if(m_iNextTaskToExecute >= m_vecTasks.size())
        {
            CONSOLE_OUTPUT("No more tasks available in list.. Waiting for new tasks!!")
            return false;
        }

        spTask = m_vecTasks[m_iNextTaskToExecute];

        return true;
    }

    // Finalizes all the threads and cleans them.
    bool IThreadPool::FinalizeThreads()
    {
        if(m_iNumberOfThreads <= 0)
        {
            std::cout << "Number of threads in threadpool is [" 
                        << m_iNumberOfThreads 
                        << "] is not sufficient to execute tasks."
                        << std::endl;
        }

        bool bRet = true;

        for(int i=0; i<m_iNumberOfThreads; i++)
        {
            bRet = m_vecThreads[i]->Finalize();
            if(!bRet)
            {
                std::cout << "ERROR: Finalize() returned error !! Terminating further execution..." << std::endl;
                return bRet;
            }
        }

        return bRet;
    }

} // namespace ThreadUtil
