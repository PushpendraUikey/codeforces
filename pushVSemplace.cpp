#include <iostream>
#include <vector>
#include <string>

struct Item {
    std::string name;
    int id;

    // Regular Constructor
    Item(std::string n, int i) : name(n), id(i) {
        std::cout << "Constructed\n";
    }

    // Copy Constructor
    Item(const Item& other) : name(other.name), id(other.id) {
        std::cout << "Copied\n";
    }

    // Move Constructor
    Item(Item&& other) noexcept : name(std::move(other.name)), id(other.id) {
        std::cout << "Moved\n";
    }
};

int main() {
    std::vector<Item> items;
    items.reserve(10); // Reserve memory to prevent reallocation noise

    std::cout << "--- Using push_back ---\n";
    items.push_back(Item("Widget", 1)); 

    std::cout << "\n--- Using emplace_back ---\n";
    items.emplace_back("Gadget", 2);

    return 0;
}