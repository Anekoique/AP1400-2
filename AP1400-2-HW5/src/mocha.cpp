#include "mocha.h"
#include "sub_ingredients.h"

Mocha::Mocha(){
    Espresso* ptr = new Espresso{2};
    Milk* ptr2 = new Milk{2};
    MilkFoam* ptr3 = new MilkFoam{1};
    Chocolate* ptr4 = new Chocolate{1};
    name = std::string("Mocha");
    ingredients.push_back(ptr);
    ingredients.push_back(ptr2);
    ingredients.push_back(ptr3);
    ingredients.push_back(ptr4);
}

Mocha::Mocha(const Mocha& cap)
{
    if (this == &cap) return;
    name = std::string("Mocha");
    for (const auto& i : ingredients)
        delete i;
    ingredients.clear();
    for (const auto& i : side_items)
        delete i;
    side_items.clear();
    for (const auto i : cap.ingredients)
    {
        ingredients.push_back(i->copy());
    }
    for (const auto i : cap.side_items)
    {
        side_items.push_back(i->copy());
    }
}

Mocha::~Mocha()
{
    for (const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Mocha::operator=(const Mocha& cap)
{
    side_items = cap.side_items;
}

std::string Mocha::get_name()
{
    return name;
}

double Mocha::price()
{
    double price = 0;
    for (const auto i : ingredients)
    {
        price += i->price();
    }
    for (const auto i : side_items)
    {
        price += i->price();
    }
    return price;
}

void Mocha::add_side_item(Ingredient* side)
{
    side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items()
{
    return side_items;
}
