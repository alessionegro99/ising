#include <iostream>

#include "../include/parameters.hpp"

void geometry::lexToCart(long cart_coord[], long lex)
{
    long aux[DIM];

    aux[0] = 1;
    for (int i = 1; i < DIM; i++)
    {
        aux[i] = aux[i - 1] * d_size[i - 1];
    }
    // aux[0]=1
    // aux[1]=size[0]
    // aux[2]=size[0]*size[1]
    // ...
    // aux[STDIM-1]=size[0]*size[1]*...*size[STDIM-2]
    for (int i = (DIM - 1); i >= 0; i--) // CAREFUL: DO NOT use size_t i
    {
        cart_coord[i] = (int)(lex / aux[i]);
        lex -= aux[i] * cart_coord[i];
    }
}

int geometry::cartToLex(long cart_coord[])
{
    long res, aux;

    res = 0;
    aux = 1;

    for (int i = 0; i < DIM; i++)
    {
        res += cart_coord[i] * aux;
        aux *= d_size[i];
    }

    // res = cart_coord[0]
    //      +cart_coord[1]*size[0]
    //      +cart_coord[2]*size[0]*size[1]
    //      +...
    //      +cart_coord[STDIM-1]*size[0]*size[1]*...*size[STDIM-2]

    return res;
}

void geometry::printAll()
{
    std::cout << "Geometry related parameters: " << "\n";
    std::cout << "dimension = " << DIM << "\n";
    std::cout << "extent = " << L << "\n";
    std::cout << "volume = " << d_vol << "\n";
    std::cout << "inverse volume = " << d_inv_vol << "\n";
}

void geometry::initGeometry()
{
    int j, value, valuep, valuem;
    long r, rm, rp;
    long cart_coord[DIM];

    // intializing fundamental and derived geometrical quantities
    for (int i = 0; i < DIM; ++i)
    {
        d_size.push_back(L);
    }

    d_vol = 1;
    for (int i = 0; i < DIM; ++i)
    {
        d_vol *= d_size[i];
    }

    d_inv_vol = 1.0 / ((double)d_vol);

    // allocating memory
    d_nnp = new size_t *[d_vol];
    if (!d_nnp)
    {
        std::cerr << "Failed to allocate memory for d_nnp rows.\n";
    }
    for (r = 0; r < d_vol; r++)
    {
        d_nnp[r] = new size_t[DIM];
        if (!d_nnp[r])
        {
            std::cerr << "Failed to allocate memory for d_nnp columns at row " << r << ".\n";

            for (size_t j = 0; j < r; j++)
            {
                delete[] d_nnp[j];
            }
            delete[] d_nnp;
        }
    }

    d_nnm = new size_t *[d_vol];
    if (!d_nnm)
    {
        std::cerr << "Failed to allocate memory for d_nnm rows.\n";
    }
    for (r = 0; r < d_vol; r++)
    {
        d_nnm[r] = new size_t[DIM];
        if (!d_nnm[r])
        {
            std::cerr << "Failed to allocate memory for d_nnm columns at row " << r << ".\n";

            for (size_t j = 0; j < r; j++)
            {
                delete[] d_nnm[j];
            }
            delete[] d_nnm;
        }
    }

    // initializing
    for (r = 0; r < d_vol; r++)
    {
        lexToCart(cart_coord, r);

        for (j = 0; j < DIM; j++)
        {
            value = cart_coord[j];

            valuep = value + 1;
            // implementing PBC in positive direction
            if (valuep >= d_size[j])
            {
                valuep -= d_size[j];
            }
            cart_coord[j] = valuep;
            rp = cartToLex(cart_coord);
            d_nnp[r][j] = rp;

            valuem = value - 1;
            // implementing PBC in negative direction
            if (valuem < 0)
            {
                valuem += d_size[j];
            }
            cart_coord[j] = valuem;
            rm = cartToLex(cart_coord);
            d_nnm[r][j] = rm;

            cart_coord[j] = value;
        }
    }
}

void geometry::freeGeometry()
{
    long r;

    for (r = 0; r < d_vol; ++r)
    {
        delete[] d_nnp[r];
    }
    delete[] d_nnp;

    for (r = 0; r < d_vol; ++r)
    {
        delete[] d_nnm[r];
    }
    delete[] d_nnm;
}