#include "Bottom.h"

Bottom::Bottom(int id, const std::string& name, int thicknessLevel)
    : Clothing(id, name, thicknessLevel) {
}

std::string Bottom::getCategory() const {
    return "Bottom";
}
