#include "../include/customexceptions.h"

#include <iostream>
FileNotFoundException::FileNotFoundException(const string& msg) : m_msg(msg)
{
}

FileNotFoundException::~FileNotFoundException() throw ()
{
}

const char* FileNotFoundException::what() const throw()
{
    return m_msg.c_str();
}

FileParseException::FileParseException(const string& msg): m_msg(msg)
{
}

FileParseException::~FileParseException() throw()
{
}

const char* FileParseException::what() const throw()
{
    return m_msg.c_str();
}
