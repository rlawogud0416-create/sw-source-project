#include "Clothing.h"
#include <iostream>
#include <sstream>

Clothing::Clothing(int id, const std::string& name, int thicknessLevel)
    : id(id), name(name), thicknessLevel(thicknessLevel) {
}

Clothing::~Clothing() {
    // 가상 소멸자 (자식 클래스가 안전하게 소멸되도록)
}

int Clothing::getId() const {
    return id;
}

std::string Clothing::getName() const {
    return name;
}

int Clothing::getThicknessLevel() const {
    return thicknessLevel;
}

void Clothing::setName(const std::string& newName) {
    name = newName;
}

void Clothing::setThicknessLevel(int level) {
    if (level >= 1 && level <= 5) {
        thicknessLevel = level;
    }
}

void Clothing::display() const {
    std::cout << "[#" << id << "] "
              << getCategory() << " / "
              << name << " / Lv."
              << thicknessLevel;
}

std::string Clothing::toFileString() const {
    // 파일 저장용 직렬화: id,category,name,thickness
    std::ostringstream oss;
    oss << id << "," << getCategory() << "," << name << "," << thicknessLevel;
    return oss.str();
}
