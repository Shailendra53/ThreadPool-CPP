/**
 * @file CThread.hpp
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THREADPOOLLIB_CTHREAD
#define THREADPOOLLIB_CTHREAD

#include "IThread.hpp"
#include <thread>

namespace ThreadUtil
{
    class CThread: public IThread
    {
        public:

            CThread(){}
            ~CThread(){}

            virtual bool Join() override;

            virtual void Sleep(unsigned long long ullSleepTime /* In milli-seconds */) override;

        protected:
            virtual bool OnRun() override;
            virtual bool OnTerminate() override;

        private:
            ULONG m_ulThreadId = 0;
            std::thread m_oThread;
            
    };
} // namespace ThreadUtil

#endif