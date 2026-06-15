#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include "Wardrobe.h"
#include "Outfit.h"
#include <string>

// 콘솔 입출력을 담당하는 View 클래스
class CLIView {
public:
    // 메인 메뉴 출력 후 사용자 선택 반환 (0~5)
    static int showMainMenu(const Wardrobe& wardrobe);

    // 옷 추가 폼 → 새로 생성된 Clothing 객체 반환 (실패 시 nullptr)
    static Clothing* showAddForm(Wardrobe& wardrobe);

    // 옷장 조회 / 필터링
    static void showWardrobeMenu(const Wardrobe& wardrobe);

    // 옷 수정
    static void showUpdateMenu(Wardrobe& wardrobe);

    // 옷 삭제 (Y/N 확인 포함)
    static void showDeleteMenu(Wardrobe& wardrobe);

    // 기온 입력 → 코디 추천 → 재추천 루프
    static void showRecommendMenu(const Wardrobe& wardrobe);

    // 메시지 출력 유틸
    static void showError(const std::string& message);
    static void showSuccess(const std::string& message);
    static void showInfo(const std::string& message);

    // 사용자 입력 받기 유틸
    static std::string getStringInput(const std::string& prompt);
    static int getIntInput(const std::string& prompt);
    static double getDoubleInput(const std::string& prompt);
    static bool askYesNo(const std::string& prompt);

    // Enter 키 대기
    static void waitEnter();

    // 화면 클리어 (간단한 줄바꿈)
    static void clearScreen();
};

#endif
