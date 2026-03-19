#include <vector>

using namespace std;

vector<int> eratosten(int n) 
{
    vector<int> najmanjiCinilac(n + 1);
    for (int i = 1; i <= n; i++)
    {
        if(i % 2 == 0)
            najmanjiCinilac[i] = 2;
        else
            najmanjiCinilac[i] = i;
    }
    najmanjiCinilac[1] = 1;
        
    for (int d = 3; d * d <= n; d++)
        if (najmanjiCinilac[d] == d)
            for (int i = d * d; i <= n; i += 2 * d)
                if (najmanjiCinilac[i] == i)
                    najmanjiCinilac[i] = d;


    return najmanjiCinilac;
}