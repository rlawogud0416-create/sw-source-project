# 📋 Implementation 과제 제출 가이드

본인이 LMS에 제출할 때 참고할 가이드입니다.

---

## 1. 본문에 작성할 내용

LMS 과제 제출창의 본문(텍스트) 입력란에 아래 내용을 그대로 복사해서 붙여넣고, 빈 부분을 채워넣으세요.

```
[ 학번 ] 22213505
[ 이름 ] 김재형
[ GitHub 저장소 ] https://github.com/본인아이디/저장소명

[ 프로젝트 정보 ]
- 프로젝트명: WC (Weather Coordinator) - 날씨 맞춤형 외출복 코디 추천 프로그램
- 구현 언어: C++17
- 실행 방식: CLI (Command Line Interface)

[ 첨부 파일 ]
1. WC_Source.zip - 전체 소스 코드 및 문서
2. WC.exe - 빌드된 실행 파일 (정적 링크, Windows 환경 독립적)
```

> ⚠️ **`본인아이디/저장소명`** 부분을 본인 GitHub 저장소 주소로 바꿔주세요!

---

## 2. 첨부 파일 준비

### (1) 소스 코드 zip 파일

본 폴더(`WC-Project`) 전체를 zip으로 압축합니다. 다음 파일들이 포함되어야 합니다:

```
WC-Project/
├── src/                     ← C++ 소스 코드 (10개 .h + 10개 .cpp)
├── data/wardrobe.txt        ← 샘플 데이터
├── docs/                    ← 1~3단계 문서들 (Markdown)
├── Makefile                 ← Linux/Mac 빌드용
├── BUILD.md                 ← 빌드 가이드
├── README.md                ← 프로젝트 설명
└── .gitignore
```

**압축 방법 (Windows)**:
1. `WC-Project` 폴더 우클릭
2. `보내기 → 압축(ZIP) 폴더`
3. `WC-Project.zip` 또는 `WC_Source.zip`으로 이름 변경

**압축 방법 (macOS)**:
1. `WC-Project` 폴더 우클릭 → `WC-Project 압축`

**압축 방법 (Linux/터미널)**:
```bash
zip -r WC_Source.zip WC-Project/
```

### (2) 실행 파일 (.exe)

본인 PC에서 빌드한 `WC.exe` 파일을 별도로 첨부합니다.

> ⚠️ **반드시 `/MT` 옵션 (정적 링크)으로 빌드**해야 다른 PC에서도 실행됩니다.  
> 자세한 방법은 `BUILD.md` 참고.

빌드한 `WC.exe`가 정말 환경 독립적인지 확인하려면:
- 다른 친구 PC에서 실행해보기
- 또는 본인 PC에서 Visual Studio가 설치되지 않은 폴더로 옮겨서 실행

---

## 3. 제출 절차

### 단계 1: GitHub에 최종 push

```bash
cd WC-Project
git add .
git commit -m "feat: Implementation phase complete"
git push origin main
```

### 단계 2: GitHub에서 소스 코드 zip 다운로드 (또는 본인이 직접 압축)

방법 A - GitHub에서 다운로드:
1. 본인 저장소 페이지 접속
2. 우측 상단 녹색 `Code` 버튼 클릭
3. `Download ZIP` 클릭
4. `WC-Project-main.zip` 파일 다운로드

방법 B - 본인 PC에서 직접 압축:
- 위의 "압축 방법" 참고

### 단계 3: Windows에서 실행 파일 빌드

`BUILD.md`의 1단계(Visual Studio 사용) 참고:
1. Visual Studio에서 빈 프로젝트 생성
2. `src/` 폴더의 모든 파일 추가
3. **`Release | x64`** 설정
4. **런타임 라이브러리: `/MT (다중 스레드)`** 로 설정 ⭐
5. **C++ 언어 표준: `/std:c++17`**
6. `Ctrl + Shift + B`로 빌드
7. `프로젝트폴더/x64/Release/WC.exe` 확보

### 단계 4: 실행 파일 동작 확인

- `WC.exe`를 다른 폴더로 복사
- 더블 클릭해서 정상 실행되는지 확인
- 가능하면 **다른 PC**에서도 실행해보기

### 단계 5: LMS에 제출

1. LMS의 Implementation 과제 페이지 접속
2. **본문**: 위 1번 항목의 내용 복사 후 학번/이름/GitHub 주소 채우기
3. **첨부 파일**:
   - `WC_Source.zip` (소스 코드)
   - `WC.exe` (실행 파일)
4. 제출 클릭

---

## 4. 제출 전 최종 체크리스트

### 코드 측면
- [ ] 모든 소스 파일이 컴파일 오류 없이 빌드됨
- [ ] 옷 추가 / 조회 / 수정 / 삭제 / 추천 / 종료 모두 동작
- [ ] 종료 후 재실행 시 데이터 유지됨 (`wardrobe.txt` 저장/로드)
- [ ] 한글이 깨지지 않고 표시됨

### 실행 파일 측면
- [ ] **`/MT` 옵션으로 정적 링크 빌드 완료** (가장 중요!)
- [ ] `WC.exe`를 다른 폴더에서 실행해도 정상 동작
- [ ] (가능하면) 다른 PC에서 테스트 완료

### 문서 측면
- [ ] `docs/` 폴더에 1~3단계 문서 모두 포함
- [ ] `README.md`, `BUILD.md` 작성됨
- [ ] GitHub에 최종 push 완료

### 제출물 측면
- [ ] 본문에 학번, 이름, GitHub URL 작성
- [ ] 첨부 파일에 zip과 exe 모두 포함

---

## 5. 마감일 주의

- **서버 사용자**: 6월 25일까지 서버 유지
- **일반 사용자**: LMS의 마감일 확인 후 그 전에 제출

본인은 단독 CLI 프로그램이므로 서버는 해당 없음. LMS 마감일만 지키면 됨.

---

## 6. 도움말

### 빌드가 안 될 때
→ `BUILD.md`의 "자주 발생하는 문제" 섹션 참고

### GitHub 사용법
- 저장소 만들기: github.com에서 `New repository`
- 최초 푸시:
  ```bash
  git init
  git add .
  git commit -m "Initial commit"
  git branch -M main
  git remote add origin https://github.com/본인아이디/저장소명.git
  git push -u origin main
  ```

### 추가 질문
프로젝트 진행 중 막히는 부분이 있으면 언제든 문의하세요.

---

## 행운을 빕니다! 🎉

지금까지 만든 모든 산출물:
- ✅ Conceptualization 문서
- ✅ Analysis 문서  
- ✅ Design 문서 (Mermaid 다이어그램 10장 포함)
- ✅ Implementation: 완전한 C++17 소스 코드 (총 19개 파일)
- ✅ 샘플 데이터 (`wardrobe.txt`)
- ✅ 빌드 시스템 (Makefile)
- ✅ 빌드 가이드 (BUILD.md)
- ✅ 프로젝트 README

본인이 한 학기 동안 만든 결과물이 잘 정리되어 있으니, 자신감 갖고 제출하세요!
