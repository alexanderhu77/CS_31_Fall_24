#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


int main()
{
	double total = 0;
	int odometer_start;
	int odometer_end;
	int rental_days;
	string customer_name;
	string luxury_car;
	int starting_month;
	
	//messages for invalid inputs below
	cout << "Odometer at start: ";
	cin >> odometer_start;
	if (odometer_start < 0) {
		cout << "---"<< endl << "The starting odometer reading must not be negative." << endl;
		return 1;
	}
	
	cout << "Odometer at end: ";
	cin >> odometer_end;
	if (odometer_end < odometer_start) {
		cout << "---" << endl << "The ending odometer reading must be at least as large as the starting reading." << endl;
		return 1;
	}

	cout << "Rental days: ";
	cin >> rental_days;
	if (rental_days <= 0) {
		cout << "---" << endl << "The number of rental days must be positive." << endl;
		return 1;
	}

	cout << "Customer name: ";
	 
	cin.ignore(10000, '\n');
	getline(cin, customer_name);
	if (customer_name == "") {
		cout << "---" << endl << "You must enter a customer name." << endl;
		return 1;
	}

	cout << "Luxury car? (y/n): ";
	cin >> luxury_car;
	if (luxury_car != "y" && luxury_car != "n") {
		cout << "---" << endl << "You must enter y or n." << endl;
		return 1;
	}

	cout << "Starting month (1=Jan, 2=Feb, etc.): ";
	cin >> starting_month;
	if (starting_month <1 || starting_month > 12) {
		cout << "---" << endl << "The month number must be in the range 1 through 12." << endl;
		return 1;
	}
	
	if (luxury_car == "n") {
		total += 45*rental_days;
	}
	else {
		total += 75*rental_days;
	}

	int total_miles = odometer_end - odometer_start; //new variable created to track the number of miles driven
	
	// charges for miles up to 100
	if (total_miles <= 100) {
		total += total_miles * 0.33;
		
	}

	//charges for miles between 100 and 600
	else if (total_miles <= 600){
		total += 100* 0.33;
		total_miles -= 100;
		if (starting_month == 12 || starting_month <= 3) {
			total += 0.33 * total_miles;
		}
		else {
			total += 0.27 * total_miles;
		}
	}

	//charges for miles above 600
	else {
		total += 100 * 0.33;
		total_miles -= 100;
		if (starting_month == 12 || starting_month <= 3) {
			total += 0.33 * 500;
		}
		else {
			total += 0.27 * 500;
		}
		total_miles -= 500;
		total += total_miles * 0.21;
	}

	//prints out the final charge with double digit precision
	cout << "---" << endl << "The rental charge for " << customer_name << " is $" << fixed << setprecision(2) << total << endl;
	return 0;
}