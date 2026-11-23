#pragma once
#include "Product.h"
#include <vector>
#include <memory>
#include <stdexcept>

class Warehouse {
    std::vector<std::unique_ptr<Product>> products_;
    size_t maxSize_;
    size_t currentSize_;

public:
    // Итератор
    class WarehouseIterator {
        using Iter = std::vector<std::unique_ptr<Product>>::iterator;
        Iter current_;
        Iter end_;
    public:
        WarehouseIterator(Iter cur, Iter end) : current_(cur), end_(end) {}
        
        bool operator!=(const WarehouseIterator& other) const { return current_ != other.current_; }
        bool operator==(const WarehouseIterator& other) const { return current_ == other.current_; }
        Product& operator*() const { return **current_; }
        WarehouseIterator& operator++() { ++current_; return *this; }
    };

    // Константный итератор
    class ConstWarehouseIterator {
        using Iter = std::vector<std::unique_ptr<Product>>::const_iterator;
        Iter current_;
        Iter end_;
    public:
        ConstWarehouseIterator(Iter cur, Iter end) : current_(cur), end_(end) {}
        
        bool operator!=(const ConstWarehouseIterator& other) const { return current_ != other.current_; }
        bool operator==(const ConstWarehouseIterator& other) const { return current_ == other.current_; }
        const Product& operator*() const { return **current_; }
        ConstWarehouseIterator& operator++() { ++current_; return *this; }
    };

    explicit Warehouse(size_t maxSize);
    
    // Правило пяти
    Warehouse(const Warehouse& other);
    Warehouse& operator=(const Warehouse& other);
    Warehouse(Warehouse&& other) noexcept;
    Warehouse& operator=(Warehouse&& other) noexcept;
    ~Warehouse() = default;

    void addProduct(std::unique_ptr<Product> product);
    void removeById(int id);
    void removeByIndex(size_t index);

    Product* findById(int id);
    std::vector<Product*> findByCategory(const std::string& category) const;
    std::vector<Product*> findByPrice(const Price& price) const;

    size_t size() const { return currentSize_; }
    size_t maxSize() const { return maxSize_; }

    WarehouseIterator begin() { return WarehouseIterator(products_.begin(), products_.end()); }
    WarehouseIterator end() { return WarehouseIterator(products_.end(), products_.end()); }

    ConstWarehouseIterator begin() const { return ConstWarehouseIterator(products_.begin(), products_.end()); }
    ConstWarehouseIterator end() const { return ConstWarehouseIterator(products_.end(), products_.end()); }
};