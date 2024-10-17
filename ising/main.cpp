#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <cstring>

const int STDIM {2};
const int L {8};
const char* START {"HOT"};

long cartToLex (std::vector<int>& cartesianCoordinates);

void initializeLattice(std::vector<int>& latticeConfiguration);

void printConfiguration(std::vector<int> latticeConfiguration);

/*--------------------------------------------------------*/

auto main() -> int
{
  std::vector<int> latticeConfiguration (static_cast<int>(pow(L, STDIM)) , 1);

  initializeLattice(latticeConfiguration);

  printConfiguration(latticeConfiguration);
  
  return 0;
}

/*--------------------------------------------------------*/

void printConfiguration(std::vector<int> latticeConfiguration){
  for(auto it = latticeConfiguration.begin(); it != latticeConfiguration.end(); ++it){
    std::cout << *it << " ";
  }
  std::cout << '\n';
}

void initializeLattice(std::vector<int>& latticeConfiguration){

  if (strcmp(START, "COLD") == 0){
    std::cout << "COLD START" << std::endl;
  }

  else if (strcmp(START, "HOT") == 0){
    std::cout << "HOT START" << std::endl;
  
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distribution(0,1);
  
    for(auto it = latticeConfiguration.begin(); it != latticeConfiguration.end(); ++it){
      *it = distribution(gen);
    }
  }
  else{
    std::cerr << "UNDEFINED START CONDITION!" << std::endl;
  }
}

long cartToLex (std::vector<int>& cartesianCoordinates){
  int i;
  long res, aux;

  res = 0;
  aux = 1;

  for(i=0; i<STDIM; ++i){
    res += cartesianCoordinates[i]*aux;
    aux *= L;
  }

  return res;
}
