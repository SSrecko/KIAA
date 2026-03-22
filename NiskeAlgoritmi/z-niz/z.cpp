#include <iostream>
#include <string>
#include <vector>

std::vector<int> z_arr(std::string a, std::string b)
{
    std::string p = a + "#" + b;
    std::vector<int> z(p.size());

    int l = 0, d = 0;

    for(int i = 1; i < p.size(); i++)
    {
        if(i <= d)
        {
            z[i] = std::min(z[i - l], d - i + 1);
        }

        while(i + z[i] < p.size() && p[i + z[i]] == p[z[i]])
        {
            z[i]++;
        }

        if(i + z[i] > d)
        {
            l = i;
            d = i + z[i] - 1;
        }
    }

    return z;

}


int main()
{
    return 0;
}