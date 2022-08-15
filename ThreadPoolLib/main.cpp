/**
 * @file main.cpp
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief File showing how to use Threads in your program.
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Threads/CThread.hpp"
#include "Tasks/CTestTask.hpp"

bool ThreadCheckFunction()
{
	std::shared_ptr<ThreadUtil::CThread> ptrThread = std::make_shared<ThreadUtil::CThread>();
	
	bool bRet = true;

	bRet = ptrThread->Intialize();
	if(!bRet)
	{
		std::cout << "ERROR: Intialize() returned error !! Terminating further execution..." << std::endl;
		return bRet;
	}

	std::shared_ptr<ITask> pTask1 = std::make_shared<CTestTask>(TaskStatus::TaskStatus_LOADED, 1);
	bRet = ptrThread->SetTask(pTask1);
	if(!bRet)
	{
		std::cout << "ERROR: SetTask() returned error !! Terminating further execution..." << std::endl;
		return bRet;
	}

	bRet = ptrThread->Start();
	if(!bRet)
		return bRet;

	std::shared_ptr<ITask> pTask2 = std::make_shared<CTestTask>(TaskStatus::TaskStatus_LOADED, 2);
	while(!ptrThread->SetTask(pTask2));

	ptrThread->SetAllTasksCompleted();

	std::cout << "Let's wait for thread now!" << std::endl;
	ptrThread->Join();

	CONSOLE_OUTPUT("Checking Task Status")
	CONSOLE_OUTPUT("Task 1 status: ")
	CONSOLE_OUTPUT(pTask1->GetTaskStatus())
	CONSOLE_OUTPUT("Task 2 status: ")
	CONSOLE_OUTPUT(pTask2->GetTaskStatus())

	bRet = ptrThread->Finalize();
	if(!bRet)
	{
		std::cout << "ERROR: Finalize() returned error !! Failed to finalize, skipping further Finalize() logic..." << std::endl;
		return bRet;
	}

	return bRet;
}

int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;
	std::cout << "Starting ThreadUtil check!" << std::endl;

	bool bRet = ThreadCheckFunction();
	if(!bRet)
	{
		std::cout << "ERROR: ThreadCheckFuntion Failed!" << std::endl;
	}

	return 0;
}

