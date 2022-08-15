/**
 * @file Common.hpp
 * @author Shailendra Kumar Gupta (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>

// All the typedefs are written here
typedef unsigned long ULONG;

// TODO: 
//Shared Pointer declaration

// Make Shared pointer syntax
#define MAKE_SHARED_PTR(arg1, ...) make_shared<arg1>(...)

// printing thing
#define CONSOLE_OUTPUT(args) std::cout << args << std::endl;