#pragma once
constexpr int DEFAULT_RESET_INTERVAL_MSEC = 1000;//msec

enum RequestWeight {
    C = 0,
    R,
    U,
    D

};

struct tReqW
{
    static int getWeight(RequestWeight req)
    {
        switch (req)
        {
        case C: return 1;
        case R: return 2;
        case U: return 3;
        case D: return 4;
        default:return 0;
        }
    }
};