#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse(size_t maxSize) : maxSize_(maxSize), currentSize_(0) {
    if (maxSize == 0) throw std::invalid_argument("Max size must be positive");
}

// Конструктор копирования (глубокое копирование)
Warehouse::Warehouse(const Warehouse& other) 
    : maxSize_(other.maxSize_), currentSize_(other.currentSize_) {
    products_.reserve(currentSize_);
    for (const auto& prod : other.products_) {
        products_.push_back(prod->clone());
    }
}

// Оператор копирования
Warehouse& Warehouse::operator=(const Warehouse& other) {
    if (this != &other) {
        Warehouse temp(other);
        std::swap(products_, temp.products_);
        std::swap(maxSize_, temp.maxSize_);
        std::swap(currentSize_, temp.currentSize_);
    }
    return *this;
}

// Конструктор перемещения
Warehouse::Warehouse(Warehouse&& other) noexcept 
    : products_(std::move(other.products_)), maxSize_(other.maxSize_), currentSize_(other.currentSize_) {
    other.maxSize_ = 0;
    other.currentSize_ = 0;
}

// Оператор перемещения
Warehouse& Warehouse::operator=(Warehouse&& other) noexcept {
    if (this != &other) {
        products_ = std::move(other.products_);
        maxSize_ = other.maxSize_;
        currentSize_ = other.currentSize_;
        other.maxSize_ = 0;
        other.currentSize_ = 0;
    }
    return *this;
}

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    if (!product) throw std::invalid_argument("Product is null");
    if (currentSize_ >= maxSize_) throw std::runtime_error("Warehouse is full");
    products_.push_back(std::move(product));
    currentSize_++;
}

void Warehouse::removeById(int id) {
    for (auto it = products_.begin(); it != products_.end(); ++it) {
        if ((*it)->getId() == id) {
            products_.erase(it);
            currentSize_--;
            return;
        }
    }
    throw std::runtime_error("Product with this ID not found");
}

void Warehouse::removeByIndex(size_t index) {
    if (index >= currentSize_) throw std::out_of_range("Index out of bounds");
    products_.erase(products_.begin() + index);
    currentSize_--;
}

Product* Warehouse::findById(int id) {
    for (auto& prod : products_) {
        if (prod->getId() == id) return prod.get();
    }
    return nullptr;
}

std::vector<Product*> Warehouse::findByCategory(const std::string& category) const {
    std::vector<Product*> res;
    for (const auto& prod : products_) {
        if (prod->getCategory() == category) res.push_back(prod.get());
    }
    return res;
}

std::vector<Product*> Warehouse::findByPrice(const Price& price) const {
    std::vector<Product*> res;
    for (const auto& prod : products_) {
        if (prod->getPrice().getValue() == price.getValue()) res.push_back(prod.get());
    }
    return res;
}