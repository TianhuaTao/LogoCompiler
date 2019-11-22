#include <cstdlib>
#include <cstring>
#include <iostream>
int w = 1000;
int h = 1000;
int red[1000][1000];
int green[1000][1000];
int blue[1000][1000];
int x, y;
int r, g, b;
int main(int argc, char const *argv[]) {
    for (size_t i = 0; i < 1000; i++) {
        if (i % 200 < 100)
            continue;
        for (size_t k = 0; k < 1000; k++) {
            red[i][k] = 1;
            green[i][k] = 1;
            blue[i][k] = 1;
        }
    }

    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3 * w * h; //w is your image width, h is image height, both int

    img = (unsigned char *)malloc(3 * w * h);
    std::memset(img, 0, 3 * w * h);

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            x = i;
            y = (h - 1) - j;
            r = red[i][j] * 200;
            g = green[i][j] * 40;
            b = blue[i][j] * 40;
            if (r > 255)
                r = 255;
            if (g > 255)
                g = 255;
            if (b > 255)
                b = 255;
            img[(x + y * w) * 3 + 2] = (unsigned char)(r);
            img[(x + y * w) * 3 + 1] = (unsigned char)(g);
            img[(x + y * w) * 3 + 0] = (unsigned char)(b);
        }
    }

    unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w >> 8);
    bmpinfoheader[6] = (unsigned char)(w >> 16);
    bmpinfoheader[7] = (unsigned char)(w >> 24);
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h >> 8);
    bmpinfoheader[10] = (unsigned char)(h >> 16);
    bmpinfoheader[11] = (unsigned char)(h >> 24);

    f = fopen("img.bmp", "wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    for (int i = 0; i < h; i++) {
        fwrite(img + (w * (h - i - 1) * 3), 3, w, f);
        fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
    }

    free(img);
    fclose(f);
    return 0;
}
