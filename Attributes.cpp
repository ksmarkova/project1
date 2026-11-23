#include "Attributes.h"

Price::Price(int val) {
    if (val < 0) throw std::invalid_argument("Price can't be negative");
    value = val;
}

int Price::getValue() const { return value; }

void Price::setValue(int newVal) {
    if (newVal < 0) throw std::invalid_argument("Price can't be negative");
    value = newVal;
}

Quantity::Quantity(int val) {
    if (val < 0) throw std::invalid_argument("Quantity can't be negative");
    value = val;
}

int Quantity::getValue() const { return value; }

void Quantity::setValue(int newVal) {
    if (newVal < 0) throw std::invalid_argument("Quantity can't be negative");
    value = newVal;
}

void Quantity::change(int delta) {
    int newVal = value + delta;
    if (newVal < 0) throw std::invalid_argument("Quantity can't be negative");
    value = newVal;
}

Weight::Weight(double val) {
    if (val < 0) throw std::invalid_argument("Weight can't be negative");
    value = val;
}

double Weight::getValue() const { return value; }

void Weight::setValue(double newVal) {
    if (newVal < 0) throw std::invalid_argument("Weight can't be negative");
    value = newVal;
}