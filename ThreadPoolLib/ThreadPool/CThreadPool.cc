/**
 * @file CThreadPool.cc
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "CThreadPool.hpp"

#include "../Threads/CThread.hpp"

namespace ThreadUtil
{
    CThreadPool::CThreadPool(int iNumberOfThreads /* = 1*/):
        Inherited(iNumberOfThreads)
    {

    }

    CThreadPool::~CThreadPool()
    {
        
    }

    bool CThreadPool::AddTask(const std::shared_ptr<ITask>& spTask)
    {
        {
            // Take lock and fecth an item to assign.
            m_mtxTaskQueueLock.lock();

            if(spTask) // check for task status as well
            {
                m_vecTasks.push_back(spTask);
            }

            m_mtxTaskQueueLock.unlock();

            m_bIsAllTasksCompleted = false;
        }

        return true;
    }

    bool CThreadPool::AssignATask()
    {
        std::shared_ptr<IThread> spThread = NULL;
        
        bool bRet = GetFreeThreadForTaskExecution(spThread);
        if(!bRet)
        {
            std::cout << "ERROR: GetFreeThreadForTaskExecution() returned error !!"
                        << "Terminating further execution..." << std::endl;
            return bRet;
        }

        std::shared_ptr<ITask> spTask = NULL;

        bRet = GetNextTaskToAssign(spTask);
        if(!bRet)
        {
            std::cout << "ERROR: GetNextTaskToAssign() returned error !!"
                        << "Terminating further execution..." << std::endl;
            return bRet;
        }

        spThread->SetTask(spTask);

        return true;
    }

    bool CThreadPool::InitializeThreads()
    {
        if(m_iNumberOfThreads <= 0)
        {
            std::cout << "Number of threads requested is [" 
                        << m_iNumberOfThreads 
                        << "] is not sufficient to execute tasks."
                        << std::endl;
        }

        bool bRet = true;

        for(int i=0; i<m_iNumberOfThreads; i++)
        {
            std::shared_ptr<IThread> spThread = std::make_shared<CThread>();

            bRet =  spThread->Intialize();
            if(!bRet)
            {
                std::cout << "ERROR: Intialize() returned error !! Terminating further execution..." << std::endl;
                return bRet;
            }

            m_vecThreads.push_back(spThread);
        }

        return bRet;
    }
}