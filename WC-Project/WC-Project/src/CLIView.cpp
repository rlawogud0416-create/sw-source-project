#include "CLIView.h"
#include "Top.h"
#include "Bottom.h"
#include "Outer.h"
#include "OutfitRecommender.h"
#include "DataStorage.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// 화면 클리어 (간단하게 줄바꿈으로)
void CLIView::clearScreen() {
    std::cout << "\n\n";
}

void CLIView::showError(const std::string& message) {
    std::cout << "\n  [오류] " << message << std::endl;
}

void CLIView::showSuccess(const std::string& message) {
    std::cout << "\n  [성공] " << message << std::endl;
}

void CLIView::showInfo(const std::string& message) {
    std::cout << "\n  " << message << std::endl;
}

void CLIView::waitEnter() {
    std::cout << "\n  Enter 키를 눌러 계속...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string CLIView::getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int CLIView::getIntInput(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);

        try {
            return std::stoi(line);
        } catch (...) {
            std::cout << "  [오류] 숫자를 입력하세요.\n";
        }
    }
}

double CLIView::getDoubleInput(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);

        try {
            return std::stod(line);
        } catch (...) {
            std::cout << "  [오류] 숫자를 입력하세요.\n";
        }
    }
}

bool CLIView::askYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);

        if (line == "Y" || line == "y") return true;
        if (line == "N" || line == "n") return false;
        std::cout << "  [오류] Y 또는 N을 입력하세요.\n";
    }
}

// ============================================================
// 메인 메뉴
// ============================================================
int CLIView::showMainMenu(const Wardrobe& wardrobe) {
    int topCount = wardrobe.countByCategory("Top");
    int bottomCount = wardrobe.countByCategory("Bottom");
    int outerCount = wardrobe.countByCategory("Outer");

    std::cout << "\n============================================================\n";
    std::cout << "         WC - Weather Coordinator (v1.0)\n";
    std::cout << "            날씨 맞춤형 외출복 코디 추천\n";
    std::cout << "============================================================\n";
    std::cout << "  현재 등록된 옷: " << wardrobe.size() << "벌";
    std::cout << " (상의 " << topCount << " / 하의 " << bottomCount
              << " / 아우터 " << outerCount << ")\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "  [ 1 ] 옷 추가하기\n";
    std::cout << "  [ 2 ] 옷장 보기\n";
    std::cout << "  [ 3 ] 옷 정보 수정하기\n";
    std::cout << "  [ 4 ] 옷 삭제하기\n";
    std::cout << "  [ 5 ] 코디 추천받기\n";
    std::cout << "  [ 0 ] 프로그램 종료\n";
    std::cout << "============================================================\n";

    while (true) {
        int choice = getIntInput("  메뉴를 선택하세요 >> ");
        if (choice >= 0 && choice <= 5) {
            return choice;
        }
        std::cout << "  [오류] 0~5 사이의 숫자를 입력하세요.\n";
    }
}

// ============================================================
// 옷 추가
// ============================================================
Clothing* CLIView::showAddForm(Wardrobe& wardrobe) {
    clearScreen();
    std::cout << "============================================================\n";
    std::cout << "                     [ 옷 추가 ]\n";
    std::cout << "============================================================\n";

    // 카테고리 입력
    int categoryChoice;
    while (true) {
        std::cout << "  카테고리를 선택하세요:\n";
        std::cout << "    [ 1 ] 상의 (Top)\n";
        std::cout << "    [ 2 ] 하의 (Bottom)\n";
        std::cout << "    [ 3 ] 아우터 (Outer)\n";
        categoryChoice = getIntInput("  선택 >> ");
        if (categoryChoice >= 1 && categoryChoice <= 3) break;
        std::cout << "  [오류] 1~3 사이의 숫자를 입력하세요.\n";
    }

    // 이름 입력
    std::string name;
    while (true) {
        name = getStringInput("\n  옷 이름을 입력하세요:\n  >> ");
        if (!name.empty()) break;
        std::cout << "  [오류] 이름을 입력해야 합니다.\n";
    }

    // 두께 입력
    int thickness;
    while (true) {
        thickness = getIntInput("\n  두께 레벨을 입력하세요 (1: 가장 얇음 ~ 5: 가장 두꺼움):\n  >> ");
        if (thickness >= 1 && thickness <= 5) break;
        std::cout << "  [오류] 1~5 사이의 숫자를 입력하세요.\n";
    }

    // 객체 생성
    int newId = wardrobe.getNextId();
    Clothing* newClothing = nullptr;

    switch (categoryChoice) {
        case 1: newClothing = new Top(newId, name, thickness); break;
        case 2: newClothing = new Bottom(newId, name, thickness); break;
        case 3: newClothing = new Outer(newId, name, thickness); break;
    }

    if (newClothing == nullptr) {
        showError("옷 객체 생성 실패");
        return nullptr;
    }

    wardrobe.add(newClothing);

    std::cout << "\n------------------------------------------------------------\n";
    std::cout << "  [성공] 등록 완료!\n";
    std::cout << "    ";
    newClothing->display();
    std::cout << "\n------------------------------------------------------------\n";
    waitEnter();

    return newClothing;
}

// ============================================================
// 옷장 조회 / 필터링
// ============================================================
void CLIView::showWardrobeMenu(const Wardrobe& wardrobe) {
    clearScreen();
    std::cout << "============================================================\n";
    std::cout << "                    [ 내 옷장 ]\n";
    std::cout << "============================================================\n";

    int filterChoice;
    while (true) {
        std::cout << "  필터를 선택하세요:\n";
        std::cout << "    [ 0 ] 전체 보기  [ 1 ] 상의  [ 2 ] 하의  [ 3 ] 아우터\n";
        filterChoice = getIntInput("  선택 >> ");
        if (filterChoice >= 0 && filterChoice <= 3) break;
        std::cout << "  [오류] 0~3 사이의 숫자를 입력하세요.\n";
    }

    std::cout << "\n";

    if (filterChoice == 0) {
        // 전체 보기
        wardrobe.displayAll();
    } else {
        // 카테고리별 필터링
        std::string category;
        switch (filterChoice) {
            case 1: category = "Top"; break;
            case 2: category = "Bottom"; break;
            case 3: category = "Outer"; break;
        }

        auto filtered = wardrobe.filterByCategory(category);
        if (filtered.empty()) {
            std::cout << "  조회된 옷이 없습니다.\n";
        } else {
            std::cout << "------------------------------------------------------------\n";
            std::cout << "   ID  | 카테고리 | 옷 이름                  | 두께\n";
            std::cout << "------------------------------------------------------------\n";
            for (Clothing* c : filtered) {
                std::cout << "   ";
                if (c->getId() < 10) std::cout << "0";
                std::cout << c->getId() << "  | " << c->getCategory();
                // 패딩
                int pad = 8 - (int)c->getCategory().length();
                for (int i = 0; i < pad; ++i) std::cout << " ";
                std::cout << " | " << c->getName();
                pad = 24 - (int)c->getName().length();
                for (int i = 0; i < pad; ++i) std::cout << " ";
                std::cout << " | Lv." << c->getThicknessLevel() << "\n";
            }
            std::cout << "------------------------------------------------------------\n";
            std::cout << "  총 " << filtered.size() << "벌\n";
        }
    }

    waitEnter();
}

// ============================================================
// 옷 수정
// ============================================================
void CLIView::showUpdateMenu(Wardrobe& wardrobe) {
    clearScreen();
    std::cout << "============================================================\n";
    std::cout << "                     [ 옷 수정 ]\n";
    std::cout << "============================================================\n";

    if (wardrobe.size() == 0) {
        std::cout << "  등록된 옷이 없습니다.\n";
        waitEnter();
        return;
    }

    wardrobe.displayAll();

    int id = getIntInput("\n  수정할 옷의 번호(ID)를 입력하세요:\n  >> ");
    Clothing* target = wardrobe.findById(id);

    if (target == nullptr) {
        showError("해당 ID의 옷이 없습니다.");
        waitEnter();
        return;
    }

    std::cout << "\n  수정 대상: ";
    target->display();
    std::cout << "\n";

    // 새 이름 입력 (Enter만 누르면 기존 값 유지)
    std::string newName = getStringInput("\n  새 이름 (변경하지 않으려면 Enter): ");

    // 새 두께 입력
    std::cout << "  새 두께 레벨 (1~5, 변경하지 않으려면 0): ";
    std::string thicknessStr;
    std::getline(std::cin, thicknessStr);

    int newThickness = -1;
    if (!thicknessStr.empty()) {
        try {
            newThickness = std::stoi(thicknessStr);
            if (newThickness == 0) {
                newThickness = -1;  // 변경 안 함
            } else if (newThickness < 1 || newThickness > 5) {
                showError("두께는 1~5 범위여야 합니다.");
                waitEnter();
                return;
            }
        } catch (...) {
            showError("올바른 숫자를 입력하세요.");
            waitEnter();
            return;
        }
    }

    // 실제 변경할 두께 결정
    int thicknessToUse = (newThickness == -1) ? target->getThicknessLevel() : newThickness;

    if (wardrobe.update(id, newName, thicknessToUse)) {
        std::cout << "\n------------------------------------------------------------\n";
        std::cout << "  [성공] 수정 완료!\n";
        std::cout << "    ";
        target->display();
        std::cout << "\n------------------------------------------------------------\n";
    } else {
        showError("수정 실패");
    }

    waitEnter();
}

// ============================================================
// 옷 삭제
// ============================================================
void CLIView::showDeleteMenu(Wardrobe& wardrobe) {
    clearScreen();
    std::cout << "============================================================\n";
    std::cout << "                     [ 옷 삭제 ]\n";
    std::cout << "============================================================\n";

    if (wardrobe.size() == 0) {
        std::cout << "  등록된 옷이 없습니다.\n";
        waitEnter();
        return;
    }

    wardrobe.displayAll();

    int id = getIntInput("\n  삭제할 옷의 번호(ID)를 입력하세요:\n  >> ");
    Clothing* target = wardrobe.findById(id);

    if (target == nullptr) {
        showError("해당 ID의 옷이 없습니다.");
        waitEnter();
        return;
    }

    std::cout << "\n  삭제 대상: ";
    target->display();
    std::cout << "\n";

    if (askYesNo("\n  정말 삭제하시겠습니까? (Y/N) >> ")) {
        if (wardrobe.remove(id)) {
            std::cout << "\n------------------------------------------------------------\n";
            std::cout << "  [성공] 삭제 완료!\n";
            std::cout << "------------------------------------------------------------\n";
        } else {
            showError("삭제 실패");
        }
    } else {
        showInfo("삭제가 취소되었습니다.");
    }

    waitEnter();
}

// ============================================================
// 코디 추천
// ============================================================
void CLIView::showRecommendMenu(const Wardrobe& wardrobe) {
    clearScreen();
    std::cout << "============================================================\n";
    std::cout << "                  [ 코디 추천받기 ]\n";
    std::cout << "============================================================\n";

    // 옷이 충분히 있는지 사전 확인
    if (wardrobe.countByCategory("Top") == 0 ||
        wardrobe.countByCategory("Bottom") == 0 ||
        wardrobe.countByCategory("Outer") == 0) {
        showError("상의, 하의, 아우터가 각각 1개 이상 등록되어야 합니다.");
        waitEnter();
        return;
    }

    // 기온 입력
    double temp;
    while (true) {
        temp = getDoubleInput("  오늘의 기온(℃)을 입력하세요:\n  >> ");
        if (temp >= -50 && temp <= 60) break;
        std::cout << "  [오류] 현실적인 기온 범위(-50 ~ 60℃)로 입력하세요.\n";
    }

    // 추천 받기 (재추천 루프)
    while (true) {
        int level = OutfitRecommender::tempToThickness(temp);
        std::string season = OutfitRecommender::getSeasonDescription(level);

        std::cout << "\n  ★ 기온 " << temp << "℃ -> 권장 두께 레벨: "
                  << level << " (" << season << ") ★\n";

        Outfit outfit = OutfitRecommender::recommend(temp, wardrobe);

        if (!outfit.isValid()) {
            showError("추천 가능한 코디가 부족합니다. 옷장에 옷을 더 추가해주세요.");
            waitEnter();
            return;
        }

        outfit.display();

        if (!askYesNo("\n  다시 추천받으시겠습니까? (Y/N) >> ")) {
            break;
        }
    }
}
