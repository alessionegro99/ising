#pragma once

// Measures the total magnetization M of a given spin configuration.
// The magnetization per unit volume can then be obtained dividing i 
// the total volume.
double measMagnetization(std::vector<int> &spin_config)
{
    int total_size{int(spin_config.size())};
    int tot_magnetization{0};

    for (int x = 0; x < total_size; x++)
    {
        tot_magnetization += spin_config[x];
    }

    return tot_magnetization;
}

// Measures the total energy E of a given spin configuration with interaction 
// strength J. The energy per unit volume can then be obtained dividing by
// the total volume. 
double measEnergy(std::vector<int> &spin_config, const double J, const size_t N)
{
    int tot_size{int(spin_config.size())};
    double tot_energy{0.};
    int neigh_sum{0};
    const int S_DIM{2};

    for (int x = 0; x < tot_size; x++)
    {
        neigh_sum = {0};
        for (int i = 0; i < S_DIM; i++)
        {
            neigh_sum += spin_config[(x + i * (N - 1) + 1) % int(pow(N, S_DIM))] + spin_config[(x - i * (N - 1) - 1) % int(pow(N, S_DIM))];
        }

        tot_energy += spin_config[x] * neigh_sum;
    }

    return -J * double(tot_energy);
}