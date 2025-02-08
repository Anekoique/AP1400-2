#include "espresso_based.h"
#include <iostream>

EspressoBased::EspressoBased(const EspressoBased& esp)
{
    ingredients = esp.ingredients;
    name = esp.name;
}

void EspressoBased::operator=(const EspressoBased& esp)
{
    ingredients = esp.ingredients;
    name = esp.name;
}

std::vector<Ingredient*>& EspressoBased::get_ingredients()
{
    return ingredients; 
}

EspressoBased::~EspressoBased()
{
    for (const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

