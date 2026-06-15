#ifndef CLOTHING_H
#define CLOTHING_H

#include <string>

// 모든 옷의 공통 속성과 동작을 정의하는 추상 클래스
class Clothing {
protected:
    int id;
    std::string name;
    int thicknessLevel;  // 1(여름) ~ 5(한겨울)

public:
    Clothing(int id, const std::string& name, int thicknessLevel);
    virtual ~Clothing();

    // Getters
    int getId() const;
    std::string getName() const;
    int getThicknessLevel() const;

    // Setters
    void setName(const std::string& name);
    void setThicknessLevel(int level);

    // 순수 가상 함수 - 자식 클래스에서 반드시 구현
    virtual std::string getCategory() const = 0;

    // 가상 함수 - 자식 클래스에서 오버라이드 가능
    virtual void display() const;
    virtual std::string toFileString() const;
};

#endif
