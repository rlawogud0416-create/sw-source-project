#include "Top.h"

Top::Top(int id, const std::string& name, int thicknessLevel)
    : Clothing(id, name, thicknessLevel) {
}

std::string Top::getCategory() const {
    return "Top";
}
