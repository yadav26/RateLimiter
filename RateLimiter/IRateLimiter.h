#pragma once
#include "Rules.h"

class IRateLimiter
{

public:
	virtual bool AllowRequest(int clientid, RequestWeight req) = 0;
};

