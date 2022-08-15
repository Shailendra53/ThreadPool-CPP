/**
 * @file CTestTask.hpp
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ITask.hpp"

class CTestTask: public ITask
{
    private:
        typedef ITask Inherited;

    public:
        CTestTask(TaskStatus eTaskStatus, int iTaskId);
        ~CTestTask();

        virtual bool Execute() override;

    private:
        int m_iTaskId = -1;
};