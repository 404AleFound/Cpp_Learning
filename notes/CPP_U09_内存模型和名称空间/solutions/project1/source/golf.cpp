// golf.cpp -- the detailed definition of golf.h
# include<iostream>
# include<cstring>
# include"golf.h"

using std::cout;
using std::endl;
using std::cin;

// non-interactive version:
// function sets golf structure to provided name, handicap
// using values passed as arguments to the function
void setgolf(golf & g, const char * name, int hc) {
	strcpy(g.fullname, name);
	g.handicap = hc;
}

// interactive version:
// function solicits name and handicap from user
// and sets the member of g to the values entered
// returns 1 if name is entered, 0 if name is empty string
int setgolf(golf & g) {
	cout << "Enter the name of golf member:";
	(cin.get(g.fullname, Len)).get();
	cout << "Enter the handicap of golf member:";
	cin >> g.handicap;
	if (g.fullname[0] == '\0') {
		return 0;
	}
	else {
		return 1;
	}
}


// function resets handicap to new value
void handicap(golf & g, int hc)
{
	g.handicap = hc;
}

// function displays contents of golf structure
void showgolf(const golf & g)
{
	cout << "fullname: " << g.fullname << ", handicap: " << g.handicap << endl;
}
