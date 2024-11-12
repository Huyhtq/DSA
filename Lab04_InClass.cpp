#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// Function to generate a list of random integers
vector<int> generateRandomList(int size, int min = 1, int max = 1000) {
    vector<int> list(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    for (int& num : list) {
        num = dist(gen);
    }
    return list;
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Helper function to measure execution time
template <typename Func>
void measureTime(Func func, vector<int> arr, const string& sortName) {
    auto start = chrono::high_resolution_clock::now();
    func(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " took " << duration.count() << " seconds.\n";
}

// Helper function to measure execution time
template <typename Func>
void measureTime(Func func, vector<int> arr, const string& sortName, int size) {
    auto start = chrono::high_resolution_clock::now();
    func(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " (size " << size << ") took " << duration.count() << " seconds.\n";
}

// Exercise01 function (for single-size test case)
void Exercise01() {
    int size = 1000;
    auto originalList = generateRandomList(size);

    // Measure time for each sorting algorithm
    measureTime(selectionSort, originalList, "Selection Sort", size);
    measureTime(bubbleSort, originalList, "Bubble Sort", size);
    measureTime(insertionSort, originalList, "Insertion Sort", size);
    measureTime([&](vector<int> arr) { quickSort(arr, 0, arr.size() - 1); }, originalList, "Quick Sort", size);
    measureTime([&](vector<int> arr) { mergeSort(arr, 0, arr.size() - 1); }, originalList, "Merge Sort", size);
}

// Exercise02 function (for multiple array sizes)
void Exercise02() {
    vector<int> sizes = { 100, 1000, 10000 };  // Different array sizes to test

    for (int size : sizes) {
        auto originalList = generateRandomList(size);

        // Measure time for each sorting algorithm
        measureTime(selectionSort, originalList, "Selection Sort", size);
        measureTime(bubbleSort, originalList, "Bubble Sort", size);
        measureTime(insertionSort, originalList, "Insertion Sort", size);
        measureTime([&](vector<int> arr) { quickSort(arr, 0, arr.size() - 1); }, originalList, "Quick Sort", size);
        measureTime([&](vector<int> arr) { mergeSort(arr, 0, arr.size() - 1); }, originalList, "Merge Sort", size);
        cout << endl;
    }
}

// Function to generate a list of random integers, strings, or floats
template <typename T>
vector<T> generateRandomList(int size, T min, T max) {
    vector<T> list(size);
    random_device rd;
    mt19937 gen(rd());

    if constexpr (is_integral<T>::value) {
        uniform_int_distribution<> dist(min, max);
        for (auto& num : list) {
            num = dist(gen);
        }
    }
    else if constexpr (is_floating_point<T>::value) {
        uniform_real_distribution<> dist(min, max);
        for (auto& num : list) {
            num = dist(gen);
        }
    }
    else if constexpr (is_same<T, string>::value) {
        uniform_int_distribution<> dist(97, 122);  // lowercase letters a-z
        for (auto& str : list) {
            str = "";
            for (int i = 0; i < 5; ++i) {  // Random 5-letter strings
                str += static_cast<char>(dist(gen));
            }
        }
    }
    return list;
}

// Selection Sort
template <typename T>
void selectionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Bubble Sort
template <typename T>
void bubbleSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
template <typename T>
void insertionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort
template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quickSort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
template <typename T>
void merge(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<T> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

template <typename T>
void mergeSort(vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Helper function to measure execution time
template <typename Func, typename T>
void measureTime(Func func, vector<T> arr, const string& sortName, int size) {
    auto start = chrono::high_resolution_clock::now();
    func(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " (size " << size << ") took " << duration.count() << " seconds.\n";
}

template <typename T>
void Exercise03() {
    vector<int> sizes = { 100, 1000, 10000 };  // Different array sizes to test

    for (int size : sizes) {
        cout << "\nTesting with size: " << size << "\n";

        // Test with integers
        cout <<"int: "<< endl;
        auto intList = generateRandomList<int>(size, 1, 1000);
        measureTime(selectionSort<int>, intList, "Selection Sort (int)", size);
        measureTime(bubbleSort<int>, intList, "Bubble Sort (int)", size);
        measureTime(insertionSort<int>, intList, "Insertion Sort (int)", size);
        measureTime([&](vector<int> arr) { quickSort(arr, 0, arr.size() - 1); }, intList, "Quick Sort (int)", size);
        measureTime([&](vector<int> arr) { mergeSort(arr, 0, arr.size() - 1); }, intList, "Merge Sort (int)", size);
        cout << endl;

        // Test with floating point numbers
        cout << "double: " << endl;
        auto floatList = generateRandomList<double>(size, 1.0, 1000.0);
        measureTime(selectionSort<double>, floatList, "Selection Sort (float)", size);
        measureTime(bubbleSort<double>, floatList, "Bubble Sort (float)", size);
        measureTime(insertionSort<double>, floatList, "Insertion Sort (float)", size);
        measureTime([&](vector<double> arr) { quickSort(arr, 0, arr.size() - 1); }, floatList, "Quick Sort (float)", size);
        measureTime([&](vector<double> arr) { mergeSort(arr, 0, arr.size() - 1); }, floatList, "Merge Sort (float)", size);
        cout << endl;

        // Test with strings
        cout << "string: " << endl;
        auto strList = generateRandomList<string>(size, "", "");
        measureTime(selectionSort<string>, strList, "Selection Sort (string)", size);
        measureTime(bubbleSort<string>, strList, "Bubble Sort (string)", size);
        measureTime(insertionSort<string>, strList, "Insertion Sort (string)", size);
        measureTime([&](vector<string> arr) { quickSort(arr, 0, arr.size() - 1); }, strList, "Quick Sort (string)", size);
        measureTime([&](vector<string> arr) { mergeSort(arr, 0, arr.size() - 1); }, strList, "Merge Sort (string)", size);
        cout << endl;


    }
}

// Helper function to measure execution time
template <typename Func, typename Container>
void measureTime(Func func, Container& container, const string& sortName) {
    auto start = chrono::high_resolution_clock::now();
    func(container);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " took " << duration.count() << " seconds.\n";
}

// Exercise04: Sorting Algorithms for Linked List, Queue, and Stack
void Exercise04() {
    vector<int> sizes = { 100, 1000, 10000 };  // Different array sizes to test

    for (int size : sizes) {
        cout << "\nTesting with size: " << size << "\n";

        // Create a random list for sorting
        auto originalList = generateRandomList(size);

        // --- Linked List Sorting ---
        list<int> linkedList(originalList.begin(), originalList.end());
        auto linkedListCopy = linkedList;
        measureTime([](list<int>& ll) { ll.sort(); }, linkedListCopy, "Linked List Sort");

        // --- Queue Sorting ---
        queue<int> q;
        for (int num : originalList) {
            q.push(num);
        }
        auto qCopy = q;
        vector<int> qVec;
        while (!qCopy.empty()) {
            qVec.push_back(qCopy.front());
            qCopy.pop();
        }
        measureTime([&](vector<int>& qVec) { sort(qVec.begin(), qVec.end()); }, qVec, "Queue Sort");

        // --- Stack Sorting ---
        stack<int> s;
        for (int num : originalList) {
            s.push(num);
        }
        auto sCopy = s;
        vector<int> sVec;
        while (!sCopy.empty()) {
            sVec.push_back(sCopy.top());
            sCopy.pop();
        }
        measureTime([&](vector<int>& sVec) { sort(sVec.begin(), sVec.end()); }, sVec, "Stack Sort");

        cout << endl;
    }
}

// Binary Search to find the insertion position
template <typename T>
int binarySearch(const vector<T>& arr, int start, int end, const T& key) {
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) start = mid + 1;
        else end = mid - 1;
    }
    return start; // return the position where key should be inserted
}

// Insertion Sort using Binary Search
template <typename T>
void binaryInsertionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int pos = binarySearch(arr, 0, i - 1, key);

        // Shift all elements from position to the right to make space for the key
        for (int j = i - 1; j >= pos; --j) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = key;
    }
}

// Exercise05: Comparing standard Insertion Sort and Binary Insertion Sort
void Exercise05() {
    vector<int> sizes = { 100, 1000, 10000 };  // Different array sizes to test

    for (int size : sizes) {
        cout << "\nTesting with size: " << size << "\n";

        // Create a random list for sorting
        auto originalList = generateRandomList(size);

        // --- Standard Insertion Sort ---
        auto standardInsertionSortCopy = originalList;
        measureTime(insertionSort<int>, standardInsertionSortCopy, "Standard Insertion Sort");

        // --- Binary Insertion Sort ---
        auto binaryInsertionSortCopy = originalList;
        measureTime(binaryInsertionSort<int>, binaryInsertionSortCopy, "Binary Insertion Sort");

        cout << endl;
    }
}


// Heapify function to maintain the Max-Heap property
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root, swap and heapify the affected subtree
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest); // Recursively heapify the affected subtree
    }
}

// Function to build a Max-Heap
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
}

// Function to find the maximum value without fully sorting
int heapSortMaxValue(vector<int>& arr) {
    int n = arr.size();

    // Build the Max-Heap
    buildMaxHeap(arr);

    // The root of the Max-Heap is the maximum value
    return arr[0];  // Return the maximum value from the root of the Max-Heap
}

// Exercise06: Find maximum using Heap Sort
void Exercise06() {
    vector<int> sizes = { 100, 1000, 10000 };  // Different array sizes to test

    for (int size : sizes) {
        cout << "\nTesting with size: " << size << "\n";

        // Create a random list for sorting
        auto originalList = generateRandomList(size);

        // --- Finding maximum value using Heap Sort ---
        measureTime(heapSortMaxValue, originalList, "Heap Sort to find maximum");
    }
}

// Insertion Sort for small arrays
void insertionSort2(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Merge function to merge two halves of the array
void merge2(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Copy any remaining elements of L[] or R[]
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort2(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeSort2(arr, left, mid);
        mergeSort2(arr, mid + 1, right);

        // Merge the sorted halves
        merge2(arr, left, mid, right);
    }
}


// Hybrid Sort function
void hybridSort(vector<int>& arr, int left, int right, int threshold = 10) {
    if (right - left + 1 <= threshold) {
        // Use Insertion Sort for small arrays
        insertionSort2(arr, left, right);
    }
    else {
        // Use Merge Sort for large arrays
        mergeSort2(arr, left, right);
    }
}

// Helper function to measure execution time
template <typename Func, typename Container>
void measureTime2(Func func, Container& container, const string& sortName) {
    auto start = chrono::high_resolution_clock::now();
    func(container);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " took " << duration.count() << " seconds.\n";
}


// Exercise07: Compare performance of Hybrid Sort with Merge Sort
void Exercise07() {
    vector<int> sizes = { 10, 100, 1000, 10000 };  // Different array sizes to test

    for (int size : sizes) {
        cout << "\nTesting with size: " << size << "\n";

        // Create a random list for sorting
        auto originalList = generateRandomList(size);

        // --- Comparing Hybrid Sort with Merge Sort ---
        vector<int> mergeSortList = originalList; // Copy for Merge Sort
        measureTime2(mergeSort2, mergeSortList, "Merge Sort");

        vector<int> hybridSortList = originalList; // Copy for Hybrid Sort
        measureTime2(hybridSort, hybridSortList, "Hybrid Sort");
    }
}

// Hybrid Sort: Uses Quick Sort for large datasets and Insertion Sort for small subarrays
template <typename T>
void hybridSort(vector<T>& arr, int low, int high) {
    if (high - low + 1 <= 10) { // Use Insertion Sort for small subarrays
        insertionSort(arr, low, high);
    }
    else { // Use Quick Sort for large subarrays
        int pi = partition(arr, low, high);
        hybridSort(arr, low, pi - 1);
        hybridSort(arr, pi + 1, high);
    }
}

// Exercise 08: Compare performance of Hybrid Sort with Quick Sort
void Exercise08() {
    vector<int> sizes = { 10, 100, 1000, 10000 };  // Different array sizes to test

    for (int size : sizes) {
        cout << "\nTesting with size: " << size << "\n";

        // Create a random list for sorting
        auto originalList = generateRandomList(size);

        // --- Comparing Hybrid Sort with Quick Sort ---
        vector<int> quickSortList = originalList; // Copy for Quick Sort
        measureTime(quickSort, quickSortList, "Quick Sort");

        vector<int> hybridSortList = originalList; // Copy for Hybrid Sort
        measureTime(hybridSort, hybridSortList, "Hybrid Sort");
    }
}

// Point structure to represent 2D points
struct Point {
    int x;
    int y;

    // Constructor to initialize point
    Point(int x_val, int y_val) : x(x_val), y(y_val) {}

    // Function to calculate distance from origin
    double distanceFromOrigin() const {
        return sqrt(x * x + y * y);
    }
};

// Insertion Sort for small subarrays
template <typename T>
void insertionSort(vector<T>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j].distanceFromOrigin() > key.distanceFromOrigin()) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Generate a random list of Points
vector<Point> generateRandomPoints(int size) {
    vector<Point> points;
    for (int i = 0; i < size; i++) {
        int x = rand() % 1000; // Random x coordinate
        int y = rand() % 1000; // Random y coordinate
        points.push_back(Point(x, y));
    }
    return points;
}

// Exercise 09: Compare performance of Hybrid Sort with Quick Sort for sorting 2D points
void Exercise09() {
    vector<int> sizes = { 10, 100, 1000, 10000 };  // Different array sizes to test

    for (int size : sizes) {
        cout << "\nTesting with size: " << size << "\n";

        // Create a random list of points
        auto originalList = generateRandomPoints(size);

        // --- Comparing Hybrid Sort with Quick Sort ---
        vector<Point> quickSortList = originalList; // Copy for Quick Sort
        measureTime(quickSort, quickSortList, "Quick Sort");

        vector<Point> hybridSortList = originalList; // Copy for Hybrid Sort
        measureTime(hybridSort, hybridSortList, "Hybrid Sort");
    }
}

int main() {
    // Test Exercise03 with different data types
    //Exercise03<int>();
    Exercise01();

    return 0;
}


