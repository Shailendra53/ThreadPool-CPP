/**
 * @file CTestTask.cc
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "CTestTask.hpp"

#include <chrono>
#include <thread>

CTestTask::CTestTask(TaskStatus eTaskStatus, int iTaskId) :
    Inherited(eTaskStatus)
{
    m_iTaskId = iTaskId;
}

CTestTask::~CTestTask()
{

}

bool CTestTask::Execute()
{
    int i = 0;
    while (i < 5)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        i++;
        std::cout << "1 second done for task " << m_iTaskId << std::endl;
    }

    return true;
}