#include "Product.h"
#include "Warehouse.h"

int Product::nextId_ = 1;

void Product::transferTo(Warehouse& other) {
    other.addProduct(this->clone());
}