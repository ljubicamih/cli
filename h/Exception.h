//
// Created by User on 02.03.2026..
//

#ifndef PROJEKAT_EXCEPTION_H
#define PROJEKAT_EXCEPTION_H
#include <exception>
#include <string>


class Exception : public std::exception {
public:
    explicit Exception(const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message;
};


#endif //PROJEKAT_EXCEPTION_H