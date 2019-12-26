#if !defined(FILEWRITER_H)
#define FILEWRITER_H
#include <string>
extern bool verbose;
class FileWriter {
private:
public:
    FileWriter();
    ~FileWriter();
    size_t WriteBMP(std::string filename, const unsigned char *data, int width, int height);
};

#endif // FILEWRITER_H
