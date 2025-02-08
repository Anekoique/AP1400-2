#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient
{
public:
    double get_price_unit()
    {
        return price_unit;
    }
    size_t get_units()
    {
        return units;
    }
    virtual std::string get_name()
    {
        return name;
    }
    double price()
    {
        return units * price_unit;
    }
    Ingredient* copy()
    {
        Ingredient* ptr = new Ingredient(price_unit, units);
        ptr->name = name;
        return ptr;
    }
    
protected:
    Ingredient(double price_unit, size_t units) : price_unit(price_unit), units(units) {}

    double price_unit;
    size_t units;
    std::string name;
};

#endif // INGREDIENT_H
