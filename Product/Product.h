#include <string>
using std::string;
class Product
{
private:
	string name_;		//наименование
	string unit_;		//единицы измерения
	double amount_;		//количество
public:
	Product() :name_(), unit_(), amount_(0) {};
	Product(string name, string unit, double amount);
	Product(Product& p);

	string getName() const;
	string getUnit() const;
	double getAmount() const;

	void setName(string);
	void setUnit(string);
	void setAmount(double);
};