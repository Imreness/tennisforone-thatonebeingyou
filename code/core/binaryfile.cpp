#include <core/binaryfile.hpp>

char* binaryFile::readChars(std::size_t size){
    char* data = new char[size];
    m_file.read(data, size);
    return data;
}

void binaryFile::open(const char* path, bool write){
    if(write)
        m_file.open(path , std::ios::binary | std::ios::out);
    else
        m_file.open(path , std::ios::binary | std::ios::in);
}

void binaryFile::close(){
    m_file.close();
}