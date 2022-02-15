// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <chrono>
#include <random>
#include<thread>

#include "TokenBucket.h"
#include "Rules.h"



int main()
{

    using namespace std::chrono_literals;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, 5);

    int cid = dist(mt);

    TokenBucket* tb = new TokenBucket(cid, 10);


    for (;;)
    {

        tb->AllowRequest(cid, C);
        tb->Summary();

        int value = dist(mt);
        auto time = std::chrono::milliseconds(value);

        std::this_thread::sleep_for(time);
    }


}
