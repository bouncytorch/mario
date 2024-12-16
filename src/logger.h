#pragma once
#include <iostream>

namespace logger {
    template <typename... Messages> 
    void print(Messages&&... rest) 
    {
        (std::cout << ... << rest) << "\033[0m\n";
    }

    template <typename... Msgs> 
    void printWarn(Msgs&&... msgs) 
    {
        print("\033[93;1m", msgs...);
    }

    template <typename... Msgs> 
    void printInfo(Msgs&&... msgs) 
    {
        print("\033[92;1m", msgs...);
    }

    template <typename... Msgs> 
    void printErr(Msgs&&... msgs) 
    {
        print("\033[91;1m", msgs...);
    }
}

#define LOGERROR(args...) logger::printErr(args)
#ifndef NDEBUG
#define LOGWARN(args...) logger::printWarn(args)
#define LOGINFO(args...) logger::printInfo(args)
#else 
#define LOGWARN(args...)
#define LOGINFO(args...)
#endif