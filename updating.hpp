#pragma once

#include "random.hpp"

double deltaH(std::vector<int> spin_config, const double J, int x, int N){
    int dH{0};

    for (int i = 0; i < 2; i++)
    {
        dH += spin_config[(x + i * (N - 1) + 1) % (N * N)] + spin_config[(x - i * (N - 1) - 1) % (N * N)];
    }

    dH = 2 * J * spin_config[x] * dH;

    return dH;
}

double MetropolisSweep(std::vector<int> &spin_config, const double J, const double beta, const int N)
{
    int dH{0};
    int accepted_per_sweep{0};

    for (int x = 0; x < N * N; x++)
    {
        dH = deltaH(spin_config, J, x, N);
        if (randUnif(0., 1.) < exp(-beta * dH))
        {
            spin_config[x] = -spin_config[x];
            accepted_per_sweep += 1;
        }
    }
    return accepted_per_sweep / double(N * N);
}