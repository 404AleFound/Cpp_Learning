// test.cpp -- test the function of golf
# include <iostream>
# include "golf.h"

int main()
{
	using namespace std;
	golf test1 = {};
	golf test2 = {};
	
	setgolf(test1, "Golden Golf", 156);
	setgolf(test2);
	
	showgolf(test1);
	showgolf(test2);
	
	handicap(test1, 234);
	showgolf(test1);
 } 
