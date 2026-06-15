# WC - Weather Coordinator Makefile
# Linux / macOS 빌드용

CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
TARGET = WC
SRCDIR = src
BUILDDIR = build
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# 기본 빌드
all: $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(TARGET): $(SOURCES)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)
	@echo "빌드 완료: $(BUILDDIR)/$(TARGET)"

# 정적 링크 빌드 (배포용 - Linux)
static: $(SOURCES)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -static -o $(BUILDDIR)/$(TARGET) $(SOURCES)
	@echo "정적 빌드 완료: $(BUILDDIR)/$(TARGET)"

# 실행
run: all
	cd $(BUILDDIR) && ./$(TARGET)

# 정리
clean:
	rm -rf $(BUILDDIR)
	@echo "빌드 디렉토리 정리 완료"

.PHONY: all static run clean
