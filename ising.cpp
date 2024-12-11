#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

double randUnif(double a, double b);

void IsingInit(std::vector<int> &spin_config);

void printVec(std::vector<int> vec);

double deltaH(std::vector<int> spin_config, double J, int x, int N);

int main(){
    int N {3};
    double beta {0.1};
    std::vector<int> spin_config(N*N,0);

    IsingInit(spin_config);

    //printVec(spin_config);

    //std::cout << deltaH(spin_config, 1, 4, N) << std::endl;
    
    return 0;
}

double randUnif(double a, double b){
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(a, b);

    return dis(gen);
}

void IsingInit(std::vector<int> &spin_config){
    for (int i = 0; i < spin_config.size(); i++){
        if (randUnif(0.,1.) < 0.5)
            spin_config[i] = -1;
        else 
            spin_config[i] = 1;
    }
}

void printVec(std::vector<int> vec){
    for (auto i : vec){
        std::cout << i << " ";
    }
}

double deltaH(std::vector<int> spin_config, double J, int x, int N){
    int dH {0};

    for(int i = 0; i < 2; i++){
        dH += spin_config[(x + i * (N-1) + 1)%(N*N)] + spin_config[(x - i * (N-1) - 1)%(N*N)];
    }

    dH = 2 * J * spin_config[x] * dH;

    return dH;
}

double MetropolisSweep(std::vector<int> &spin_config, double J, double beta, int N){
    int dH {0};
    int accepted_per_sweep {0};

    for(int x = 0; x < N*N; x++){
        dH = deltaH(spin_config, J, x, N);
        if(randUnif(0.,1.) < exp(-beta*dH)){
            spin_config[x] = -spin_config[x];
            accepted_per_sweep += 1;
        }

    }
}