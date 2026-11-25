#pragma once
#include <stdexcept>

class Price {
    int value_;
public:
    explicit Price(int val);
    int getValue() const;
    void setValue(int newVal);
};

class Quantity {
    int value_;
public:
    explicit Quantity(int val);
    int getValue() const;
    void setValue(int newVal);
    void change(int delta);
};

class Weight {
    double value_;
public:
    explicit Weight(double val);
    double getValue() const;
    void setValue(double newVal);
};
