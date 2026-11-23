#pragma once
#include <stdexcept>

class Price {
    int value_;
public:
    explicit Price(int val) : value_(val) { if (val < 0) throw std::invalid_argument("Price < 0"); }
    int getValue() const { return value_; }
    void setValue(int newVal) { if (newVal < 0) throw std::invalid_argument("Price < 0"); value_ = newVal; }
};

class Quantity {
    int value_;
public:
    explicit Quantity(int val) : value_(val) { if (val < 0) throw std::invalid_argument("Quantity < 0"); }
    int getValue() const { return value_; }
    void setValue(int newVal) { if (newVal < 0) throw std::invalid_argument("Quantity < 0"); value_ = newVal; }
    void change(int delta) { setValue(value_ + delta); }
};

class Weight {
    double value_;
public:
    explicit Weight(double val) : value_(val) { if (val < 0) throw std::invalid_argument("Weight < 0"); }
    double getValue() const { return value_; }
    void setValue(double newVal) { if (newVal < 0) throw std::invalid_argument("Weight < 0"); value_ = newVal; }
};