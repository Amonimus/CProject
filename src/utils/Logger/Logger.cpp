#pragma once
#include "Logger.h"

#include <iostream>
#include <string>
#include <stdlib.h>

using std::cout, std::wcout, std::endl;
using std::string, std::to_string;

Logger::Logger(){}
Logger::~Logger(){}

template <typename T>
void printvar(T t){
    wcout << t << " ";
}



// Prints message into console
template <typename... T>
void Logger::log(string level, T... msg) {
    // Get timestamp
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    // Print
    cout << timestamp << " - " << level << " - ";
    (printvar(msg), ...);
    cout << endl;
}

// Prints with DEBUG
template <typename... T>
void Logger::debug(T... msg) {
    Logger::log("DEBUG", msg...);
}

// Prints with INFO
template <typename... T>
void Logger::info(T... msg) {
    Logger::log("INFO", msg...);
}

// Prints with ERROR
template <typename... T>
void Logger::error(T... msg) {
    Logger::log("DEBUG", msg...);
}

// Logger instance
Logger logger;