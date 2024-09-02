#include "Product/Product.h"

int main(int argc, char** argv)
{
	Product p("Milk", "l", 200);
	Product p3("Milk", "l", 200);
	p3 = p;
	return 0;
}