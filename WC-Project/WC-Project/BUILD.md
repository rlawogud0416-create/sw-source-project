# 빌드 가이드 (BUILD.md)

이 문서는 WC (Weather Coordinator) 프로젝트를 본인의 PC에서 빌드하여 **실행 환경에 독립적인 실행 파일**을 만드는 방법을 안내한다.

> ⚠️ **중요**: 과제 제출 요구사항이 "실행 환경에 독립적(independent)"이므로, 본 가이드의 **정적 링크 옵션**을 반드시 따라야 한다. 그래야 컴파일러나 런타임이 설치되지 않은 다른 PC에서도 그대로 실행할 수 있다.

---

## 목차

1. [Windows에서 빌드 (Visual Studio 권장)](#1-windows에서-빌드-visual-studio-권장)
2. [Windows에서 빌드 (MinGW-w64 + VS Code)](#2-windows에서-빌드-mingw-w64--vs-code)
3. [macOS에서 빌드](#3-macos에서-빌드)
4. [Linux에서 빌드](#4-linux에서-빌드)
5. [빌드된 실행 파일 배포 및 테스트](#5-빌드된-실행-파일-배포-및-테스트)
6. [자주 발생하는 문제](#6-자주-발생하는-문제)

---

## 1. Windows에서 빌드 (Visual Studio 권장)

본인이 Windows라면 이 방법을 추천한다. 한 번에 독립 실행 가능한 `.exe` 파일이 나온다.

### 1.1 Visual Studio 설치

이미 설치되어 있다면 1.2로.

1. [https://visualstudio.microsoft.com/ko/downloads/](https://visualstudio.microsoft.com/ko/downloads/) 접속
2. **Visual Studio Community 2022** (무료) 다운로드
3. 설치 시 워크로드에서 **"C++를 사용한 데스크톱 개발"** 체크
4. 설치 완료 (약 5~10GB)

### 1.2 새 프로젝트 만들기

1. Visual Studio 실행
2. `새 프로젝트 만들기` 클릭
3. 템플릿에서 **"빈 프로젝트"** (C++, Windows) 선택 → `다음`
4. 프로젝트 이름: `WC`
5. 위치: 원하는 폴더
6. 솔루션 이름도 `WC`로
7. `만들기` 클릭

### 1.3 소스 파일 추가

GitHub에서 다운받은 `src/` 폴더 안의 모든 파일을 추가한다.

1. 솔루션 탐색기에서 프로젝트(`WC`) 우클릭
2. `추가 → 기존 항목`
3. `src/` 폴더에서 다음 파일들을 **모두 선택 (Ctrl + A)** 후 `추가`:
   - `main.cpp`
   - `Clothing.h`, `Clothing.cpp`
   - `Top.h`, `Top.cpp`
   - `Bottom.h`, `Bottom.cpp`
   - `Outer.h`, `Outer.cpp`
   - `Wardrobe.h`, `Wardrobe.cpp`
   - `Outfit.h`, `Outfit.cpp`
   - `OutfitRecommender.h`, `OutfitRecommender.cpp`
   - `DataStorage.h`, `DataStorage.cpp`
   - `CLIView.h`, `CLIView.cpp`

총 19개 파일이 추가되어야 한다.

### 1.4 ⭐ 정적 링크 설정 (가장 중요!)

이 설정을 빠뜨리면 다른 PC에서 실행할 때 "VCRUNTIME140.dll이 없습니다" 같은 오류가 난다.

1. 솔루션 탐색기에서 프로젝트(`WC`) 우클릭 → **`속성`**
2. 좌측 상단에서:
   - **`구성: Release`** 선택
   - **`플랫폼: x64`** 선택
3. 좌측 트리에서 **`구성 속성 → C/C++ → 코드 생성`** 클릭
4. **`런타임 라이브러리`** 항목을 **`다중 스레드(/MT)`** 로 변경
   - 기본값은 `다중 스레드 DLL(/MD)`이지만, 이건 동적 링크라 다른 PC에서 안 됨
5. `적용` → `확인`

### 1.5 C++17 표준 설정

같은 속성 창에서:

1. **`구성 속성 → C/C++ → 언어`**
2. **`C++ 언어 표준`** 항목을 **`ISO C++17 표준 (/std:c++17)`** 으로 변경
3. `적용` → `확인`

### 1.6 빌드

1. 상단 도구 모음에서 **`Release | x64`** 가 선택되어 있는지 확인
2. **`빌드 → 솔루션 빌드`** (단축키 `Ctrl + Shift + B`)
3. 출력 창에 다음과 같은 메시지가 나오면 성공:
   ```
   ========== 빌드: 성공 1개, 실패 0개, 최신 항목 0개, 건너뜀 0개 ==========
   ```

### 1.7 실행 파일 위치

빌드된 `.exe` 파일은 다음 경로에 생성된다:

```
프로젝트폴더/x64/Release/WC.exe
```

이 `WC.exe` 파일이 **제출용 실행 파일**이다.

### 1.8 실행 테스트

빌드된 `.exe`가 정상 동작하는지 확인하자.

1. 탐색기에서 `WC.exe`가 있는 폴더로 이동
2. `data/wardrobe.txt`를 같은 폴더에 복사 (선택사항, 샘플 데이터 사용시)
3. `WC.exe` 더블 클릭 또는 명령 프롬프트에서 실행
4. 한글이 깨지면 명령 프롬프트에서 다음과 같이 실행:
   ```cmd
   chcp 65001
   WC.exe
   ```
   (코드 내부에서 자동으로 UTF-8 설정하지만, 일부 환경에서 필요)

---

## 2. Windows에서 빌드 (MinGW-w64 + VS Code)

Visual Studio가 너무 무거우면 가벼운 MinGW로도 가능하다.

### 2.1 MinGW-w64 설치

1. [https://www.mingw-w64.org/downloads/](https://www.mingw-w64.org/downloads/) 또는 [MSYS2](https://www.msys2.org/) 권장
2. MSYS2 설치 후 터미널에서:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```
3. 환경 변수 PATH에 `C:\msys64\mingw64\bin` 추가

### 2.2 컴파일 (정적 링크)

명령 프롬프트나 PowerShell에서 프로젝트 폴더로 이동 후:

```bash
g++ -std=c++17 -O2 -static -static-libgcc -static-libstdc++ -o WC.exe src/*.cpp
```

`-static` 옵션이 핵심이다. 이렇게 빌드하면 MinGW 런타임 DLL 없이 단독 실행 가능한 `.exe`가 생성된다.

### 2.3 실행

```bash
WC.exe
```

---

## 3. macOS에서 빌드

### 3.1 컴파일러 설치

터미널에서:

```bash
xcode-select --install
```

또는 Homebrew로 GCC 설치:

```bash
brew install gcc
```

### 3.2 빌드

프로젝트 폴더에서:

```bash
make           # 일반 빌드
make static    # 정적 빌드 (배포용, macOS는 완전한 정적 링크가 제한적)
```

또는 수동:

```bash
g++ -std=c++17 -O2 -o build/WC src/*.cpp
```

### 3.3 실행

```bash
./build/WC
```

> 💡 macOS는 시스템 라이브러리 구조상 Windows처럼 완전 정적 링크는 어렵다. 동일 macOS 버전이라면 그대로 실행 가능하다.

---

## 4. Linux에서 빌드

### 4.1 컴파일러 설치 (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential
```

### 4.2 빌드

```bash
make           # 일반 빌드
make static    # 정적 링크 빌드 (배포용)
```

또는 수동:

```bash
g++ -std=c++17 -O2 -static -o build/WC src/*.cpp
```

### 4.3 실행

```bash
./build/WC
```

---

## 5. 빌드된 실행 파일 배포 및 테스트

### 5.1 다른 PC에서 동작 확인하기

빌드된 실행 파일이 진짜로 "환경 독립적"인지 확인하는 것이 중요하다.

**테스트 방법**:

1. 빌드한 `.exe`를 USB나 클라우드(구글 드라이브 등)로 다른 PC에 복사
2. **Visual Studio가 설치되어 있지 않은** PC에서 실행해보기
3. 정상 동작하면 성공
4. "VCRUNTIME140.dll을 찾을 수 없습니다" 등 DLL 오류가 나면 → **/MT 옵션이 빠진 것**. 1.4 단계 다시 확인.

### 5.2 wardrobe.txt 위치

프로그램은 **실행 파일과 같은 폴더**에서 `wardrobe.txt`를 찾고 저장한다.

- 처음 실행 시 `wardrobe.txt`가 없어도 정상 (빈 옷장으로 시작)
- 프로그램 사용 중 자동으로 생성/갱신됨
- 샘플 데이터를 쓰려면 `data/wardrobe.txt`를 실행 파일 옆에 복사

### 5.3 제출용 폴더 구성 (권장)

```
WC_제출/
├── WC.exe              ← 빌드된 실행 파일
├── wardrobe.txt        ← 샘플 데이터 (선택)
└── README.txt          ← 간단한 실행 안내 (선택)
```

이 폴더를 그대로 zip으로 압축해서 제출하면 깔끔하다.

---

## 6. 자주 발생하는 문제

### Q1. 빌드 시 "한글 인코딩" 관련 오류

**증상**: 컴파일 시 한글이 들어간 문자열에서 경고/오류.

**해결**:
- Visual Studio: 모든 `.cpp`, `.h` 파일을 **UTF-8 (BOM 포함)** 으로 저장
- 파일 → 다른 이름으로 저장 → 저장 버튼 옆 화살표 → "인코딩과 함께 저장" → "유니코드 (UTF-8, 서명 있음) - 코드 페이지 65001"

### Q2. 실행 시 한글이 깨져 보임 (`?` 또는 `□`)

**증상**: `WC.exe` 실행하면 메뉴의 한글이 깨짐.

**해결**:
- 코드 안에서 이미 `SetConsoleOutputCP(65001)` 호출하고 있어 자동으로 해결됨
- 그래도 깨진다면 명령 프롬프트에서:
  ```cmd
  chcp 65001
  WC.exe
  ```
- 또는 Windows Terminal 사용

### Q3. "VCRUNTIME140.dll을 찾을 수 없습니다"

**증상**: 다른 PC에서 실행 시 DLL 오류.

**해결**: 1.4 단계의 **`/MT (다중 스레드)`** 옵션 설정. **`/MD`** 가 아님!

### Q4. 빌드는 되는데 실행하면 즉시 종료

**증상**: 더블 클릭하면 검은 창이 잠깐 떴다가 사라짐.

**해결**: 명령 프롬프트를 먼저 열고 거기서 실행해서 오류 메시지 확인:
```cmd
cd "경로\WC.exe가 있는 폴더"
WC.exe
```

### Q5. `wardrobe.txt`가 안 만들어진다

**증상**: 옷을 추가해도 폴더에 `wardrobe.txt`가 없음.

**해결**:
- 프로그램이 현재 작업 디렉토리에 저장하므로 **명령 프롬프트에서 실행**해야 의도한 위치에 생성됨
- 더블 클릭 시에는 `C:\Users\사용자\` 같은 다른 위치에 생성될 수도 있음
- 명령 프롬프트에서 실행 파일이 있는 폴더로 이동한 뒤 실행하는 것을 권장

### Q6. C++17 관련 오류

**증상**: `error: 'std::filesystem' is not a member of 'std'` 같은 컴파일 오류.

**해결**: C++17 표준 설정 확인 (1.5 단계).
- Visual Studio: `/std:c++17` 옵션
- GCC: `-std=c++17` 옵션

### Q7. Makefile 실행 시 `make: command not found`

**해결**:
- Windows: MSYS2 또는 WSL 사용. 또는 `g++` 명령어로 직접 컴파일.
- macOS: `xcode-select --install`로 Command Line Tools 설치
- Linux: `sudo apt install build-essential`

---

## 빠른 빌드 명령어 요약

| 환경 | 빌드 명령어 |
| :--- | :--- |
| Windows (VS) | `Release | x64` + `/MT` + `Ctrl+Shift+B` |
| Windows (MinGW) | `g++ -std=c++17 -O2 -static -static-libgcc -static-libstdc++ -o WC.exe src/*.cpp` |
| macOS | `make` 또는 `g++ -std=c++17 -O2 -o WC src/*.cpp` |
| Linux | `make static` 또는 `g++ -std=c++17 -O2 -static -o WC src/*.cpp` |

---

## 빌드 후 체크리스트

- [ ] 빌드 성공 (오류 0개)
- [ ] 실행 파일이 정상 생성됨
- [ ] 본인 PC에서 실행 → 메뉴 정상 표시
- [ ] 옷 추가 → 옷장 보기 → 코디 추천 동작 확인
- [ ] 종료 후 재실행 → 데이터 유지 확인
- [ ] **다른 PC**에서도 실행 → 정상 동작 확인 (가장 중요!)

이 모든 항목을 통과하면 제출 준비 완료!
