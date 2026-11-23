#pragma once
#include "Attributes.h"
#include <memory>
#include <string>
#include <iostream>

class Warehouse;

class Product {
protected:
    int id;
    std::string name;
    Price price_;
    Quantity quantity_;
    Weight weight_;
    std::string category;

public:
    static int nextId_;
    
    Product(int id_, std::string name_, Price price, Quantity quantity, Weight weight, std::string cat)
        : id(id_), name(std::move(name_)), price_(price), quantity_(quantity), weight_(weight), category(std::move(cat)) {
        if (id_ >= nextId_) nextId_ = id_ + 1; // Синхронизация счетчика
    }
    
    virtual ~Product() = default;

    int getId() const { return id; }
    const std::string& getName() const { return name; }
    const std::string& getCategory() const { return category; }
    Price getPrice() const { return price_; }
    Quantity getQuantity() const { return quantity_; }
    Weight getWeight() const { return weight_; }

    virtual void changeQuantity(int delta) { quantity_.change(delta); }
    virtual void setPrice(const Price& newPrice) { price_ = newPrice; }
    virtual void transferTo(Warehouse& other); // Реализация в .cpp
    virtual std::unique_ptr<Product> clone() const = 0;
};

// Промежуточные классы
class Electronics : public Product {
public:
    Electronics(int id, std::string name, Price p, Quantity q, Weight w) 
        : Product(id, std::move(name), p, q, w, "electronics") {}
};

class Clothing : public Product {
public:
    Clothing(int id, std::string name, Price p, Quantity q, Weight w) 
        : Product(id, std::move(name), p, q, w, "clothing") {}
};

class Food : public Product {
public:
    Food(int id, std::string name, Price p, Quantity q, Weight w) 
        : Product(id, std::move(name), p, q, w, "food") {}
};

// Конкретные классы
class Smartphone : public Electronics {
public:
    using Electronics::Electronics;
    std::unique_ptr<Product> clone() const override { return std::make_unique<Smartphone>(*this); }
};

class Laptop : public Electronics {
public:
    using Electronics::Electronics;
    std::unique_ptr<Product> clone() const override { return std::make_unique<Laptop>(*this); }
};

class TShirt : public Clothing {
public:
    using Clothing::Clothing;
    std::unique_ptr<Product> clone() const override { return std::make_unique<TShirt>(*this); }
};

class Jacket : public Clothing {
public:
    using Clothing::Clothing;
    std::unique_ptr<Product> clone() const override { return std::make_unique<Jacket>(*this); }
};

class Milk : public Food {
public:
    using Food::Food;
    std::unique_ptr<Product> clone() const override { return std::make_unique<Milk>(*this); }
};

class Bread : public Food {
public:
    using Food::Food;
    std::unique_ptr<Product> clone() const override { return std::make_unique<Bread>(*this); }
};