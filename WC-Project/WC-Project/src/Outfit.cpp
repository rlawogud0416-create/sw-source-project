#include "Outfit.h"
#include <iostream>
#include <iomanip>

Outfit::Outfit(Top* top, Bottom* bottom, Outer* outer)
    : top(top), bottom(bottom), outer(outer) {
}

void Outfit::display() const {
    if (!isValid()) {
        std::cout << "  추천 가능한 코디가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n============================================================\n";
    std::cout << "                  오늘의 추천 코디\n";
    std::cout << "============================================================\n";
    std::cout << "  [상의]   : " << top->getName()
              << " (Lv." << top->getThicknessLevel() << ")\n";
    std::cout << "  [하의]   : " << bottom->getName()
              << " (Lv." << bottom->getThicknessLevel() << ")\n";
    std::cout << "  [아우터] : " << outer->getName()
              << " (Lv." << outer->getThicknessLevel() << ")\n";
    std::cout << "============================================================\n";
}

bool Outfit::isValid() const {
    return top != nullptr && bottom != nullptr && outer != nullptr;
}
