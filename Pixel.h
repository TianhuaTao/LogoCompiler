struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char alpha;

    Pixel(){}
    Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) : r(r), g(g), b(b), alpha(alpha) {
    }
};