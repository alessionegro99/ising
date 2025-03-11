#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <cmath>

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

    if (!p_params.loadFromFile(file_name))
    {
        return 1;
    }

    p_params.printAll();

    const size_t S_DIM{size_t(p_params.get("S_DIM"))};

    const size_t N{size_t(p_params.get("N"))};
    const size_t num_sweeps{size_t(p_params.get("num_sweeps"))};

    const double beta{p_params.get("beta")};
    const double J{p_params.get("J")};

    const bool start{bool(p_params.get("start"))};
    double tot_magnetization{0.};
    double tot_energy{0.};
    double acceptance_rate{0};

    std::vector<int> spin_config = coldStart(N);

    if (start)
        hotStart(spin_config);

    // printVec(spin_config);

    computeBoltzmannWeights(S_DIM, J, beta);

    std::ofstream file_data("data.dat", std::ios::app);

    if (isFileEmpty(file_name))
    {
        file_data << "magnetization";
        file_data << " ";
        file_data << "energy";
        file_data << " ";
        file_data << "acceptance_rate";

        file_data << "\n";
    }

    

    /*for (int i = 0; i < num_sweeps; i++)
    {
        tot_magnetization = measMagnetization(spin_config);
        file_data << std::fixed << std::setprecision(14) << tot_magnetization / (double)(spin_config.size());
        file_data << " ";

        tot_energy = measEnergy(spin_config, J, N);
        file_data << std::fixed << std::setprecision(14) << tot_energy / (double)(spin_config.size());
        file_data << " ";

        // 0 for Metropolis 1 for heatbath (+ overrelaxation to be added)
        if (int(p_params.get("updating_procedure")) == 0)
        {
            acceptance_rate = updateMetropolis(spin_config, weights_Boltzmann, N, S_DIM);
            file_data << std::fixed << std::setprecision(14) << acceptance_rate;
            file_data << "\n";
        }

        else if (int(p_params.get("updating_procedure")) == 1)
        {
            updateHeatbath(spin_config, J, beta, N);
            acceptance_rate = 1.;
            file_data << std::fixed << std::setprecision(14) << acceptance_rate;
            file_data << "\n";
        }

        else
            fatalError("Unknown updating procedure.", __func__);
    }
*/
    file_data.close();

    return 0;
}
