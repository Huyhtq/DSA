#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

mutex mtx;  //protect comparisons in multi threads

int linearSearch(const vector<int>& arr, int x, int& comparisons) {
	int result = -1;
	for (int i = 0; i < arr.size(); i++) {
		mtx.lock();
		comparisons++;  // count comparisons
		mtx.unlock();
		if (arr[i] == x) {
			result = i;
			break;
		}
	}
	return result;
}

int binarySearch(const vector<int>& arr, int x, int& comparisons) {
	int left = 0, right = arr.size() - 1;
	int result = -1;
	while (left <= right) {
		mtx.lock();
		comparisons++;  // count comparisons
		mtx.unlock();
		int mid = left + (right - left) / 2;
		if (arr[mid] == x) {
			result = mid;
			break;
		}
		else if (arr[mid] < x) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return result;
}

int binarySearchCount(vector<int>& arr, int x) {
	int left = 0, right = arr.size() - 1, result = -1, count = 0;
	//binary search
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] == x) {
			result = mid;
			count++;
			break;
		}
		else if (arr[mid] < x) {
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	// find left 
	int i = result - 1;
	while (arr[i] == x) {
		count++;
		i--;
	}
	// find right
	i = result + 1;
	while (arr[i] == x) {
		count++;
		i++;
	}
	return count;
}


int findStep(const vector<int>& arr, int target, int step, int sizeArr) {
	if (step >= sizeArr || arr[step] >= target) {
		return step;
	}
	return findStep(arr, target, step + sqrt(sizeArr), sizeArr);
}

int jumpSearch(const vector<int>& arr, int x, int& comparisons) {
	int n = arr.size();
	int step = findStep(arr,x,0,n);
	int prev = step - sqrt(n);

	for (int i = prev; i < min(step, n); i++) {
		mtx.lock();
		comparisons++;  // count comparisons
		mtx.unlock();
		if (arr[i] == x) {
			return i;
		}
	}

	return -1;
}

void inputArr(vector<int>& arr) {
	int x;
	cout << "Input your sorted list( -1 to stop): ";
	cin >> x;
	while (x >= 0) {
		arr.push_back(x);
		int y = x;
		cin >> x;
		if (x == -1 or x < y)
			break;
	}
}

void exercise01() {
	vector<int> arr;
	inputArr(arr);
	int x;
	cout << "Input target: ";
	cin >> x;

	int result = binarySearchCount(arr, x);

	cout << "Target " << x << " appear: " << result << " times!" << endl;
}

void exercise02() {
	vector<int> arr;
	inputArr(arr);
	int x;
	cout << "Input target: ";
	cin >> x;
	int step, comparisons;
	
	int result = jumpSearch(arr, x, comparisons);

	if (result == -1)
		cout << "Not found!";
	else
		cout << "Index = " << result;
}

int interpolationSearch(vector<string>& arr, string& x) {
	int low = 0, high = arr.size() - 1;

	while (low <= high && x[0] >= arr[low][0] && x[0] <= arr[high][0]) {
		// If the search has narrowed down to a single element
		if (low == high) {
			if (arr[low] == x) return low;
			else return -1;
		}

		// Estimate the position based on lexicographic distance for the first character
		int pos = low + (high - low) * (x[0] - arr[low][0]) / (arr[high][0] - arr[low][0]);

		// Ensure position is within bounds
		if (pos < 0 || pos >= arr.size()) return -1;

		// Check the string at the estimated position
		if (arr[pos] == x) {
			return pos;
		}
		else if (arr[pos] < x) {
			low = pos + 1;
		}
		else {
			high = pos - 1;
		}
	}

	// Perform linear search around the position found, if the prefix matches
	for (int i = low; i <= high; i++) {
		if (arr[i][0] != x[0]) break;  // Stop if first character no longer matches
		if (arr[i] == x) {
			return i;
		}
	}

	return -1;  // Return -1 if not found
}

void inputStringArr(vector<string>& arr) {
	int c;
	cout << "Size of array: ";
	cin >> c;
	cin.ignore();

	arr.resize(c);
	cout << "Input array: " << endl;

	for (int i = 0; i < c; ++i) {
		cout << "String " << i + 1 <<" : ";
		getline(cin, arr[i]); 
	}
	
}

void exercise03() {
	vector<string> arr;
	inputStringArr(arr);
	string s;
	cout << "Target: ";
	getline(cin, s);
	cout << interpolationSearch(arr,s);
}

int findMissingNumber(vector<int>& arr) {
	int left = 0, right = arr.size();

	while (left < right) {
		int mid = left + (right - left) / 2;

		// If the current element matches its index, missing number must be on the right
		if (arr[mid] == mid) {
			left = mid + 1;
		}
		else {
			// Otherwise, missing number is on the left
			right = mid;
		}
	}

	// 'left' now points to the missing number
	return left;
}

void exercise04() {
	vector<int> arr;
	inputArr(arr);
	cout << "Missing number is: " << findMissingNumber(arr);
}

void executeSearch(const vector<int>& arr, int x, int (*searchFunc)(const vector<int>&, int, int&), const string& searchType) {
	int comparisons = 0;  // reset counter
	auto start = chrono::high_resolution_clock::now();
	int result = searchFunc(arr, x, comparisons);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;

	lock_guard<mutex> lock(mtx);
	cout << searchType << " Search Result: " << result << endl;
	cout << searchType << " Comparisons: " << comparisons << endl;
	cout << searchType << " Execution Time: " << duration.count() << " seconds" << endl<< endl;
}

void exercise05() {
	vector<int> arr;
	inputArr(arr);

	int target;
	cout << "Enter target: ";
	cin >> target;

	thread linearThread([&]() { executeSearch(arr, target, linearSearch, "Linear"); });
	thread binaryThread([&]() { executeSearch(arr, target, binarySearch, "Binary"); });
	thread jumpThread([&]() { executeSearch(arr, target, jumpSearch, "Jump"); });

	linearThread.join();
	binaryThread.join();
	jumpThread.join();
}

int bidirectionalBinarySearch(const vector<int>& arr, int x, int &comparisons) {
	int left = 0, right = arr.size() / 2 - 1;          // Left search pointers
	int leftRev = arr.size() / 2, rightRev = arr.size() - 1;  // Right search pointers

	while (left <= right && leftRev <= rightRev) {
		// Left half binary search
		int mid = left + (right - left) / 2;
		comparisons++;  // Count comparison
		if (arr[mid] == x) {
			return mid;
		}
		comparisons++;  // Count comparison
		if (arr[mid] < x) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}

		// Right half binary search
		int midRev = leftRev + (rightRev - leftRev) / 2;
		comparisons++;  // Count comparison
		if (arr[midRev] == x) {
			return midRev;
		}
		comparisons++;  // Count comparison
		if (arr[midRev] < x) {
			leftRev = midRev + 1;
		}
		else {
			rightRev = midRev - 1;
		}

		// If ranges overlap, the element is not present
		if (left > right && leftRev > rightRev) {
			return -1;
		}
	}

	return -1;  // Target not found
}

void compareSearches(const vector<int>& arr, int target) {
	// Traditional Binary Search
	int comparisons = 0;
	auto start1 = chrono::high_resolution_clock::now();
	int result1 = binarySearch(arr, target, comparisons);
	auto end1 = chrono::high_resolution_clock::now();
	chrono::duration<double> duration1 = end1 - start1;

	cout << "Traditional Binary Search Result: " << result1 << "\n";
	cout << "Traditional Comparisons: " << comparisons << "\n";
	cout << "Traditional Execution Time: " << duration1.count() << " seconds\n";

	// Bidirectional Binary Search
	comparisons = 0;
	auto start2 = chrono::high_resolution_clock::now();
	int result2 = bidirectionalBinarySearch(arr, target, comparisons);
	auto end2 = chrono::high_resolution_clock::now();
	chrono::duration<double> duration2 = end2 - start2;

	cout << "Bidirectional Binary Search Result: " << result2 << "\n";
	cout << "Bidirectional Comparisons: " << comparisons << "\n";
	cout << "Bidirectional Execution Time: " << duration2.count() << " seconds\n";
}

void exercise06() {
	vector<int> arr;
	inputArr(arr);

	int target;
	cout << "Enter target: ";
	cin >> target;

	compareSearches(arr, target);
}

// Partition function for Quickselect
int partition(vector<int>& arr, int low, int high) {
	int pivot = arr[high]; // Choose the last element as pivot
	int i = low; // Index of the smaller element

	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
			swap(arr[i], arr[j]);
			i++;
		}
	}
	swap(arr[i], arr[high]);
	return i;
}

// Quickselect function to find the k-th smallest element
int quickSelect(vector<int>& arr, int low, int high, int k) {
	if (low <= high) {
		int pivotIndex = partition(arr, low, high);

		// Check if pivot position is the k-th smallest
		if (pivotIndex == k) {
			return arr[pivotIndex];
		}
		else if (pivotIndex > k) {
			return quickSelect(arr, low, pivotIndex - 1, k);
		}
		else {
			return quickSelect(arr, pivotIndex + 1, high, k);
		}
	}
	return -1; // Error case (k out of bounds)
}

// Function to find the k-th smallest element
int findKthSmallest(vector<int>& arr, int k) {
	int n = arr.size();
	if (k < 1 || k > n) {
		cout << "k is out of bounds\n";
		return -1;
	}
	return quickSelect(arr, 0, n - 1, k - 1);
}

void inputUnsortedArr(vector<int>& arr) {
	int x;
	cout << "Input your list( -1 to stop): ";
	cin >> x;
	while (x >= 0) {
		arr.push_back(x);
		cin >> x;
	}
}

void exercise07() {
	vector<int> arr;
	inputUnsortedArr(arr);

	cout << "Input k: ";
	int k;
	cin >> k;

	cout << "The " << k << "-th smallest element is " << findKthSmallest(arr, k) << endl;
}

void showMenu() {
	system("cls");
	cout << "\n--- Lab3 ---\n"
		 << "1. Exercise 1\n"
		 << "2. Exercise 2\n"
		 << "3. Exercise 3\n"
		 << "4. Exercise 4\n"
		 << "5. Exercise 5\n"
		 << "6. Exercise 6\n"
		 << "7. Exercise 7\n"
		 << "8. Clear screen\n"
		 << "0. Exit\n";
}

void Menu() {
	int choice;
	showMenu();
	do {
		cout << "\nEnter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			exercise01();
			break;
		case 2:
			exercise02();
			break;
		case 3:
			exercise03();
			break;
		case 4:
			exercise04();
			break;
		case 5:
			exercise05();
			break;
		case 6:
			exercise06();
			break;
		case 7:
			exercise07();
			break;
		case 8:
			showMenu();
			break;
		case 0:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice! Please enter a valid option.\n";
			break;
		}
	} while (choice != 0);
}

int main() {
	Menu();

}
