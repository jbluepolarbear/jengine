#ifndef MATH_UTILS_H
#define MATH_UTILS_H

unsigned nextPowerOf2(unsigned number)
{
    unsigned powOf2 = 1;
    while (powOf2 < number)
    {
        powOf2 <<= 1;
    }
    return powOf2;
}

#endif//MATH_UTILS_H
