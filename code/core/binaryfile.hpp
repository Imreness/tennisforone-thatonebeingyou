#include <iostream>
#include <fstream>
#include <string>

//Sidenote:
//for smaller projects it is possible to do this by hand, but this speeds up work by such a large margin.

//Helping class to ease work with storing and loading data bit-by-bit. Theres a brick-by-brick joke there somewhere.
class binaryFile{
public:

    std::fstream m_file;

    template <typename T>
    void write(T data){
        m_file.write((char*)&data, sizeof(T));
    }

    template <typename T>
    void write(T data, int seekTo){
        m_file.seekp(seekTo);
        m_file.write((char*)&data, sizeof(T));
    }

    void writeChars(const char* data, std::size_t size){
        m_file.write(data, size);
    }

    void writeChars(char* data, std::size_t size){
        m_file.write(data, size);
    }

    void writeChars(unsigned char* data, std::size_t size){
        m_file.write((char*)data, size);
    }


    template <typename T>
    T read(){
        char* datachar = new char[sizeof(T)];
        T data;
        m_file.read(datachar, sizeof(T));
        data = *(T*)datachar;
        delete[] datachar;
        return data;
    }


    template <typename T>
    T read(std::size_t size){
        char* datachar = new char[size];
        T data;
        m_file.read(datachar, size);
        data = *(T*)datachar;
        delete[] datachar;
        return data;
    }


    char* readChars(std::size_t size);

    void open(const char* path, bool write);

    void close();
};