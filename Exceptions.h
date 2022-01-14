#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

class InvalidInput : public std::exception
{
};

class NullArg : public std::exception
{
};

class NotExist : public std::exception
{
};

class AlreadyExist : public std::exception
{
};

class OutOfBounds : public std::exception
{
};

class FAIL : public std::exception
{
};

#endif