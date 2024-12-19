#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include "random.hpp"
#include "updating.hpp"
#include "io.hpp"
#include "spinConfiguration.hpp"
#include "measurements.hpp"


int main()
{
    const int N{32};
    const double beta{0.1};
    const double J{1.};
    const int Nsweeps{50};
    const int discarded_sweeps {10};

    double m{0.};
    double acceptance_rate{0};

    std::vector<int> spin_config = coldStart(N);

    hotStart(spin_config);

    // printVec(spin_config);

    // std::cout << deltaH(spin_config, 1, 4, N) << std::endl;

    for (int i = 0; i < Nsweeps; i++)
    {
        acceptance_rate += MetropolisSweep(spin_config, J, beta, N);
        
        if (i > discarded_sweeps)
            m += measMagnetization(spin_config);
    }
    std::cout << "Average acceptance rate is : " << acceptance_rate / double(Nsweeps) << "\n";
    std::cout << "Average magnetization is : " << m / double(Nsweeps);

    return 0;
}


