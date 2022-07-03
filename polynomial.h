#ifndef LAB1_POLYNOMIAL_H
#define LAB1_POLYNOMIAL_H

#include <iostream>
#include "doubly-linked-list.h"

class Polynomial {
public:
    // Can be seen outside as DoublyLinkedList::DataType

    DoublyLinkedList dll;

private:
    // Befriend so tests have access to variables.
    friend class PolynomialTest;

public:
    Polynomial(int A[], int size);

    Polynomial *add(Polynomial *rhs);

    Polynomial *sub(Polynomial *rhs);

    Polynomial *mul(Polynomial *rhs);

    void print();

};

#endif
