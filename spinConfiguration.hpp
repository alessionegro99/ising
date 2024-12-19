#pragma once

std::vector<int> coldStart(const size_t N)
{
    return std::vector<int>(N*N, 1);
}

void hotStart(std::vector<int> &spin_config)
{
    for (int i = 0; i < spin_config.size(); i++)
    {
        if (randUnif(0., 1.) < 0.5)
            spin_config[i] = -1;
        else
            spin_config[i] = 1;
    }
}
