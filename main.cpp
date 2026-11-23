#include "Warehouse.h"
#include "Factories.h"
#include <iostream>

int main() {
    try {
        std::cout << "--- Сценарий 1: Создание склада и добавление товаров ---\n";
        Warehouse shop(10);
        SmartphoneFactory sf;
        MilkFactory mf;
        
        shop.addProduct(sf.createProduct(1, "iPhone 15", 100000, 5, 0.2));
        shop.addProduct(sf.createProduct(2, "Samsung S24", 90000, 10, 0.2));
        shop.addProduct(mf.createProduct(3, "Milk 3.2%", 100, 20, 1.0));

        for (auto it = shop.begin(); it != shop.end(); ++it) {
            std::cout << "ID: " << (*it).getId() << ", Name: " << (*it).getName() 
                      << ", Cat: " << (*it).getCategory() << "\n";
        }

        std::cout << "\n--- Сценарий 2: Копирование склада и проверка независимости ---\n";
        Warehouse shopCopy = shop;
        shopCopy.findById(1)->changeQuantity(-2); // Изменяем остаток в копии
        std::cout << "Оригинал iPhone (ID 1) qty: " << shop.findById(1)->getQuantity().getValue() << "\n";
        std::cout << "Копия iPhone (ID 1) qty:    " << shopCopy.findById(1)->getQuantity().getValue() << "\n";

        std::cout << "\n--- Сценарий 3: Перемещение склада ---\n";
        Warehouse movedShop = std::move(shopCopy);
        std::cout << "Размер перемещенного склада: " << movedShop.size() << "\n";
        std::cout << "Размер старого (после move): " << shopCopy.size() << "\n";

        std::cout << "\n--- Сценарий 4: Поиск и удаление ---\n";
        auto electronics = shop.findByCategory("electronics");
        std::cout << "Найдено электроники: " << electronics.size() << "\n";
        
        auto cheapItems = shop.findByPrice(Price(100));
        std::cout << "Найдено товаров по цене 100: " << cheapItems.size() << "\n";

        shop.removeById(2); // Удаляем Samsung
        shop.removeByIndex(0); // Удаляем iPhone (теперь он первый)
        std::cout << "После удалений осталось товаров: " << shop.size() << "\n";

        std::cout << "\n--- Сценарий 5: Перемещение товара между складами ---\n";
        Warehouse shopA(5);
        Warehouse shopB(5);
        
        shopA.addProduct(mf.createProduct(4, "Bread", 50, 30, 0.5));
        std::cout << "До перемещения (ShopA): " << shopA.size() << ", (ShopB): " << shopB.size() << "\n";
        
        Product* bread = shopA.findById(4);
        if (bread) {
            bread->transferTo(shopB);
            shopA.removeById(4); // Внимание: transferTo только клонирует, поэтому нужно удалить из старого
        }
        std::cout << "После перемещения (ShopA): " << shopA.size() << ", (ShopB): " << shopB.size() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}