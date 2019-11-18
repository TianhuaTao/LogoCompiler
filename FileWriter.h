#include <string>

class FileWriter
{
private:
    
public:
    FileWriter();
    ~FileWriter();
    size_t WriteBMP(std::string filename, const unsigned char* data, int width, int height);
};

