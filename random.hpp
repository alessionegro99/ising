#pragma once

// generates a random number uniformly distributed in the interval
// [a, b).
double randUnif(double a, double b)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(a, b);

    return dis(gen);
}
