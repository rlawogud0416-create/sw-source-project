#ifndef WARDROBE_H
#define WARDROBE_H

#include "Clothing.h"
#include <vector>
#include <string>

// 모든 옷을 담아 관리하는 컨테이너 클래스
class Wardrobe {
private:
    std::vector<Clothing*> clothingList;
    int nextId;

public:
    Wardrobe();
    ~Wardrobe();

    // CRUD 기능
    void add(Clothing* clothing);
    bool remove(int id);
    bool update(int id, const std::string& newName, int newThickness);
    Clothing* findById(int id);

    // 필터링
    std::vector<Clothing*> filterByCategory(const std::string& category) const;
    std::vector<Clothing*> filterByThickness(int level) const;

    // 출력
    void displayAll() const;

    // 유틸리티
    int size() const;
    int getNextId();
    const std::vector<Clothing*>& getList() const;

    // 카테고리별 개수 (메뉴 헤더 표시용)
    int countByCategory(const std::string& category) const;
};

#endif
