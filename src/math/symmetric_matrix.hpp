
#ifndef SYMMETRiC_MATRIX_H
#define SYMMETRiC_MATRIX_H

#include <vector>

/*
* Used for storing the force between nodes. 
* Instead of using a complete matrix, this class provides an efficient
* way of storing a symmetric matrix in an array.

This would be a complete matrix:
+---+---+-----------+-----------+-----------+-----------+
|   | A |     B     |     C     |     D     |     E     |
+---+---+-----------+-----------+-----------+-----------+
| A | 0 | value_a_b | value_a_c | value_a_d | value_a_e |
| B | 0 | 0         | value_b_c | value_b_d | value_b_e |
| C | 0 | 0         | 0         | value_c_d | value_c_e |
| D | 0 | 0         | 0         | 0         | value_d_e |
| E | 0 | 0         | 0         | 0         | 0         |
+---+---+-----------+-----------+-----------+-----------+

This is the actual array we are using:
+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
|     0     |     1     |     2     |     3     |     4     |     5     |     6     |     7     |     8     |     9     |
+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
| value_a_b | value_a_c | value_a_d | value_a_e | value_b_c | value_b_d | value_b_e | value_c_d | value_c_e | value_d_e |
+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+

We store n*(n-1)/2 values instead of n*n.
*/
class SymmetricMatrix
{
public:
    SymmetricMatrix() = default;
    SymmetricMatrix(size_t num_nodes);

    void set(size_t i, size_t j, float value);

    float get(size_t i, size_t j);

    void reset(float value);

    void print(bool asArray = true);

private:
    size_t getActualPosition(size_t i, size_t j);

    size_t size_;
    std::vector<float> values_;
};

#endif