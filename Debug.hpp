#ifndef DEBUG
#include <random>
#endif

#ifdef DEBUG

#pragma message("Using a custom pRNG...")

/****
* pRNG based on http://www.cs.wm.edu/~va/software/park/park.html
*****/

#define MODULUS 2147483647                  
#define MULTIPLIER 48271
#define DEFAULT 123456789

static long seed = DEFAULT;

double Random(void)
/* ----------------------------------------------------------------
 * Random returns a pseudo-random real number uniformly distributed
 * between 0.0 and 1.0.
 * ----------------------------------------------------------------
 */
{
    const long Q = MODULUS / MULTIPLIER;
    const long R = MODULUS % MULTIPLIER;
    long t;

    t = MULTIPLIER * (seed % Q) - R * (seed / Q);
    if (t > 0)
    {
        seed = t;
    }
    else
    {
        seed = t + MODULUS;
    }
    return ((double)seed / MODULUS);
}

#else

std::random_device r;
std::default_random_engine engine(r());
std::uniform_real_distribution<datatype> uniform(0.0, 1.0);

#endif