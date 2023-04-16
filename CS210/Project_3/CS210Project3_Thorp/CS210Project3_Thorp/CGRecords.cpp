//Cameron Thorp, CS210 Programming Languages, Project 3
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class PurchaseHistory {
public:
	PurchaseHistory();
	PurchaseHistory(string inputFile);
	void SetSourceFile(string fileName);
	string GetSourceFile();
	void SetDestFile(string fileName);
	string GetDestFile();
	void SetItems();
	void SingleItemLookup(string ItemToLookup);
	void AllFreqByNum();
	void AllFreqByVisual();
	void FileBackup();
private:
	map<string, int> item_freqs;
	string sourceFile;
	string destFile;
};

//Constructor Definitions for history obj
PurchaseHistory::PurchaseHistory() {
	item_freqs;
	sourceFile = "CS210_Project_Three_Input_File.txt";
	destFile = "frequency.dat";
}

//Leaves open for future feature to choose a file instead of relying on exerior naming convention
PurchaseHistory::PurchaseHistory(string inputFile) {
	item_freqs;
	sourceFile = inputFile;
	destFile = "frequency.dat";
}

//Getters and setters for history obj
void PurchaseHistory::SetSourceFile(string fileName) {
	this->sourceFile = fileName;
}

string PurchaseHistory::GetSourceFile() {
	return this->sourceFile;
}

void PurchaseHistory::SetDestFile(string fileName) {
	this->destFile = fileName;
}

string PurchaseHistory::GetDestFile() {
	return this->destFile;
}

void PurchaseHistory::SetItems() {
	ifstream inputData;
	try {
		inputData.open(this->sourceFile);
	}
	catch (...) {
		cout << "File error, no data loaded." << endl;
	}
	string tempItem;
	
	while (!inputData.eof()) {
		inputData >> tempItem;
		if (this->item_freqs.count(tempItem) == 0) {
			item_freqs.emplace(tempItem, 1);
		}
		else if (this->item_freqs.count(tempItem) == 1) {
			item_freqs.at(tempItem) += 1;
		}
	}
	if (!inputData.eof()) {
		cout << "Input failed before reaching end of file." << endl;
	}
	inputData.close();
}

//Also getters, but used to complete operational requirements
void PurchaseHistory::SingleItemLookup(string itemToLookup) {
	if (this->item_freqs.count(itemToLookup) != 0) {
		cout << itemToLookup << " appears " << this->item_freqs.at(itemToLookup) << " times in current data set." << endl;
	}
	else {
		cout << itemToLookup << " was not found in the loaded data (data is case sensitive)." << endl;
	}
}

//Uses map iterator to output the key and value of each item
void PurchaseHistory::AllFreqByNum() {
	map<string, int>::iterator iter;
	for (iter = this->item_freqs.begin(); iter != this->item_freqs.end(); iter++) {
		cout << iter->first << " " << iter->second << endl;
	}
}

//
void PurchaseHistory::AllFreqByVisual() {
	map<string, int>::iterator iter;
	for (iter = this->item_freqs.begin(); iter != this->item_freqs.end(); iter++) {
		cout << iter->first << " ";
		for (int i = 0; i < iter->second; i++) {
			cout << "*";
		}
		cout << endl;
	}
}

void PurchaseHistory::FileBackup() {
	ofstream outputData;
	outputData.open(this->destFile);
	if (!outputData.is_open()) {
		cout << "Backup File could not be accessed. Backup failed." << endl;
	}
	else {
		map<string, int>::iterator iter;
		for (iter = this->item_freqs.begin(); iter != this->item_freqs.end(); iter++) {
			outputData << iter->first << " " << iter->second << endl;
		}
		cout << "Backup to 'frequency.dat' completed." << endl;
		outputData.close();
	}
}

//Menu list for users to choose form
void printMenu() {
	
	cout << "1. Single item lookup." << endl;
	cout << "2. All item frequency by number." << endl;
	cout << "3. All item visual frequency." << endl;
	cout << "4. Quit." << endl;
}

//Message to display at start of session
void welcomeMessage() {
	cout << "Welcome to the Corner Grocer records system!" << endl;
	cout << "A backup of activity will be generated and can be found in CGRecords.txt" << endl;
}

//Simple buffer for readability
void dataBuffer() {
	cout << string(30, '=') << endl;
}

string itemAssigner() {
	string itemInput = "Invalid input";
	cout << "Input item to lookup: ";
	while (itemInput == "Invalid input") {
		try {
			cin >> itemInput;
		}
		catch (ios_base::failure& except) {
			cin.clear();
			itemInput = "Invalid input";
		}
	}
	return itemInput;
}

//Looping menu selection for user to perform vaiable number of operations
void runningRecords(PurchaseHistory* purchases) {
	string rawInput;
	int userInput = 0;
	while (userInput != 4) {
		system("CLS");
		printMenu();
		cout << "Please select operation by number: ";
		cin >> rawInput;

		//Trys to convert any input into a usable menu option or resets to default value
		//This handles both negative numbers, and non-integer inputs
		try {
			userInput = stoi(rawInput);
		}
		catch (...) {
			cin.clear();
			userInput = 0;
		}

		//Calls required function or requests a valid input depending on user input
		switch (userInput) {
			case 1:
				purchases->SingleItemLookup(itemAssigner());
				dataBuffer();
				break;
			case 2:
				purchases->AllFreqByNum();
				dataBuffer();
				break;
			case 3:
				purchases->AllFreqByVisual();
				dataBuffer();
				break;
			case 4:
				cout << "Operations complete." << endl;
				break;
			default:
				cout << "Invalid option, please enter a menu number." << endl;
				break;
		}
		system("pause");
		cin.clear();
	}
}

//Message to confirm action and remind user of backup location
void closeMessage() {
	cout << "Thank you for using Corner Grocer records system." << endl;
	cout << "Goodbye." << endl;
}

int main() {
	cin.exceptions(ios::failbit);
	PurchaseHistory* todaysPurchases = new PurchaseHistory();
	todaysPurchases->SetItems();
	welcomeMessage();
	runningRecords(todaysPurchases);
	todaysPurchases->FileBackup();
	closeMessage();
}