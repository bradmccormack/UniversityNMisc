//
// utility1.h
//
// This header file contains utility  functions
// You can more if you wish
//

#ifndef __UTILITY1_H__
#define __UTILITY1_H__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../include/customexceptions.h"

using namespace std;

void clearInputBuffer();

vector<string> loadFile(string filename) throw (FileNotFoundException);
void saveFile(vector<string> input,string filename);
void strUpper(std::string& s);


//will attempt to convert something into a string
template <class T>
inline string toStr(const T& t)
{
    std::stringstream ss;
    ss <<t;
    return ss.str();
}

//will attempt to convert something into a double
template <class T>
inline double toDouble(const T& t)
{
    std::stringstream is;
    is << t;
    double result;
    is >> result;
    return result;
}


#endif
