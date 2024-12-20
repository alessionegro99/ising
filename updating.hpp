#pragma once

std::vector<int> computeBoltzmannWeights(const size_t S_DIM, const double beta){
    std::vector<int> weights_Boltzmann;
    
    for(int i = -S_DIM; i <= S_DIM; i++){
        weights_Boltzmann.push_back(exp(- beta * (4*i)));
    }  
    
    return weights_Boltzmann;
}

double deltaH(std::vector<int> spin_config, const double J, int x, const size_t N)
{
    int dH{0};

    for (int i = 0; i < 2; i++)
    {
        dH += spin_config[(x + i * (N - 1) + 1) % (N * N)] + spin_config[(x - i * (N - 1) - 1) % (N * N)];
    }

    dH = 2 * J * spin_config[x] * dH;

    return dH;
}

double updateMetropolis(std::vector<int> &spin_config, const double J, const double beta, const size_t N)
{
    int accepted_per_sweep{0};

    for (int x = 0; x < N * N; x++)
    {
        if (randUnif(0., 1.) < exp(-beta * deltaH(spin_config, J, x, N)))
        {
            spin_config[x] = -spin_config[x];
            accepted_per_sweep += 1;
        }
    }
    return accepted_per_sweep / double(N * N);
}


void updateHeatbath(std::vector<int> &spin_config, const double J, const double beta, const size_t N)
{
    std::vector<int> spin_config_tmp{spin_config};
    for (int x = 0; x < N * N; x++)
    {   
        spin_config_tmp[x] = 1;
        if (randUnif(0., 1.) < 1/(1 + exp(beta * deltaH(spin_config_tmp, J, x, N))))
            spin_config[x] = 1;
        else
            spin_config[x] = -1;
    }
}