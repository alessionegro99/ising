#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <map>
#include <string>

#include "random.hpp"
#include "updating.hpp"
#include "io.hpp"
#include "spinConfiguration.hpp"
#include "measurements.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3 || std::string(argv[1]) != "-f")
    {
        printUsage(argv[0]);

        return 1;
    }

    std::string file_name = argv[2];
    physicalParameters p_params;

    if (!p_params.loadFromFile(file_name)){
        return 1;
    }

    p_params.printAll();

    const int N{int(p_params.get("N"))};
    const double beta{p_params.get("beta")};
    const double J{p_params.get("J")};
    const int num_sweeps{int(p_params.get("num_sweeps"))};

    double m{0.};
    double acceptance_rate{0};

    std::vector<int> spin_config = coldStart(N);

    hotStart(spin_config);

    std::ofstream file_data("data.dat", std::ios::app);

    if (isFileEmpty)
    {
        file_data << "m" << " " << "acceptance_rate" << "\n";
    }

    for (int i = 0; i < num_sweeps; i++)
    {
        acceptance_rate = MetropolisSweep(spin_config, J, beta, N);
        m = measMagnetization(spin_config);

        file_data << std::fixed << std::setprecision(14) << m << " ";
        file_data << std::fixed << std::setprecision(14) << acceptance_rate << "\n";
    }

    file_data.close();

    return 0;
}
