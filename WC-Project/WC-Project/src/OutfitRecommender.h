#ifndef OUTFIT_RECOMMENDER_H
#define OUTFIT_RECOMMENDER_H

#include "Wardrobe.h"
#include "Outfit.h"

// 기온 기반으로 코디를 추천하는 핵심 로직 클래스
class OutfitRecommender {
public:
    // 기온을 두께 레벨(1~5)로 변환
    static int tempToThickness(double temp);

    // 기온에 맞는 코디 한 세트를 추천
    // 카테고리 중 하나라도 비어있으면 isValid()가 false인 Outfit 반환
    static Outfit recommend(double temp, const Wardrobe& wardrobe);

    // 기온에 대한 설명 (예: "환절기")
    static std::string getSeasonDescription(int thickness);
};

#endif
