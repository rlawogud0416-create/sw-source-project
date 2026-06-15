#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include "Wardrobe.h"
#include <string>

// 옷장 데이터를 파일에 저장하고 불러오는 영속성 담당 클래스
class DataStorage {
public:
    // 옷장 데이터를 텍스트 파일에 저장
    static bool save(const Wardrobe& wardrobe, const std::string& path);

    // 텍스트 파일에서 옷장 데이터 복원
    static bool load(Wardrobe& wardrobe, const std::string& path);

private:
    // 카테고리 문자열을 보고 알맞은 자식 객체 생성 (팩토리 역할)
    static Clothing* createClothing(const std::string& category, int id,
                                     const std::string& name, int thickness);
};

#endif
