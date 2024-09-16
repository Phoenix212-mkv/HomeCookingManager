#ifndef PRODUCT_H
#define PRODUCT_H


#include <string>
#include<iostream>

class Product {
private:
    std::string name_;   // �������� ��������
    std::string unit_;   // ������� ��������� (��������, "��", "�", "��")

public:
    Product(const std::string& name, int quantity, const std::string& unit)
        : name_(name), unit_(unit) {}

    // �������
    std::string getName() const { return name_; }
    std::string getUnit() const { return unit_; }

    // �������
    void setName(std::string name) { name_ = name; }
    void setUnit(std::string unit) { unit_ = unit; }

};

#endif // !PRODUCT_H