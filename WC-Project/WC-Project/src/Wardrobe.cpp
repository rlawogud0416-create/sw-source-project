#include "Wardrobe.h"
#include <iostream>
#include <iomanip>

Wardrobe::Wardrobe() : nextId(1) {
}

Wardrobe::~Wardrobe() {
    // 동적 할당된 모든 옷 객체 해제
    for (Clothing* c : clothingList) {
        delete c;
    }
    clothingList.clear();
}

void Wardrobe::add(Clothing* clothing) {
    if (clothing == nullptr) return;
    clothingList.push_back(clothing);

    // 추가된 옷의 id가 nextId보다 크거나 같으면 nextId 조정
    if (clothing->getId() >= nextId) {
        nextId = clothing->getId() + 1;
    }
}

bool Wardrobe::remove(int id) {
    for (auto it = clothingList.begin(); it != clothingList.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;          // 메모리 해제
            clothingList.erase(it);
            return true;
        }
    }
    return false;
}

bool Wardrobe::update(int id, const std::string& newName, int newThickness) {
    Clothing* c = findById(id);
    if (c == nullptr) return false;

    if (!newName.empty()) {
        c->setName(newName);
    }
    if (newThickness >= 1 && newThickness <= 5) {
        c->setThicknessLevel(newThickness);
    }
    return true;
}

Clothing* Wardrobe::findById(int id) {
    for (Clothing* c : clothingList) {
        if (c->getId() == id) return c;
    }
    return nullptr;
}

std::vector<Clothing*> Wardrobe::filterByCategory(const std::string& category) const {
    std::vector<Clothing*> result;
    for (Clothing* c : clothingList) {
        if (c->getCategory() == category) {
            result.push_back(c);
        }
    }
    return result;
}

std::vector<Clothing*> Wardrobe::filterByThickness(int level) const {
    std::vector<Clothing*> result;
    for (Clothing* c : clothingList) {
        if (c->getThicknessLevel() == level) {
            result.push_back(c);
        }
    }
    return result;
}

void Wardrobe::displayAll() const {
    if (clothingList.empty()) {
        std::cout << "  등록된 옷이 없습니다." << std::endl;
        return;
    }

    std::cout << "------------------------------------------------------------\n";
    std::cout << "   ID  | 카테고리 | 옷 이름                  | 두께\n";
    std::cout << "------------------------------------------------------------\n";
    for (Clothing* c : clothingList) {
        std::cout << "   " << std::setw(2) << std::setfill('0') << c->getId() << std::setfill(' ')
                  << "  | " << std::left << std::setw(8) << c->getCategory()
                  << " | " << std::setw(24) << c->getName()
                  << " | Lv." << c->getThicknessLevel() << std::right << "\n";
    }
    std::cout << "------------------------------------------------------------\n";
    std::cout << "  총 " << clothingList.size() << "벌\n";
}

int Wardrobe::size() const {
    return static_cast<int>(clothingList.size());
}

int Wardrobe::getNextId() {
    return nextId++;
}

const std::vector<Clothing*>& Wardrobe::getList() const {
    return clothingList;
}

int Wardrobe::countByCategory(const std::string& category) const {
    int count = 0;
    for (Clothing* c : clothingList) {
        if (c->getCategory() == category) count++;
    }
    return count;
}
