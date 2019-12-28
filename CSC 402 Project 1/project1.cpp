/*
File Name: project1.cpp
Author: Will St. Onge
Course: CSC 402 
Date: 
*/

#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <random>

using namespace std;
using namespace std::chrono;

/* The C/C++ old library for obtaining system time, similar to Java System.currentTimeMillis()
   is based on a clock() call and a special data type for the clock ticks.
   Like Java, there is a better alternative that can measure time in nanoseconds, microseconds, etc.

	clock_t _start, _end;        // basic time in ms. (assuming 1000 CLOCKS_PER_SEC)
	_start = clock();
	_end = clock();
	cout << "elapsed time using old system clock functions = " << (_end - _start) << endl;


	A finer-grained clock is available in the C++  <chrono> library, with options as to the unit of duration

	std::chrono::system_clock::time_point start, end;
	start = system_clock::now();
	end = system_clock::now();
	cout << "elapsed time using chrono (in nanoseconds): " << duration_cast<nanoseconds>(end - start).count() << endl;
	cout << "elapsed time using chrono (in microseconds): " << duration_cast<microseconds>(end - start).count() << endl;

	*/

	/* function prototypes (forward declaration)
	   Notice that any complex data type that is passed to a C++ function in which
	   there is an expectation that the data will not be changed is marked "const".
	   We will study this in more detail later.
	*/
void print(const int arr[], int size);
void print(const vector<int>& v);

bool isShuffled(const int arr[], int size);
bool isShuffled(const vector<int>& v);


int main()
{
	// It's a good idea to check this for your compiler/platform when using the legacy clock function.
	// For Windows/VS, its 1000, meaning millisecond granularity, but Linux may differ
	cout << "Default clock ticks per second: " << CLOCKS_PER_SEC << endl;

	// declare a primitive array of sizes to facilitate test runs of various sizes
	int sizes[]{ 10, 100, 1000, 10000, 100000, 1000000 };

	// declare data structures that can be initialized/reinitialized later
	int* arr = nullptr;  // must be heap-allocated since size is variable
	vector<int> v;     // type declaration only

	// declare time measurement variables
	std::chrono::system_clock::time_point start, end;
	clock_t _start, _end;

	cout << boolalpha << endl;  // turn on true-false display of bools

	// The test runs are managed by a for-each loop
	for (int sz : sizes) {

		// clear out data from previous trial and clean up heap-allocated memory
		if (arr != nullptr)
			delete[] arr;
		arr = new int[sz];

		v.clear();   // much simpler for vectors

		// C++ random number support that mimics Java's Random object
		// Generate random indexes in the range 0 to sz - 1 
		// See also the HINT below in the shuffle TODO
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0, sz - 1);


		cout << endl << "Time trials for array and vector of size " << sz << endl;
		cout << "=======================================================" << endl;

		start = system_clock::now();
		_start = clock();

		for (int i = 0; i < sz; i++)
			arr[i] = i + 1;

		end = system_clock::now();
		_end = clock();

		cout << "Elapsed time in nanoseconds for initializing a C++ primitive array of " << sz << " elements: " << duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;
		cout << "DEMO: Elapsed time in milliseconds for initializing a C++ primitive array of " << sz << " elements: " << (_end - _start) << endl;

		cout << "Initial state - arr isShuffled: " << isShuffled(arr, sz) << endl;
		print(arr, sz);

		start = system_clock::now();

		for (int i = 0; i < sz; ++i) {
			int pos1 = distribution(generator);
			int pos2 = distribution(generator);
			if (sz < 100)
				cout << "Swapping " << arr[pos1] << " with " << arr[pos2] << endl;
			int temp = arr[pos2];
			arr[pos2] = arr[pos1];
			arr[pos1] = temp;
		}

		end = system_clock::now();
		cout << "Post-shuffle state - arr isShuffled: " << isShuffled(arr, sz) << endl;
		print(arr, sz);
		cout << "Elapsed time in nanoseconds for shuffling a C++ primitive array of " << sz << " elements: " << duration_cast<std::chrono::nanoseconds>(end - start).count() << endl << endl;

		// Vector tests
		start = system_clock::now();

		for (int i = 0; i < sz; i++)
			v.push_back(i + 1);

		end = system_clock::now();
		cout << "Elapsed time in nanoseconds for initializing a C++ vector of " << sz << " elements: " << duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;

		cout << "Initial state - v isShuffled: " << isShuffled(v) << endl;
		print(v);

		start = system_clock::now();

		for (int i = 0; i < sz; ++i) {
			int pos1 = distribution(generator);
			int pos2 = distribution(generator);
			if (sz < 100)
				cout << "Swapping " << v.at(pos1) << " with " + v.at(pos2) << endl;
			int temp = v.at(pos2);
			v.at(pos2) = v.at(pos1);
			v.at(pos1) = temp;
		}

		end = system_clock::now();

		cout << "Post-shuffle state - v isShuffled: " << isShuffled(v) << endl;
		print(v);
		cout << "Elapsed time in nanoseconds for shuffling a C++ vector of " << sz << " elements: " << duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;
	}

	cin.get();
	return 0;
}

void print(const int arr[], int size)
{
	cout << "Array contents: ";
	if (size > 10)
		cout << arr[0] << ", " << arr[1] << ", " << arr[2] << " ... " << arr[size - 3] << ", " << arr[size - 2] << ", " << arr[size - 1];
	else
		for (int i = 0; i < size; i++)
			cout << arr[i] << "\t";
	cout << endl;
}

void print(const vector<int>& v)
{
	int size = v.size();
	cout << "Vector contents: ";

	if (size > 10)
		cout << v.at(0) << ", " << v.at(1) << ", " << v.at(2) << " ... " << v.at(size - 3) << ", " << v.at(size - 2) << ", " << v.at(size - 1);
	else
		for (int i = 0; i < size; i++)
			cout << v.at(i) << "\t";
	cout << endl;
}

bool isShuffled(const int arr[], int size)
{
	for (int i = 0; i < size - 1; ++i)
		if (arr[i] != arr[i + 1] - 1)
			return true;
	return false;
}

bool isShuffled(const vector<int>& v)
{
	for (int i = 0; i < v.size() - 1; ++i)
		if (v.at(i) != v.at(i + 1) - 1)
			return true;
	return false;
}