#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>

class FileError : public std::runtime_error {
public:
    explicit FileError(const std::string& message) : std::runtime_error(message) {}
};

class DataError : public std::runtime_error {
public:
    explicit DataError(const std::string& message) : std::runtime_error(message) {}
};

#endif
