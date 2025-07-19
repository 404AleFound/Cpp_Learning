// usett0.cpp -- using a base class
#include<iostream>
#include"code-list-13-01-tabtenn0.h"

int main()
{
	using std::cout;
	TableTennisPlayer player1{ "Chuck", "Blizzard", true };
	TableTennisPlayer player2{ "Tara", "Boomdea", false };

	player1.Name();
	if (player1.HasTable())
		cout << ": has a table.\n";
	else
		cout << ": hasn't no table.\n";

	player2.Name();
	if (player2.HasTable())
		cout << ": has a table.\n";
	else
		cout << ": hasn't no table.\n";
	return 0;
}