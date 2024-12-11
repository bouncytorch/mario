#pragma once
#include <iostream>
namespace logger {
    template <typename... Messages> 
    void log(Messages&&... rest) 
    {
        (std::cout << ... << rest) << "\033[0m\n";
    }

    #ifdef NDEBUG
    inline void logWarn(...) {}
    inline void logInfo(...) {}
    #else
    template <typename... Msgs> 
    void logWarn(Msgs&&... msgs) 
    {
        log("\033[93;1m", msgs...);
    }

    template <typename... Msgs> 
    void logInfo(Msgs&&... msgs) 
    {
        log("\033[92;1m", msgs...);
    }
    #endif

    template <typename... Msgs> 
    void logErr(Msgs&&... msgs) 
    {
        log("\033[91;1m", msgs...);
    }
}

