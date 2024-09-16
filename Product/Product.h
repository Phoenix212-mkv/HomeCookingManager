#include <string>
#include<iostream>

class Product {
private:
    std::string name;   // �������� ��������
    int quantity;       // ���������� �������� � ���������
    std::string unit;   // ������� ��������� (��������, "��", "�", "��")

public:
    Product(const std::string& name, int quantity, const std::string& unit)
        : name(name), quantity(quantity), unit(unit) {}

    // �������
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    std::string getUnit() const { return unit; }

    // �������
    void setQuantity(int newQuantity) { quantity = newQuantity; }
};