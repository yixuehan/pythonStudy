#pragma once
#include <exception>
#include <string_view>
#include <string>

class Fatal : public std::exception
{
public:
    Fatal(std::string &&msg)
        :_msg(std::move(msg))
    {
    }
    virtual const char *what() const noexcept override
    {
        return _msg.c_str();
    }
private:
    std::string _msg;
};
