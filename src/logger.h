#pragma once
#include <iostream>
namespace logger {
    template <typename... Messages> 
    void log(Messages&&... rest) {
        (std::cout << ... << rest) << "\033[0m\n";
    }

    // "First" in all these is to prevent function calls with no args
    // because it will prepend the ANSII color code and then go to the first `log()` overload
    // and not reset the color

    // realistically why would you even use this for newlines, use `log()` instead
    #ifdef DEBUG
    template <typename First, typename... Rest> 
    void logWarn(First&& fmsg, Rest&&... msgs) {
        std::cout << "\033[93;1m";
        log(fmsg, msgs...);
    }

    template <typename First, typename... Rest> 
    void logInfo(First&& fmsg, Rest&&... msgs) {
        std::cout << "\033[92;1m";
        log(fmsg, msgs...);
    }

    #else
    inline void logWarn(...) {}
    inline void logInfo(...) {}
    #endif

    template <typename First, typename... Rest> 
    void logErr(First&& fmsg, Rest&&... msgs) {
        std::cout << "\033[91;1m";
        log(fmsg, msgs...);
    }
}

