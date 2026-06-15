#include "OutfitRecommender.h"
#include <vector>
#include <random>
#include <ctime>

int OutfitRecommender::tempToThickness(double temp) {
    // 기온 → 두께 레벨 매핑
    if (temp >= 28.0) return 1;       // 한여름
    else if (temp >= 23.0) return 2;  // 늦여름·초가을
    else if (temp >= 17.0) return 3;  // 환절기
    else if (temp >= 10.0) return 4;  // 늦가을·초겨울
    else return 5;                    // 한겨울
}

std::string OutfitRecommender::getSeasonDescription(int thickness) {
    switch (thickness) {
        case 1: return "한여름";
        case 2: return "늦여름·초가을";
        case 3: return "환절기";
        case 4: return "늦가을·초겨울";
        case 5: return "한겨울";
        default: return "알 수 없음";
    }
}

Outfit OutfitRecommender::recommend(double temp, const Wardrobe& wardrobe) {
    int targetLevel = tempToThickness(temp);

    // 카테고리별로 두께 레벨이 맞는 옷들을 찾기
    // 두께가 정확히 일치하는 옷이 없으면 ±1 범위까지 허용
    std::vector<Clothing*> tops, bottoms, outers;

    for (Clothing* c : wardrobe.getList()) {
        int diff = c->getThicknessLevel() - targetLevel;
        // 두께가 ±1 이내인 것 허용 (유연한 추천을 위해)
        if (diff < -1 || diff > 1) continue;

        if (c->getCategory() == "Top") {
            tops.push_back(c);
        } else if (c->getCategory() == "Bottom") {
            bottoms.push_back(c);
        } else if (c->getCategory() == "Outer") {
            outers.push_back(c);
        }
    }

    // 어느 카테고리라도 비어있으면 추천 불가
    if (tops.empty() || bottoms.empty() || outers.empty()) {
        return Outfit(nullptr, nullptr, nullptr);
    }

    // 무작위로 1개씩 선택
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

    std::uniform_int_distribution<size_t> distTop(0, tops.size() - 1);
    std::uniform_int_distribution<size_t> distBottom(0, bottoms.size() - 1);
    std::uniform_int_distribution<size_t> distOuter(0, outers.size() - 1);

    Top* selectedTop = dynamic_cast<Top*>(tops[distTop(rng)]);
    Bottom* selectedBottom = dynamic_cast<Bottom*>(bottoms[distBottom(rng)]);
    Outer* selectedOuter = dynamic_cast<Outer*>(outers[distOuter(rng)]);

    return Outfit(selectedTop, selectedBottom, selectedOuter);
}
