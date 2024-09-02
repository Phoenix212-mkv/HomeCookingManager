#include "Inventory.h"

Inventory::Inventory(vector<Product> v)
{
	productList_ = v;
}
Inventory::Inventory(Inventory& i)
{
	productList_ = i.productList_;
};

Product& Inventory::operator[](int i)
{
	return productList_[i];
}
void Inventory::addProduct(Product& p)
{
	for (auto i = productList_.begin(); i < productList_.end(); i++)
	{
		if ((*i) == p)
		{
			(*i).amount_ += p.amount_;
			return;
		}
	}
	productList_.push_back(p);
}
