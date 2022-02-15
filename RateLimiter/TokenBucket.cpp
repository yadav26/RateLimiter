#include "TokenBucket.h"
#include "Rules.h"
#include <iostream>



TokenBucket::TokenBucket(int clientid, int tokens) : 
    mClientId(clientid), 
    mResetTokens(tokens), 
    mBucketWeight(tokens),
    mRate(10)
{
    if (TokenCache.find(clientid) == TokenCache.end())
    {
        TokenCache[mClientId] = this;
    }
}

void TokenBucket::Summary()
{
    std::cout << "\n Accepted :" << mAccepted << ".  Rejected :" << mRejected;
}

bool TokenBucket::AllowRequest(int cid, RequestWeight req)
{
    std::lock_guard lock(mMutex);
    
    std::chrono::time_point<std::chrono::system_clock> recent = std::chrono::system_clock::now();
    
    auto elapsed = std::chrono::duration_cast< std::chrono::milliseconds> (recent - mTpLastQueryReq).count();

    if (elapsed >= DEFAULT_RESET_INTERVAL_MSEC)
    {
        mBucketWeight = mResetTokens;
        mBucketWeight -= tReqW::getWeight(req);
        mTpLastQueryReq = recent;
        ++mAccepted;
        return true;
    }

    int fill = (mRate * elapsed) / 1000;

    if (mBucketWeight + fill > mResetTokens)
        mBucketWeight = mResetTokens;
    else
        mBucketWeight += fill;

    if (mBucketWeight >= tReqW::getWeight(req))
    {
        mBucketWeight -= tReqW::getWeight(req);
        mTpLastQueryReq = recent;
        ++mAccepted;
        return true;
    }
    ++mRejected;
    
    // no sufficient token to process request. Err 502 or 429
    return false;
}
