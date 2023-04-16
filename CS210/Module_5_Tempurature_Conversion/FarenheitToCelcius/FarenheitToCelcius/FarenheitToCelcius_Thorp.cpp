//Cameron Thorp CS210 - Module 5 Assignment - Farenheit to Celcius File Reading and Writing

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int convertFToC(int tempF) {
	double tempC;
	tempC = ((tempF - 32) * (5.0 / 9.0)); //Given formula for F to C
	tempC = int(tempC); //Converting tempC to an int before returning
	return tempC;
}

int main() {
	//Instantiation of stream reader and writer, and temp vars
	ifstream originalTemps;
	ofstream convertedTemps;
	string cityName;
	int cityTemp;

	//Open file to read from and write to for smooth operations
	originalTemps.open("FarenheitTemperature.txt");
	convertedTemps.open("CelciusTemperature.txt");

	originalTemps >> cityName;
	originalTemps >> cityTemp;

	while (!originalTemps.fail()) {
		//This loop functions with the given parameters of the assignment, if Cities with multiple words were included then getline and string manipulation would be required
		cityTemp = convertFToC(cityTemp);
		convertedTemps << cityName << " " << cityTemp << endl;

		originalTemps >> cityName;
		originalTemps >> cityTemp;

	}

	originalTemps.close();
	convertedTemps.close();
}