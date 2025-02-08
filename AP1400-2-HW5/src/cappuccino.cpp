#include "cappuccino.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino(){
    Espresso* ptr = new Espresso{2};
    Milk* ptr2 = new Milk{2};
    MilkFoam* ptr3 = new MilkFoam{1};

    name = std::string("Cappuccino");
    ingredients.push_back(ptr);
    ingredients.push_back(ptr2);
    ingredients.push_back(ptr3);
}

Cappuccino::Cappuccino(const Cappuccino& cap)
{
    name = std::string("Cappuccino");
    for (const auto i : cap.ingredients)
    {
        ingredients.push_back(i->copy());
    }
    for (const auto i : cap.side_items)
    {
        side_items.push_back(i->copy());
    }
}

Cappuccino::~Cappuccino()
{
    for (const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Cappuccino::operator=(const Cappuccino& cap)
{
    if (this == &cap) return;
    name = std::string("Cappuccino");
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

std::string Cappuccino::get_name()
{
    return name;
}

double Cappuccino::price()
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

void Cappuccino::add_side_item(Ingredient* side)
{
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items()
{
    return side_items;
}
