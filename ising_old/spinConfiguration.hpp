#pragma once

// Initializes the spin configuration with a cold start. Every link
// is set to 1.
std::vector<int> coldStart(const size_t N)
{
    return std::vector<int>(N*N, 1);
}

// Initializes the spin configuration with a hot start. Links are 
// randomly set to either 1 or -1.
void hotStart(std::vector<int> &spin_config)
{   
    //cambiare semplicemente con un +-1 random...
    for (int i = 0; i < spin_config.size(); i++)
    {
        if (randUnif(0., 1.) < 0.5)
            spin_config[i] = -1;
        else
            spin_config[i] = 1;
    }
}
