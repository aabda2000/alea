#include <cstdlib>
#include <iostream>
using namespace std;

// Drawing a random number between [0, N-1]
static const uint32_t N_FACE = 6;
static int nBits;

static uint64_t count = 0, word = 0;
static int pos = 0;
int flip(void)
{
    if (pos == 0)
    {
        word = rand();
        pos = 32;
    }
    count++;
    pos--;
    return (word & (1 << pos)) >> pos;
}

int countBits(int nb)
{
    int count = 0, i;
    if (nb == 0)
        return 0;
    for (i = 0; i < 32; i++)
    {
        if ((1 << i) & nb)
            count = i;
    }

    return ++count;
}
uint32_t draw_random_number(unsigned int n)
{
    uint32_t c = 0;
    int round = 1;

    while (true)
    {
        while (round++ <= nBits)
            c = (c << 1) + flip();

        if (c < n)
            return c;
        else
        {
            c = 0;
            round = 1;
        }
    }
}
int main()
{
    srand(time(0));
    nBits = countBits(N_FACE);
    double nRolls = 10000000.0;
    int nRounds = nRolls;
    uint32_t nFace[7] = {0};
    uint32_t face;

    while (nRounds-- > 0)
    {
        face = 1 + draw_random_number(N_FACE);
        nFace[face]++;
    }
    cout << endl;

    double sum = 0;
    int i;
    for (i = 1; i < 7; i++)
        sum = sum + nFace[i] / (double)nRolls;
    cout << "sum=" << sum << endl;
    for (int i = 1; i < 7; i++)
        cout << i << ":" << 100 * nFace[i] / nRolls << ", ";
    cout << endl;
    return 0;
}