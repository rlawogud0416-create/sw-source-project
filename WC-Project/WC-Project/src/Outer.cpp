#include "Outer.h"

Outer::Outer(int id, const std::string& name, int thicknessLevel)
    : Clothing(id, name, thicknessLevel) {
}

std::string Outer::getCategory() const {
    return "Outer";
}
