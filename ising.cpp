#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include "updating.hpp"

void IsingInit(std::vector<int> &spin_config);

void printVec(std::vector<int> vec);

double meas_magnetization(std::vector<int> &spin_config, const int N);

int main()
{
    const int N{32};
    const double beta{0.1};
    const double J{1.};
    const int Nsweeps{5000};
    const int discarded_sweeps {1000};

    double m{0.};
    double acceptance_rate{0};

    std::vector<int> spin_config(N * N, 0);

    IsingInit(spin_config);

    // printVec(spin_config);

    // std::cout << deltaH(spin_config, 1, 4, N) << std::endl;

    for (int i = 0; i < Nsweeps; i++)
    {
        acceptance_rate += MetropolisSweep(spin_config, J, beta, N);
        
        if (i > discarded_sweeps)
            m += meas_magnetization(spin_config, N);
    }
    std::cout << "Average acceptance rate is : " << acceptance_rate / double(Nsweeps) << "\n";
    std::cout << "Average magnetization is : " << m / double(Nsweeps);

    return 0;
}

double meas_magnetization(std::vector<int> &spin_config, const int N)
{
    double m{0.};
    for (int x = 0; x < N * N; x++)
    {
        m += spin_config[x];
    }

    return m / double(N * N);
}

double randUnif(double a, double b)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(a, b);

    return dis(gen);
}

void IsingInit(std::vector<int> &spin_config)
{
    for (int i = 0; i < spin_config.size(); i++)
    {
        if (randUnif(0., 1.) < 0.5)
            spin_config[i] = -1;
        else
            spin_config[i] = 1;
    }
}

void printVec(std::vector<int> vec)
{
    for (auto i : vec)
    {
        std::cout << i << " ";
    }
}