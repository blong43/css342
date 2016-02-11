/**----------------------------------------------------------------------------
	@file lab1densitymain.cpp
    This program reads data from a seperate file and sorts the data
    in ascending order by the population densities of countries in list.

    @author Blong Thao
    @course CSS 342 Shields
    @version 01/12/14
-----------------------------------------------------------------------------*/

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const DECIMAL_PRECISION = 2;
double const ZERO_AREA = 0.01;
int const MAXRECORDS = 250;        // maximum number of records in file
int const MAXLENGTH = 32;          // maximum country name length 
int const MINAREA = 0;             // smallest possible area in km^2
char const INPUTFILE[] = "lab1data1.txt" ;
bool debug = false;

struct CountryStats {              // data for one country     
   int population;
   int area;                       // km^2
   double density;                 // pop/area
   char countryName[MAXLENGTH];    // country name (MAXLENGTH-1 at most)  
};

bool sortInput(ifstream&, CountryStats[], int&);
void displayRecords(const CountryStats[], const int);
void displayLowHigh(const CountryStats[], const int);
double findMedian(CountryStats[], int&);
double findAvg(const CountryStats[], const int);
double overallDen(const CountryStats[], const int);
void explanation(); // function is commented out due to being a cout line

/**------------------------------- main ---------------------------------------
   Runs the program and displays the methods invoked
   @pre Needs methods invoked OR cout/cin to output information.
   @post Outputs the programs functions.
   @return An integer.
*/
int main( int argc, char* argv[] ) {
    bool successfulRead = false;
   
    CountryStats countries[MAXRECORDS]; 
    int records = 0; // number of records processed
 
    ifstream infile(INPUTFILE);  // create file object and open the data file
	if (!infile)  { 
		cerr << "File could not be opened." << endl;
		return false;  
	}
	// get record and sort each, as encountered, by density and country name
	successfulRead = sortInput(infile, countries, records);

	// the functions occur only after the data has been read from file;
	// regardless if the data has negative or positive values.
	// functions account for negative values and empty lists.
	if (successfulRead)  {
		displayRecords(countries, records);
		displayLowHigh(countries, records);
		cout << "Median: " << findMedian(countries, records) << endl;
		cout << "Average: " << findAvg(countries, records) << endl;
		cout << "Overall Density: " << overallDen(countries, records) << endl;
		explanation();    // at the bottom of this program, unsure to print
	}
	return 0;
}

/**------------------------------- sortInput ----------------------------------
   Receives data from a file and sorts the data in descending order
   from highest density to lowest density.
   @param infile  The data that goes into this function.
   @param countries[]  The array that holds the countries.
   @param count  The records processed.
   @pre A file to read from.
   @post Inputs all the data from the file into countries array.
   @return Always true to run successfulread in main;
		   otherwise, function stops running.
*/

bool sortInput(ifstream& infile, CountryStats countries[], int& records) {
	// reads in the file's data into a temporary location
	// does not store negative populations and areas
	// done when its the end of file
	while (records < MAXRECORDS) {
		CountryStats temp;
		infile >> temp.countryName >> temp.population >> temp.area;
		if ( temp.population < 0 || temp.area < 0 ) break;
		if ( infile.eof() ) break;
		// trying to keep area as close to its real value
		if (temp.area == 0) {
			temp.density = 
				(double) temp.population / (temp.area + ZERO_AREA);
		} else
			temp.density = (double) temp.population / temp.area;

		// insertion sort; when the new data is smaller than the current it
		// copies the current data to the right and inserts the data in the 
		// temporary location to the index of the current spot
		int index = records-1;
		for (; index >= 0; index--) {
			// shift current data to the right when new density is smaller.
			if (temp.density < countries[index].density)
				countries[index+1] = countries[index];
			// shift current data to the right when new density is equal 
			// and when the new name is smaller.
			else if (temp.density == countries[index].density 
				&& strcmp(temp.countryName, countries[index].countryName) < 0)
				countries[index+1] = countries[index];
			// found right place, break out of loop
			else 
				break;
		}
		countries[++index] = temp;
		records++;
	}
    return true;
}

/**---------------------------------- displayRecords --------------------------
   Shows the list of records.
   @param countries The list of countries.
   @param records The amount of records.
   @pre Needs to have a list of records ready to display.
   @post Displays the list of records:  Country, Area, Population, Density.
   @return Void.
*/
void displayRecords(const CountryStats countries[], const int records) {
	cout << "List of Countries sorted: " << endl;
	for (int i = 0; i < records; i++) {
			cout << countries[i].countryName
				 << " " << countries[i].area
				 << " " << countries[i].population
				 << setprecision(DECIMAL_PRECISION) << fixed
				 << " " << countries[i].density << endl;
	}
	cout << endl;
}

/**------------------------------- displayLowHigh -----------------------------
   Prints the density values of the listed countries for lowest and highest
   density values, sorted array, prints the first and last country's density
   @param countries  The array the function looks into.
   @param records  The amount of countries in the list.
   @pre Needs to have records to look into, and already sorted.
   @post Prints lowest and highests density values.
   @return Void.
*/
void displayLowHigh(const CountryStats countries[], const int records) {
	double low = 0;
	double high = 0;
	// check for zero records
	if (records < 1)
		cout << "No records" << endl;
	// check for one record
	if (records == 1) {
		low = countries[0].density;
		high = countries[0].density;
	}
	// check for more than one record
	if (records > 1) {
	    low = countries[0].density;
		high = countries[records-1].density;
	}
	cout << "Lowest Density: " << low << endl;
	cout << "Highest Density: " << high << endl;
}

/**------------------------------- findMedian ---------------------------------
   Finds the median for the list and checks for both the even record amount 
   lists and also removes the negative density values
   @param countries  The array function look through for the median density
   @param records  The amount of countries in the list.
   @pre Needs to have records to look into, and already sorted.
   @post Finds median density value.
   @return A double.
*/
double findMedian(CountryStats countries[], int& records) {
	// checks for empty list and negative value for records
	if (records < 1)
		return -1;
	// print out the only record
	if (records == 1)
		return countries[0].density;
	// finds the median in the array for odd and even arrays
	int mid = ((records - 1) / 2);
	// checks for even lists and does a special calucation to determine median
	if ((records-1) % 2)
		return (countries[mid].density + countries[mid+1].density) / 2;
	return countries[mid].density;
}

/**----------------------------- findAvg --------------------------------------
   Adds up the density values in the list and divides it by the records to find
   the average.
   @param countries The array the function looks through.
   @param records The amount of countries records.
   @pre Needs countries; otherwise, -1 is the output.
   @post The average of the list is the output.
   @return A double.
*/
double findAvg(const CountryStats countries[], const int records) {
	// check for empty list and negative record value
	if (records < 1)
		return -1;
	// list's density average and errors
	double average = 0;
	// the sum of the densities in list; accounts for errors
	for (int i = 0; i < records; i++) { 
			average += countries[i].density;
			// cout << "density #" << i << ": " << countries[i].density << endl;
	}
	//cout << "Sum: " << average << endl;
	//cout << "Records: " << records << endl;
	// the actual calcuation for average
	return average / records;

}

/**-------------------------- overallDensity ----------------------------------
   Finds the density of the total population / area
   @param countries  The array the function looks through.
   @param records  The amount of countries in the array.
   @pre Needs data; otherwise, -1 is the output.
   @post The overall density is the output.
   @return A double.
*/
double overallDen(const CountryStats countries[], const int records) {
	// checks for empty list
	if (records < 1)
		return -1;
	// the sums of both area and population, overall density
	// total population cannot be an integer because the population
	// amount could be overwhelming and surpass the limit of the int;
	// thus producing a negative value.
	int totalArea = 0;
	long long totalPop = 0;
	double density = 0;
	// adds up all records
	for (int i = 0; i < records; i++) {
		totalArea += countries[i].area;
		totalPop += countries[i].population;
	}
	cout << "Area: " << totalArea << endl;
	cout << "Population: " << totalPop << endl;
	// overall density of list
	density = (double) totalPop / totalArea;
	return density;
}

/**---------------------- explanation -----------------------------------------
	Explains the results of steps 4 and 5
	@pre None.  
	@post Output explaining the results of steps 4 and 5
	@return Void.
*/
void explanation() {
	// I was not sure if you wanted this to be displayed at the end
	// since the instructions said that these tasks needs to be displayed
	// in the specified order:
	// 1. display each records, one country per line as the country name 
	//	  followed by the area, followed by the population followed by the
	//    density; you must have calculated and stored densities before
	//    traversal of the struct array.
	// - steps 2, 3, 4, 5; countinue on to the last task -
	// 6. explain the results of step 4 and 5.
	//cout<< "The results of steps 4 and 5 differ due to the different" << endl
	//    << "types of calculations that these functions used to find" << endl
	//	  << "what they were looking for. The average density of all" << endl
	//	  << "countries was found through dividing up the total " << endl
	//	  << "density by the total records. While the overall density" << endl
	//	  << "was found by finding the total population and area, and" << endl
	//	  << "dividing total population by total area to get the" << endl
	//	  << "overall density. Thus, each function's results differed." << endl;
}
