#include <iostream>

int dumbEuclid(int a, int b)
{
    if(a > b)
        return dumbEuclid(a - b, b);
    if(b > a) 
        return dumbEuclid(b - a, a);
    
    return a;
}

int smartEuclid(int a, int b)
{
    if(b == 0) return a;
    return smartEuclid(b, a % b);
}

int expandedEuclid(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return b;
    }

    int gcd = expandedEuclid(b, a % b, x, y);


    int x1 = y;
    int y1 = x - y* (a / b);

    x = x1;
    y = y1;

    return gcd;
}


int main()
{
    
    std::cout << smartEuclid(46, 18);

    return 0;
}