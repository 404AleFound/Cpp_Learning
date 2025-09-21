// usedma.cpp -- test class baseDMA, lackDMA and hasDMA
#include<iostream>
#include"code-list-13-14-dma.h"

int main()
{
	using std::cout;
	using std::endl;

	baseDMA shirt("Portabelly", 8);
	lackDMA balloon("Blimpo", 4, "red");
	hasDMA map("Buffalo keys", 5, "Mercator");

	cout << "Displaying baseDMA object:\n";
	cout << shirt << endl;
	cout << "Displaying lacksDMA object:\n";
	cout << balloon << endl;
	cout << "Displaying hasDMA object:\n";
	cout << map << endl;

	lackDMA balloon2(balloon);
	cout << "Result of lacksDMA copy:\n";
	cout << balloon2 << endl;

	hasDMA map2;
	map2 = map;
	cout << "Result of hasDMA assignment:\n";
	cout << map2 << endl;

	return 0;
}