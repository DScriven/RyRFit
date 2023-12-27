#ifndef TETRAMER_H
#define TETRAMER_H
struct Tetramer
{
    float xcentre;
    float ycentre;
    int angle;
    char classification;
    unsigned int tno;

    Tetramer(float x, float y, int ar, char c) : xcentre(x), ycentre(y), angle(ar), classification(c) {}
    Tetramer() {}
};

#endif // TETRAMER_H

