// WC - Weather Coordinator
// 날씨 맞춤형 외출복 코디 추천 프로그램
// 22213505 김재형

#include "Wardrobe.h"
#include "CLIView.h"
#include "DataStorage.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

const std::string DATA_FILE = "wardrobe.txt";

int main() {
    // Windows 콘솔에서 한글 출력을 위한 코드페이지 설정
    #ifdef _WIN32
    SetConsoleOutputCP(65001);   // UTF-8
    SetConsoleCP(65001);
    #endif

    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "    WC - Weather Coordinator 시작 중...\n";
    std::cout << "============================================================\n";

    // 1. 옷장 객체 생성 및 데이터 로드
    Wardrobe wardrobe;
    bool loaded = DataStorage::load(wardrobe, DATA_FILE);

    if (loaded) {
        std::cout << "  옷장 데이터를 불러왔습니다. (" << wardrobe.size() << "벌)\n";
    } else {
        std::cout << "  새 옷장이 생성되었습니다.\n";
    }

    // 2. 메인 메뉴 루프
    bool running = true;
    while (running) {
        int choice = CLIView::showMainMenu(wardrobe);

        switch (choice) {
            case 1: {
                // 옷 추가
                Clothing* added = CLIView::showAddForm(wardrobe);
                if (added != nullptr) {
                    DataStorage::save(wardrobe, DATA_FILE);
                }
                break;
            }
            case 2:
                // 옷장 보기
                CLIView::showWardrobeMenu(wardrobe);
                break;

            case 3:
                // 옷 수정
                CLIView::showUpdateMenu(wardrobe);
                DataStorage::save(wardrobe, DATA_FILE);
                break;

            case 4:
                // 옷 삭제
                CLIView::showDeleteMenu(wardrobe);
                DataStorage::save(wardrobe, DATA_FILE);
                break;

            case 5:
                // 코디 추천
                CLIView::showRecommendMenu(wardrobe);
                break;

            case 0:
                // 종료
                running = false;
                break;

            default:
                CLIView::showError("알 수 없는 선택입니다.");
                break;
        }
    }

    // 3. 종료 전 최종 저장
    std::cout << "\n  데이터를 저장 중...\n";
    if (DataStorage::save(wardrobe, DATA_FILE)) {
        std::cout << "  저장 완료.\n";
    }

    std::cout << "\n============================================================\n";
    std::cout << "    프로그램을 종료합니다. 좋은 하루 되세요!\n";
    std::cout << "============================================================\n\n";

    // wardrobe 소멸자가 자동으로 모든 동적 할당 옷 객체 해제

    return 0;
}
