
#include "symmetric_matrix.hpp"

#include <iostream>

SymmetricMatrix::SymmetricMatrix(size_t num)
: size_(num)
{
  values_.resize(num*(num-1)/2, -1);
}

size_t SymmetricMatrix::getActualPosition(size_t i, size_t j)
{
    if (i > j) std::swap(i, j);

    size_t pos = i * size_ + j - ((i+1)*(i+1) - ((i+1)*i)/2);
    return pos;
}

void SymmetricMatrix::set(size_t i, size_t j, float value)
{
    if (i == j) return;
    size_t pos = getActualPosition(i, j);
    values_[pos] = value;
}

float SymmetricMatrix::get(size_t i, size_t j)
{
    if (i == j) return 0;
    size_t pos = getActualPosition(i, j);
    return values_[pos];
}

void SymmetricMatrix::reset(float value)
{
    std::fill(values_.begin(), values_.end(), value);
}

void SymmetricMatrix::print(bool asArray)
{
    if(asArray)
        for (auto&& value: values_)
            std::cout<<value<<" ";
    std::cout<<std::endl;
}