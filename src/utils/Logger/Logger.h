#pragma once
#include <string>

using std::string;

class Logger{
    public:
        Logger();
        ~Logger();

        template <typename... T>
        void debug(T... msg);
        template <typename... T>
        void info(T... msg);
        template <typename... T>
        void error(T... msg);
    private:
        template <typename... T>
        void log(string level, T... msg);
};