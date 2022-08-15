# ThreadPool-CPP
Generic C++ ThreadPool implementation.

This is a generic Threadpool implementation for C++. The idea here is to use any C++ thread library for threadpool implementation.
In order to use other C++ thread library, one can derive IThread class as shown for C++ thread library in CThread class implementation.

Further, to use the Threadpool for their specific C++ thread library they also need to derive and override the required function of IThreadPool class.

All the operations taht are executed by threads are called Tasks and should be derived from ITask class.

# Threads Class Details
All related codes is under Threads directory.

# ThreadPool Class Details
All related codes is under ThreadPool directory.

# Task Details
All related codes is under Tasks directory.
