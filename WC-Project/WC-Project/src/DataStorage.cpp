#include "DataStorage.h"
#include "Top.h"
#include "Bottom.h"
#include "Outer.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool DataStorage::save(const Wardrobe& wardrobe, const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "  [경고] 파일을 저장할 수 없습니다: " << path << std::endl;
        return false;
    }

    for (Clothing* c : wardrobe.getList()) {
        file << c->toFileString() << "\n";
    }

    file.close();
    return true;
}

bool DataStorage::load(Wardrobe& wardrobe, const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        // 파일 없음 → 새 옷장으로 시작 (정상 상황)
        return false;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, category, name, thicknessStr;

        // CSV 파싱: id,category,name,thickness
        if (!std::getline(ss, idStr, ',') ||
            !std::getline(ss, category, ',') ||
            !std::getline(ss, name, ',') ||
            !std::getline(ss, thicknessStr, ',')) {
            std::cerr << "  [경고] " << lineNum << "번째 줄 형식 오류 - 건너뜀\n";
            continue;
        }

        // 숫자 변환
        int id, thickness;
        try {
            id = std::stoi(idStr);
            thickness = std::stoi(thicknessStr);
        } catch (...) {
            std::cerr << "  [경고] " << lineNum << "번째 줄 숫자 오류 - 건너뜀\n";
            continue;
        }

        // 두께 레벨 유효성 검사
        if (thickness < 1 || thickness > 5) {
            std::cerr << "  [경고] " << lineNum << "번째 줄 두께 범위 오류 - 건너뜀\n";
            continue;
        }

        // 카테고리에 맞는 자식 객체 생성 (팩토리)
        Clothing* clothing = createClothing(category, id, name, thickness);
        if (clothing != nullptr) {
            wardrobe.add(clothing);
        } else {
            std::cerr << "  [경고] " << lineNum << "번째 줄 알 수 없는 카테고리: "
                      << category << " - 건너뜀\n";
        }
    }

    file.close();
    return true;
}

Clothing* DataStorage::createClothing(const std::string& category, int id,
                                       const std::string& name, int thickness) {
    if (category == "Top") {
        return new Top(id, name, thickness);
    } else if (category == "Bottom") {
        return new Bottom(id, name, thickness);
    } else if (category == "Outer") {
        return new Outer(id, name, thickness);
    }
    return nullptr;
}
