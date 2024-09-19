#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product
{
private:
    int id_;            // ID ��������
    std::string name_;   // �������� ��������
    std::string unit_;   // ������� ��������� (��������, "��", "�", "��")

public:
    Product(int id, const std::string& name, const std::string& unit)
        : id_(id), name_(name), unit_(unit) {}
    Product() : id_(0), name_(""), unit_("") {}

    // �������
    std::string getName() const { return name_; }
    std::string getUnit() const { return unit_; }
    int getId() const { return id_; }

    // �������
    void setName(const std::string& name) { name_ = name; }
    void setUnit(const std::string& unit) { unit_ = unit; }
    void setID(int id) { id_ = id; }
};

#endif // PRODUCT_H