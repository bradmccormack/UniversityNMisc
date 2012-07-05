#include "../include/utility1.h"


////////////////////////////////////////////
void clearInputBuffer()     // function to clear the input buffer
{
    char symbol;
    do
    {
        cin.get(symbol);
    }
    while(symbol != '\n');
}

//method to save the vector of strings to a file
void saveFile(vector<string> data,string filename)
{
    ofstream outfile;
    outfile.open(filename.c_str());
    //open the output stream and write the data. Overwrite the destination file
    for(unsigned int i=0; i<data.size(); i++)
    {
        outfile << data.at(i)<<endl;
    }
    outfile.close();
}

//method to load in text file and return vector of strings for parsing by the model
vector<string> loadFile(string filename) throw (FileNotFoundException)
{
    ifstream inStream;
    vector<string> contents;
    char bytes[256];

    inStream.open(filename.c_str());
    if(inStream.fail())
    {
        throw FileNotFoundException(string("File not found: " + filename));
    }
    while(!inStream.eof())
    {
        inStream.getline(bytes,256);
        string lineread=string(bytes);
        if(lineread!="")
        {
            contents.push_back(lineread);
        }
    }
    inStream.close();
    return contents;
}

//will uppercase any string sent to the function
void strUpper(std::string& s)
{
    std::string::iterator i = s.begin();
    std::string::iterator end = s.end();

    while (i != end)
    {
        *i = std::toupper((unsigned char)*i);
        ++i;
    }
}




