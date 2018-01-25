#pragma once
#ifndef SET_TIMEOUT_HPP
#define SET_TIMEOUT_HPP
#include <windows.h>//different header file in linux
#include <future>
#include <chrono>
#include <thread>
using namespace std;

/**
 * \brief https://stackoverflow.com/questions/2485058/equivalent-to-window-settimeout-for-c
 * https://stackoverflow.com/questions/4184468/sleep-for-milliseconds/10613664#10613664
 * \tparam ParamTypes 
 * \param milliseconds 
 * \param func 
 * \param parames 
 */
template <typename... ParamTypes>
void set_time_out(const int milliseconds,std::function<void(ParamTypes...)> func,ParamTypes... parames)
{   
    std::async(std::launch::async,[=]()
    {       
        //Sleep(milliseconds);
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    	func(parames...); 
    });
    };
#endif
