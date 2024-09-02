#include <string>
#include <vector>
using std::string; using std::vector;
class Product
{
private:
	string name_;		//������������
	string unit_;		//������� ���������
	double amount_;		//����������
public:
	friend class Inventory;
	Product() :name_(), unit_(), amount_(0) {};
	Product(string name, string unit, double amount);
	Product(const Product& p);

	string getName() const;
	string getUnit() const;
	double getAmount() const;

	void setName(string);
	void setUnit(string);
	void setAmount(double);
	bool operator ==(const Product&);
};