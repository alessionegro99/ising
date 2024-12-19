#pragma once

double measMagnetization(std::vector<int> &spin_config)
{
    int total_size = spin_config.size();
    double m{0.};
    for (int x = 0; x < total_size; x++)
    {
        m += spin_config[x];
    }

    return m / double(total_size);
}
