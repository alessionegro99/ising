#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Z2.hpp"
#include "parameters.hpp"

class configuration
{
private:
    const geometry &geo;
    const simulation &sim;

public:
    Z2 *lattice; // [volume] lattice of Z2 spins

    configuration(const geometry &geom, const simulation &simul) : geo(geom),
                                                                   sim(simul)
    {
        initSpinConf();
    }

    // in spin_conf_def.cpp
    void initSpinConf(); // initializes gauge configuration
    void freeSpinConf(); // frees gauge configuration memory

    // in spin_conf_meas.cpp
};
