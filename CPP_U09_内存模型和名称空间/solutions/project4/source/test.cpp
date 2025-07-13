// test.cpp -- test the function
# include <iostream>
# include "Sales.h"

int main() {
	using namespace SALES;
	using namespace std;
	
	Sales s1;
	Sales s2;
	
	double ss[QUARTERS] = {122.0, 342.3, 343.5, 452.4};
	setSales(s1, ss, QUARTERS);
	setSales(s2);
	
	showSales(s1);
	showSales(s2);
	
	return 0; 
}
