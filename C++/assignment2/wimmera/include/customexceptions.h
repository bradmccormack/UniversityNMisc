#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

//Inline all custom exceptions
#include <string>
#include <exception>
using namespace std;

class FileNotFoundException : public exception
{
public:
    FileNotFoundException(const string& msg);
    virtual ~FileNotFoundException() throw ();
    virtual const char* what() const throw();
private:
    string m_msg;
};


class FileParseException: public exception
{
public:
    FileParseException(const string& msg);
    virtual ~FileParseException() throw();
    virtual const char* what() const throw();
private:
    string m_msg;
};

#endif // EXCEPTIONS_H
