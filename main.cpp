#include "Manager/Manager.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RU");
	Product p("Milk", 5, "");
	Product p3("Milk", 6, "");
	p3 = p;
	Ingredient i(p, 200);
	std::cout << i.getInfo();
	return 0;
}