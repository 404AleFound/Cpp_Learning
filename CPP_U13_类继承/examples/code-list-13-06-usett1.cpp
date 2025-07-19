// usett1.cpp -- using base class and derived class
#include<iostream>
#include"code-list-13-04-tabtenn1.h"

int main()
{
	using std::cout;
	using std::cin;
	TableTennisPlayer player1{ "Tara", "Boomdea", false };
	RatedPlayer rplayer1{ 1140, "Mallory", "Duck", true };
	rplayer1.Name();
	if (rplayer1.HasTable())
		cout << ": has a table.\n";
	else
		cout << ": hasn't a table.\n";
	player1.Name();
	if (player1.HasTable())
		cout << ": has a table";
	else
		cout << ": hasn't a table.\n";
	cout << "Name: ";
	rplayer1.Name();
	cout << "; Rating: " << rplayer1.Rating() << std::endl;
	RatedPlayer rplayer2(1212, player1);
	cout << "Name: ";
	rplayer2.Name();
	cout << "; Rating: " << rplayer2.Rating() << std::endl;
	return 0;

}


