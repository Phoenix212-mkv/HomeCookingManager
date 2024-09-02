#include "Product.h"

class Inventory
{
private:
	vector<Product> productList_;
public:
	Inventory() :productList_() {};
	Inventory(vector<Product>);
	Inventory(Inventory&);
	void addProduct(Product&);
	void deleteProduct(string);

	Product& operator[](int);
};