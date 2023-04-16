//Cameron Thorp - CS210 Project 2
#include "Banking.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//Variable declaration for displayed values
//double currentBalance = 0.0;
//double currentInterest = 0.0;
//double currentMonthly = 0.0;
//double currentTotal = 0.0;

//Method Definitions for Investment
Investment::Investment() {
	m_initialDeposit = 0;
	m_monthlyDeposit = 0;
	m_annualInterest = 0;
	m_years = 0;
}

void Investment::setInitialDeposit(double initialDeposit) {
	if (initialDeposit <= 0) {
		printf("Invalid initial deposit, must be non-negative. Initial deposit set to $0.00.\n");
		m_initialDeposit = 0;
	}
	else {
		m_initialDeposit = initialDeposit;
	}
}

double Investment::getInitialDeposit() {
	return m_initialDeposit;
}

void Investment::setMonthlyDeposit(double monthlyDeposit) {
	if (monthlyDeposit <= 0) {
		printf("Invalid monthly deposit, must be non-negative. Monthly deposit set to $0.00.\n");
		m_monthlyDeposit = 0;
	}
	else {
		m_monthlyDeposit = monthlyDeposit;
	}
}

double Investment::getMonthlyDeposit() {
	return m_monthlyDeposit;
}

void Investment::setAnnualInterest(double annualInterest) {
	if (annualInterest <= 0) {
		printf("Invalid interest percentage, must be non-negative. Interest set to 0%.\n");
		m_annualInterest = 0;
	}
	else {
		m_annualInterest = annualInterest;
	}
}

double Investment::getAnnualInterest() {
	return m_annualInterest;
}

void Investment::setYears(int years) {
	if (years <= 0) {
		printf("Invalid year, must be non-negative. Years set to 0.\n");
		m_years = 0;
	}
	else {
		m_years = years;
	}
	
}

int Investment::getYears() {
	return m_years;
}

//Methods for outputs

//Frequent buffer addition functions
void equalBuffer() {
	cout << endl << string(60, '=') << endl;
}

void dashBuffer() {
	cout << string(60, '-') << endl;
}

//Prints starting stream and gets initial values for investment displaying
Investment startingInformation() {
	Investment startingInvestment = Investment();
	double tempInitialDeposit;
	double tempMonthlyDeposit;
	double tempAnnualInterest;
	int tempYears;
	equalBuffer();
	cout << "==================== INITIAL DATA INPUT ====================" << endl;
	cout << "Initial Investment Amount: ";
	cin >> tempInitialDeposit;
	while (tempInitialDeposit < 0) {
		cout << "Please enter positive value: ";
		cin >> tempInitialDeposit;
	}
	cout << "Monthly Deposit Amount: ";
	cin >> tempMonthlyDeposit;
	while (tempMonthlyDeposit < 0) {
		cout << "Please enter positive value: ";
		cin >> tempMonthlyDeposit;
	}
	cout << "Annual Interest Percentage: ";
	cin >> tempAnnualInterest;
	while (tempAnnualInterest < 0) {
		cout << "Please enter positive value: ";
		cin >> tempAnnualInterest;
	}
	cout << "Years of Investment: ";
	cin >> tempYears;
	while (tempYears < 0) {
		cout << "Please enter positive value: ";
		cin >> tempYears;
	}
	startingInvestment.setInitialDeposit(tempInitialDeposit);
	startingInvestment.setMonthlyDeposit(tempMonthlyDeposit);
	startingInvestment.setAnnualInterest(tempAnnualInterest);
	startingInvestment.setYears(tempYears);
	cout << "Press any key to continue.";
	cin.ignore();
	return startingInvestment;
}

//Prints investment gains with and without extra monthly deposits
void yearlyIncomeND(Investment printInvestment) {
	equalBuffer();
	cout << "Balance and Interest Without Additional Monthly Deposits" << endl;
	dashBuffer();
	cout << "|  Year  "
		<< "|   Year End Balance   "
		<< "| Year End Earned Interest |" << endl;
	dashBuffer();

	double currentTotal = 0.0;
	double interestEarned = 0.0;
	double currentBalance = printInvestment.getInitialDeposit();
	double currentInterest = printInvestment.getAnnualInterest();
	double currentMonthly = printInvestment.getMonthlyDeposit();

	for (int year = 0; year < printInvestment.getYears(); year++) {
		int currentYear = year + 1;
		

		interestEarned = currentBalance * (currentInterest / 100);
		currentTotal = currentBalance + interestEarned;
		currentBalance = currentTotal;
		//cout.precision(2);
		//cout << setw(9) << currentYear << "|" << setw(15) << "$" << setprecision(2) << to_string(currentTotal) << "|" << setw(25) << '$' << setprecision(2) << to_string(interestEarned) << endl;
		printf("    %d    |        $%.2f        |          $%.2f          |\n", currentYear, currentTotal, interestEarned);
	}
}

void yearlyIncome(Investment printInvestment) {
	equalBuffer();
	cout << "Balance and Interest Including Additional Monthly Deposits" << endl;
	dashBuffer();
	cout << "|  Year  "
		<< "|   Year End Balance   "
		<< "| Year End Earned Interest |" << endl;
	dashBuffer();

	double currentTotal = printInvestment.getInitialDeposit();
	double interestEarned = 0.0;
	double currentBalance = printInvestment.getInitialDeposit();
	double currentInterest = printInvestment.getAnnualInterest();
	double currentMonthly = printInvestment.getMonthlyDeposit();

	for (int year = 0; year < printInvestment.getYears(); year++) {
		int currentYear = year + 1;
		interestEarned = 0.0;
		if (currentMonthly > 0.0) {
			for (int i = 0; i < 12; i++) {
				
				currentBalance = currentBalance + currentMonthly;
				interestEarned += (currentBalance * (currentInterest / 100)) / 12;
				currentBalance += (currentBalance * (currentInterest / 100)) / 12;
				
			}
		}
		else {
			currentBalance = currentTotal;
		}
		currentTotal = currentBalance;
		//cout << setw(9) << currentYear << "|" << setw(15) << "$" << to_string(currentTotal) << "|" << setw(25) << '$' << to_string(interestEarned) << endl;
		printf("    %d    |        $%.2f        |          $%.2f          |\n", currentYear, currentTotal, interestEarned);
	}
}

//Displays after each output to prompt user for next switch statement
int userMenu() {
	int menuSelection = 0;
	equalBuffer();
	cout << "Please enter the number of your option." << endl;
	cout << "[1] Change initial deposit." << endl;
	cout << "[2] Change monthly deposit." << endl;
	cout << "[3] Change interest rate." << endl;
	cout << "[4] Change years of investment." << endl;
	cout << "[5] Display current monthly calculations." << endl;
	cout << "[0] Quit." << endl;
	cout << "Selected option: ";
	cin >> menuSelection;
	return menuSelection;
}

void fullDisplay(Investment inputInvestment) {
	yearlyIncomeND(inputInvestment);
	yearlyIncome(inputInvestment);
}

//change functions to allow users to modify individual variables in their investment calculator
void changeInitialDeposit(Investment& changeInvestment) {
	equalBuffer();
	double newInitialInvestment = 0.0;
	cout << "Enter the new value for your initial investment." << endl;
	cout << "New Initial Investment: ";
	cin >> newInitialInvestment;
	while (newInitialInvestment < 0) {
		cout << "Please enter a positive value for initial investment.\nNew Initial Investment: " << endl;
		cin >> newInitialInvestment;
	}
	changeInvestment.setInitialDeposit(newInitialInvestment);
	printf("Initial investment now set to: $%.2f\n", newInitialInvestment);
}

void changeMonthlyDeposit(Investment& changeInvestment) {
	equalBuffer();
	double newMonthlyDeposit = 0.0;
	cout << "Enter the new value for your monthly deposit." << endl;
	cout << "New Monthly Deposit: ";
	cin >> newMonthlyDeposit;
	while (newMonthlyDeposit < 0) {
		cout << "Please enter a positive value for monthly deposit.\nNew Monthly Deposit: " << endl;
		cin >> newMonthlyDeposit;
	}
	changeInvestment.setMonthlyDeposit(newMonthlyDeposit);
	printf("Monthly deposit now set to: $%.2f\n", newMonthlyDeposit);
}

void changeInterestRate(Investment& changeInvestment) {
	equalBuffer();
	double newInterestRate = 0.0;
	cout << "Enter the new value for your interest rate." << endl;
	cout << "New Interest Rate: ";
	cin >> newInterestRate;
	while (newInterestRate < 0) {
		cout << "Please enter a positive value for interest rate.\nNew Interest Rate: " << endl;
		cin >> newInterestRate;
	}
	changeInvestment.setAnnualInterest(newInterestRate);
	printf("Interest rate now set to: %.2f%\n", newInterestRate);
}

void changeInvestmentLength(Investment& changeInvestment) {
	equalBuffer();
	int newLengthYears = 0.0;
	cout << "Enter the new value for your investment length." << endl;
	cout << "New Investment Length: ";
	cin >> newLengthYears;
	while (newLengthYears < 0) {
		cout << "Please enter a positive value for years.\nNew Investment Length: " << endl;
		cin >> newLengthYears;
	}
	changeInvestment.setYears(newLengthYears);
	printf("Length of investment now set to: %d years", newLengthYears);
}

//Monthly display after each deposit
void displayMonthlyCalc(Investment& printInvestment) {
	equalBuffer();
	cout << "Monthly Balance and Interest Including Additional Monthly Deposits" << endl;
	dashBuffer();
	cout << "| Month  "
		<< "|  Month End Balance   "
		<< "|Month End Earned Interest |" << endl;
	dashBuffer();

	double currentTotal = printInvestment.getInitialDeposit();
	double interestEarned = 0.0;
	double currentBalance = printInvestment.getInitialDeposit();
	double currentInterest = printInvestment.getAnnualInterest();
	double currentMonthly = printInvestment.getMonthlyDeposit();

	for (int month = 0; month < (printInvestment.getYears() * 12); month++) {
		int currentMonth = month + 1;
		if (currentMonthly > 0.0) {
			currentBalance = currentTotal + currentMonthly;
		}
		else {
			currentBalance = currentTotal;
		}
		interestEarned = (currentBalance * (currentInterest / 100) / 12);
		currentTotal = currentBalance + interestEarned;
		//cout << setw(9) << currentYear << "|" << setw(15) << "$" << to_string(currentTotal) << "|" << setw(25) << '$' << to_string(interestEarned) << endl;
		printf("    %d    |        $%.2f        |          $%.2f          |\n", currentMonth, currentTotal, interestEarned);
	}
}

int main() {
	cout << "Welcome to Airgead Banking's Investment Calculator!" << endl;
	cout << "Please begin by entering the following information." << endl;
	Investment baseInvestment = startingInformation();
	fullDisplay(baseInvestment);
	int currentUserSelection = userMenu();
	//Looping prompt to allow users to change inputs multiple times
	while (currentUserSelection != 0) {
		switch (currentUserSelection) {
			case 1:
				changeInitialDeposit(baseInvestment);
				fullDisplay(baseInvestment);
				break;
			case 2:
				changeMonthlyDeposit(baseInvestment);
				fullDisplay(baseInvestment);
				break;
			case 3:
				changeInterestRate(baseInvestment);
				fullDisplay(baseInvestment);
				break;
			case 4:
				changeInvestmentLength(baseInvestment);
				fullDisplay(baseInvestment);
				break;
			case 5:
				displayMonthlyCalc(baseInvestment);
				break;
			default:
				cout << "Invalid selection. Enter a number listed as an option." << endl;
				break;
		}
		currentUserSelection = userMenu();
	}
	cout << "Thank you for using Airgead Banking's Investment Calculator." << endl;
	cout << "Goodbye." << endl;
}