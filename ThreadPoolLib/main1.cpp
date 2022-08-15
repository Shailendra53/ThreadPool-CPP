/**
 * @file main1.cpp
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief This is the main file which shows how we can use ThreadPool 
 * 			in our code to perform multiple tasks parallely.
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Threads/CThread.hpp"
#include "Tasks/CTestTask.hpp"

#include "ThreadPool/CThreadPool.hpp"

bool ThreadPoolFunction()
{
	ThreadUtil::CThreadPool oThreadPool(5);
	
	bool bRet = true;

	std::vector<std::shared_ptr<ITask>> vecTasks;

	for(int i=0; i<10; i++)
	{
		std::shared_ptr<ITask> spTask = std::make_shared<CTestTask>(TaskStatus::TaskStatus_LOADED, i);
		vecTasks.push_back(spTask);
	}

	bRet = oThreadPool.Initialize();
	if(!bRet)
	{
		std::cout << "ERROR: Intialize() returned error !! Terminating further execution..." << std::endl;
		return bRet;
	}

	bRet = oThreadPool.AddTasks(vecTasks);
	if(!bRet)
	{
		std::cout << "ERROR: AddTasks() returned error !! Terminating further execution..." << std::endl;
		return bRet;
	}

	oThreadPool.SetNoMoreTasks();

	bRet = oThreadPool.Run();
	if(!bRet)
	{
		std::cout << "ERROR: Run() returned error !! Terminating further execution..." << std::endl;
		return bRet;
	}

	bRet = oThreadPool.Finalize();
	if(!bRet)
	{
		std::cout << "ERROR: Finalize() returned error !! Terminating further execution..." << std::endl;
		return bRet;
	}

	return bRet;
}

int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;
	std::cout << "Starting ThreadUtil check!" << std::endl;

	bool bRet = ThreadPoolFunction();
	if(!bRet)
	{
		std::cout << "ERROR: ThreadCheckFuntion Failed!" << std::endl;
	}

	return 0;
}

