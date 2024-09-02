#include "Product.h"

Product::Product(string name, string unit, double amount)
{
	name_ = name;
	unit_ = unit;
	amount_ = amount;
}
Product::Product(const Product& p)
{
	name_ = p.name_;
	unit_ = p.unit_;
	amount_ = p.amount_;
}

string Product::getName() const
{
	return name_;
}
string Product::getUnit() const
{
	return unit_;
}
double Product::getAmount() const
{
	return amount_;
}

void Product::setName(string name)
{
	name_ = name;
}
void Product::setUnit(string unit)
{
	unit_ = unit;
}
void Product::setAmount(double amount)
{
	amount_ = amount;
}

bool Product::operator ==(const Product& p)
{
	return (name_ == p.name_) && (unit_ == p.unit_);
}