/**
 * @file ITask.hpp
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THREADPOOLLIB_ITASK
#define THREADPOOLLIB_ITASK

#include "../Common/Common.hpp"

enum TaskStatus
{
    TaskStatus_LOADED,
    TaskStatus_RUNNING,
    TaskStatus_COMPLETED,
    TaskStatus_FAILED,
    TaskStatus_UNKNOWN
};

class ITask
{
    public:

        ITask(TaskStatus eTaskStatus)
        {
            m_eTaskStatus = eTaskStatus;
        }

        // This is a task function, every child class has to override this function.
        virtual bool Execute() = 0;
        
        void SetTaskStatus(TaskStatus eTaskStatus)
        {
            m_eTaskStatus = eTaskStatus;
        }

        TaskStatus GetTaskStatus()
        {
            return m_eTaskStatus;
        }

    private:
        TaskStatus m_eTaskStatus = TaskStatus_UNKNOWN;
};

#endif
