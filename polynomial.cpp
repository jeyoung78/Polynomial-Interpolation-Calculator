#include "polynomial.h"

Polynomial::Polynomial(int A[], int size) {

    for (int idx = 0; idx < size; ++idx) {
        dll.insert_back(A[idx]);
    }
}

Polynomial* Polynomial::add(Polynomial *rhs) {
    int result_size = 0;

    if (dll.size() >= rhs->dll.size()) { result_size = dll.size(); }
    else { result_size = rhs->dll.size(); }

    int result_array[result_size] = {};

    for (int idx = 0; idx < result_size; idx++) {
        int lhsVal = 0, rhsVal = 0;
        if ( dll.size() > idx) { lhsVal = dll.select(idx); }
        if ( rhs->dll.size() > idx) { rhsVal = rhs->dll.select(idx); }

        result_array[idx] = lhsVal + rhsVal;
        //std::cout << result_array[idx] << std::endl;
    }

    Polynomial* ret = new Polynomial(result_array, result_size);

    return ret;
}

Polynomial* Polynomial::sub(Polynomial *rhs) {
    int result_size = 0;

    if (dll.size() >= rhs->dll.size()) { result_size = dll.size(); }
    else { result_size = rhs->dll.size(); }

    int result_array[result_size] = {};

    for (int idx = 0; idx < result_size; idx++) {
        int lhsVal = 0, rhsVal = 0;
        if ( dll.size() > idx) { lhsVal = dll.select(idx); }
        if ( rhs->dll.size() > idx) { rhsVal = rhs->dll.select(idx); }

        result_array[idx] = lhsVal - rhsVal;
        //std::cout << result_array[idx] << std::endl;
    }

    Polynomial* ret = new Polynomial(result_array, result_size);

    return ret;
}

Polynomial* Polynomial::mul(Polynomial *rhs) {
    int result_size = rhs->dll.size() + dll.size() - 1;
    int result_array[result_size] = {};

    for (int idx1 = 0; idx1 < dll.size(); ++idx1) {
        for (int idx2 = 0; idx2 < rhs->dll.size(); ++idx2) {
            result_array[idx1 + idx2] += dll.select(idx1) * rhs->dll.select(idx2);
        }
    }

    Polynomial* ret = new Polynomial(result_array, result_size);

    return ret;
}

void Polynomial::print() {
    int size = int(dll.size());

    int numNotZero = 0;

    for (int idx = 0; idx < size; idx++) {
        if (dll.select(idx) != 0) numNotZero++;
    }

    for (int idx = size - 1; idx >= 0; idx--) {
        if (dll.select(idx) != 0) {
            if (dll.select(idx) > 0) std::cout << dll.select(idx) << "x^" <<idx;
            else std::cout << "(" << dll.select(idx) << ")x^" << idx;

            if (numNotZero > 1) {
                std::cout << " + ";
                numNotZero--;
            }

        }
    }

    std::cout << std::endl;
}
