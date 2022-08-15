/**
 * @file IThread.cc
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "IThread.hpp"

namespace ThreadUtil
{
    IThread::IThread()
    {

    }

    IThread::~IThread()
    {

    }

    bool IThread::Intialize()
    {
        m_pThread = this;

        return true;
    }

    bool IThread::Finalize()
    {
        m_pThread = NULL;
        
        return true;
    }

    bool IThread::Run()
    {
        bool bRet = true;

        bRet = OnRun();
        if(!bRet)
        {
            std::cout << "ERROR: OnStart() returned error !! Terminating task execution..." << std::endl;
            bRet = Terminate();
        }

        return bRet;
    }

    bool IThread::Start()
    {
        bool bRet = true;

        bRet = Run();
        if(!bRet)
        {
            std::cout << "ERROR: Start() returned error !! Terminating further Start execution..." << std::endl;
            bRet = Terminate();

            return bRet;
        }

        m_bThreadStatus = ThreadStatus_COMPLETED;

        std::cout << "SUCCESS: Thread started successfully !!!" << std::endl;

        return bRet;
    }

    bool IThread::Terminate()
    {
        bool bRet = true;

        bRet = OnTerminate();
        if(!bRet)
        {
            std::cout << "ERROR: Terminate() returned error !! Bringing down the thread..." << std::endl;
        }

        return bRet;
    }

    bool IThread::SetTask(std::shared_ptr<ITask>& pTask)
    {
        // Set the task only if thread is ready to run tasks
        // and the previous task is cleared after it's execution
        // otherwise avoid setting the task and return error.
        if(m_bThreadStatus == ThreadStatus_READY && !IsTaskAvailable())
        {
            m_spTask = pTask;
            return true;
        }

        return false;
    }

    bool IThread::AreAllTasksCompleted()
    {
        return m_bNoMoreTasks;
    }

    bool IThread::IsTaskAvailable()
    {
        if(m_spTask)
            return true;

        return false;
    }

    void IThread::SetAllTasksCompleted()
    {
        m_bNoMoreTasks = true;
    }

    bool IThread::ExecuteTask()
    {
        if(!m_spTask)
        {
            std::cout << "There is no task to execute !!!" << std::endl;
            return true;
        }

        std::cout << "Task Execution Started..." << std::endl;

        // Execute the task
        bool bRet = m_spTask->Execute();
        if(!bRet)
        {
            std::cout << "ERROR: Task execution returned error !! Marking the task failed." << std::endl;
            return false;
        }

        std::cout << "Task Execution Successfully..." << std::endl;

        return true;
    }

    bool IThread::OnTaskComplete(TaskStatus eTaskStatus)
    {
        // Do if anything required

        // Set the task status
        m_spTask->SetTaskStatus(eTaskStatus);

        return true;
    }

    void IThread::SetThreadStatus(bool bThreadStatus)
    {
        m_bThreadStatus = bThreadStatus;
    }

    void IThread::ClearTask()
    {
        m_spTask = NULL;
    }

    bool IThread::IsThreadAvailableForNextTask()
    {
        if(m_bThreadStatus == ThreadStatus_READY && !IsTaskAvailable())
        {
            return true;
        }

        return false;
    }

    void IThread::IncNoTaskAvailabilityIterationCount()
    {
        m_iNoTaskAvailableForLastNIteration++;
    }

    int IThread::GetNoTaskAvailabilityIterationCount()
    {
        return m_iNoTaskAvailableForLastNIteration;
    }

    bool IThread::OnRun()
    {
        return true;
    }

    bool IThread::OnTerminate()
    {
        // Setting the status of thread as TERMINATED
        m_bThreadStatus = ThreadStatus_TERMINATED;
        return true;
    }

    void IThread::ThreadTaskExecution(IThread*& spThread)
    {
        bool bRet = true;
        
        while(!spThread->AreAllTasksCompleted() || spThread->IsTaskAvailable())
        {
            if(spThread->IsTaskAvailable())
            {
                // Put the thread in RUNNING state.
                spThread->SetThreadStatus(ThreadStatus_RUNNING);

                bRet = spThread->ExecuteTask();
                if(!bRet)
                {
                    // Need to handle the case when task fails.
                    std::cout << "Task Failed.. " << std::endl;

                    spThread->OnTaskComplete(TaskStatus::TaskStatus_FAILED);
                }
                else
                {
                    std::cout << "Task Completed Successfully.. " << std::endl;

                    spThread->OnTaskComplete(TaskStatus::TaskStatus_COMPLETED);
                }

                // clear the task reference after completing the task.
                spThread->ClearTask();

                // Set the Thread status back to READY.
                spThread->SetThreadStatus(ThreadStatus_READY);

                // 1s delay for task assignment overhead.
                spThread->Sleep(TASK_ASSIGNMENT_OVERHEAD * 1000);
            }
            else
            {
                // We need to wait for sometime before checking for new tasks again.
                // If there are no more tasks for N times, we will bring down the 
                // thread assuming user is not supplying more tasks but case of
                // no task is not handled properly.
                
                spThread->IncNoTaskAvailabilityIterationCount();

                if(spThread->GetNoTaskAvailabilityIterationCount() > MAX_IDLE_WAIT_COUNT_FOR_THREADS)
                {
                    // Break out of the loop as no more tasks supplied for Last N*T Seconds 
                    // So bringing down the thread as it is consuming resources unnecessarily

                    std::cout << "No more tasks available for last " 
                                << spThread->GetNoTaskAvailabilityIterationCount() * THREAD_IDLE_SLEEP_TIME
                                << " seconds, bringing down the thread"
                                << std::endl;
                    break;
                }

                spThread->Sleep(THREAD_IDLE_SLEEP_TIME * 1000);
            }
        }

        std::cout << "All tasks for this thread attempted, bringing down the thread !!" << std::endl;
    }
} // namespace ThreadUtil
