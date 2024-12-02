#pragma once
#include <iostream>

namespace logger {
    inline void log() { std::cout << "\n"; }

    template <typename T> 
    void log(T t) { std::cout << t << "\033[0m\n"; }

    template <typename First, typename... Rest> 
    void log(First first, Rest... rest) {
        std::cout << first;
        log(rest...);
    }

    // "First" in all these is to prevent function calls with no args
    // because it will prepend the ANSII color code and then go to the first `log()` overload
    // and not reset the color

    // realistically why would you even use this for newlines, use `log()` instead

    template <typename First, typename... Rest> 
    void logWarn(First fmsg, Rest... msgs) {
        std::cout << "\033[93;1m";
        log(fmsg, msgs...);
    }

    template <typename First, typename... Rest> 
    void logInfo(First fmsg, Rest... msgs) {
        std::cout << "\033[92;1m";
        log(fmsg, msgs...);
    }

    template <typename First, typename... Rest> 
    void logErr(First fmsg, Rest... msgs) {
        std::cout << "\033[91;1m";
        log(fmsg, msgs...);
    }
}