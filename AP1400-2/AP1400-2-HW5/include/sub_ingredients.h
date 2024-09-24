#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#include "ingredient.h"
#define DEFCLASS(NAME, VALUE)\
class NAME : public Ingredient { \
public: \
    NAME(size_t units) : Ingredient{VALUE, units} \
    { \
        this->name = #NAME; \
    } \
    virtual std::string get_name() { return #NAME; }; \
};

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);
#endif // SUB_INGREDIENTS_H
