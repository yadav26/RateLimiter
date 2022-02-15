#pragma once
#include "IRateLimiter.h"
#include <thread>
#include <map>
#include <mutex>

class TokenBucket :
    public IRateLimiter
{
    inline static std::map<int, TokenBucket*> TokenCache;

    int mClientId;
    int mResetTokens;
    int mBucketWeight;
    int mRate; //10 tokens per second - that means 1 token each millisecond 1000ms = 1s, 100 ms got 1 token 

    std::chrono::time_point<std::chrono::system_clock> mTpBucketLastFilled =
        std::chrono::system_clock::now();
    
    std::chrono::time_point<std::chrono::system_clock> mTpLastQueryReq;

    std::mutex mMutex;

    long mAccepted = 0;
    long mRejected = 0;

public:
    TokenBucket(int clientid, int tokens);

    bool AllowRequest(int cid, RequestWeight req)override;
    void Summary();

};

