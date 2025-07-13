// Sales.cpp -- definition in Sales.h file
# include <iostream>
# include "Sales.h"

namespace SALES {
	// copies the lesser of 4 or n items from the array ar
    // to the sales member of s and computes and stores the
    // average, maximum, and minimum values of the entered items;
    // remaining elements of sales, if any, set to 0
    void setSales(Sales & s, const double ar[], int n) {
    	double max = 0, min = 0, average = 0;
    	
    	for (int i = 0; i < n; i++) {
    		s.sales[i] = ar[i];
    		if (ar[i] > max)
    			max = ar[i];
    		if (ar[i] < min)
    			min = ar[i];
    		average += ar[i];
		}
		average /= n;
		s.max = max;
		s.min = min;
		s.average = average;
	}
    
    // gathers sales for 4 quarters interactively, store them
    // in the sales member of s and computess and stores the
    // average, maxium, and minimum values
    void setSales(Sales & s) {
    	std::cout << "Enter the sales of "<< QUARTERS <<" quarters.\n";
    	double s_[QUARTERS];
    	for (int i = 0; i < QUARTERS; i++) {
    		std::cout << "quarter " << i+1 <<":"; 
    		std::cin >> s_[i];
		}
		setSales(s, s_, QUARTERS);
	}
    
    // display all infromation in structure s
    void showSales(const Sales & s) {
    	std::cout << "The sales are: ";
    	for (int i = 0; i < QUARTERS; i++)
    		std::cout << s.sales[i] << " ";
    	std::cout << std::endl;
    	std::cout << "Max sales: " << s.max << std::endl;
    	std::cout << "Min sales: " << s.max << std::endl;
    	std::cout << "Average sales: " << s.max << std::endl;
	}
}

