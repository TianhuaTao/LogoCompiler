#include "FileWriter.h"
#include "Pixel.h"
FileWriter::FileWriter() {
}

FileWriter::~FileWriter() {
}

size_t FileWriter::WriteBMP(std::string filename, const unsigned char *data, int width, int height) {
    FILE *fp;
    fp = fopen(filename.c_str(), "wb");
    if (!fp) {
        return 0;
    }
    unsigned char *img = nullptr;
    const Pixel *pixels = reinterpret_cast<const Pixel *>(data);
    img = new unsigned char[3 * width * height];
    int size = width * height * sizeof(Pixel);
    int x, y;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            x = i;
            y = (height - 1) - j;
            unsigned char r = pixels[j * width + i].r;
            unsigned char g = pixels[j * width + i].g;
            unsigned char b = pixels[j * width + i].b;

            img[(x + y * width) * 3 + 2] = r;
            img[(x + y * width) * 3 + 1] = g;
            img[(x + y * width) * 3 + 0] = b;
        }
    }

    unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};

    bmpfileheader[2] = (unsigned char)(size);
    bmpfileheader[3] = (unsigned char)(size >> 8);
    bmpfileheader[4] = (unsigned char)(size >> 16);
    bmpfileheader[5] = (unsigned char)(size >> 24);

    bmpinfoheader[4] = (unsigned char)(width);
    bmpinfoheader[5] = (unsigned char)(width >> 8);
    bmpinfoheader[6] = (unsigned char)(width >> 16);
    bmpinfoheader[7] = (unsigned char)(width >> 24);
    bmpinfoheader[8] = (unsigned char)(height);
    bmpinfoheader[9] = (unsigned char)(height >> 8);
    bmpinfoheader[10] = (unsigned char)(height >> 16);
    bmpinfoheader[11] = (unsigned char)(height >> 24);

    fwrite(bmpfileheader, 1, 14, fp);
    fwrite(bmpinfoheader, 1, 40, fp);
    for (int i = 0; i < height; i++) {
        fwrite(img + (width * (height - i - 1) * 3), 3, width, fp);
        fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, fp);
    }

    delete img;
    fclose(fp);
    return 1;
}
