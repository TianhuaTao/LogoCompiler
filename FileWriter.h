#include <string>

class FileWriter
{
private:
    
public:
    FileWriter();
    ~FileWriter();
    size_t WriteBMP(std::string filename, const char* data, size_t size);
};

