/**
 * @file CThread.cc
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "CThread.hpp"

#include <chrono>

namespace ThreadUtil
{
    bool CThread::OnRun()
    {
        // Starting the thread and don't wait here.
        std::cout << "OnRun!" << std::endl;

        m_oThread = std::thread(IThread::ThreadTaskExecution, std::ref(m_pThread));

        std::cout << "Cheking" << std::endl;

        return true;
    }

    bool CThread::OnTerminate()
    {
        return true;
    }

    bool CThread::Join()
    {
        if(m_oThread.joinable())
        {
            m_oThread.join();
            return true;
        }

        return false;
    }

    void CThread::Sleep(unsigned long long ullSleepTime /* In milli-seconds */)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ullSleepTime));
    }
} // namespace ThreadUtil
