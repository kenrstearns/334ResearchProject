/**
* @file main.cpp
* @brief Contains all of the code
*/
/*
CSCI 334 Research Project
Kenneth Stearns

This project is designed to test out various sorting algorithms
utilizing an external text document for a source of numbers.
The tested sorting algorithms are listed in the following order:
Insertion Sort
Bubble Sort
Merge Sort
Heap Sort
Radix Sort
Selection Sort
TimSort
Pigeonhole Sort
Bitronic Sort
Comb Sort

These were tested by using the chrono and the ctime
libraries to track the time and seed a random number
generator, as well as an integer that is passed to each
function in a sort that is incremented everytime an operation
is performed in the process of the sort.
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int RUN = 32;  // Integer required for the timSort algorithm declared globally

//! \brief Insertion Sort
//! This function will sort an integer array by use of an insertion sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Incrementor
//! \return Sorted Array
//!
//!

void insertionSort(int arr[], int n, int& counter)
{
    int i, key, j;                      //Initalize variables needed
    for(i = 1; i < n; i++){             //Start Loop
        key = arr[i];                   //Assign current array spot to external variable
        j = i - 1;                      //Assign one looping variable to first variable

        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];          //Swap adjacent locations
            j = j - 1;                  //Move j to next spot
            counter++;                  //Increment operation counter
        }
        arr[j + 1] = key;               //Assign next array spot to original value
        counter++;                      //Increment operation counter
    }
}

//! \brief Bubble Sort
//! This function will sort an integer array by use of an bubble sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Incrementor
//! \return Sorted Array
//!
//!
void bubbleSort(int arr[], int n, int& counter)
{
    int i, j;                               //Declare variables needed
    bool swapped;
    for(i = 0; i < n - 1; i++){
        swapped = false;
        for(j = 0; j < n - 1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
            counter++;
        }


        if(swapped == false)
            break;
    }
}

//! \brief Merge function
//! This function will sort an array via merging
//! \param Integer Array
//! \param Left end of array
//! \param Middle of array
//! \param Right end of array
//! \param Incrementor
//! \return Sorted Array
//!
//!
void merge(int arr[], int left, int mid, int right, int& counter)
{
    int subArrOne = mid - left + 1;                             //Calculation for size of left array
    int subArrTwo = right - mid;                                //Calculation for size of right array

    int *leftArray = new int[subArrOne],                        //Declaring new arrays
        *rightArray = new int[subArrTwo];

    for(int i = 0; i < subArrOne; i++)                          //Filling in new arrays
        leftArray[i] = arr[left + i];
    for(int j = 0; j < subArrTwo; j++)
        rightArray[j] = arr[mid + 1 + j];

    int indexOne = 0, indexTwo = 0;                             //Declaring inital indexes
    int indexOverall = left;

    while(indexOne < subArrOne && indexTwo < subArrTwo){        //Looping till one index surpasses the length of the array
        if (leftArray[indexOne] <= rightArray[indexTwo]){       //Assigning inital array to the lower value of the two arrays.
            arr[indexOverall] = leftArray[indexOne];
            indexOne++;
            counter++;
        }
        else{
            arr[indexOverall] = rightArray[indexTwo];
            indexTwo++;
            counter++;
        }
    }

    while(indexOne < subArrOne){
        arr[indexOverall] = leftArray[indexOne];
        indexOne++;
        indexOverall++;
        counter++;
    }

    while(indexTwo < subArrTwo){
        arr[indexOverall] = rightArray[indexTwo];
        indexTwo++;
        indexOverall++;
        counter++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

//! \brief Merge Sort
//! This function will send the information to the merge function
//! \param Integer Array
//! \param Left end of array
//! \param Right end of array
//! \param Incrementor
//! \return Sorted Array
//!
//!
void mergeSort(int arr[], int begin, int end, int& counter){
    if(begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid, counter);
    mergeSort(arr, mid + 1, end, counter);
    merge(arr, begin, mid, end, counter);
}

//! \brief Heapify
//! This function will be the guts of the Heap sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Integer that is being heaped
//! \param Incrementor
//! \return Heaping the values in an array.
//!
//!
void heapify(int arr[], int N, int i, int& counter){
    int largest = i;

    int l = 2 * i + 1;

    int r = 2 * i + 2;

    if(l < N && arr[l] > arr[largest]){
        largest = l;
        counter++;
    }

    if(r < N && arr[r] > arr[largest]){
        largest = r;
        counter++;
    }

    if(largest != i){
        swap(arr[i], arr[largest]);
        counter++;
        heapify(arr, N, largest, counter);
    }
}

//! \brief Heap Sort
//! This function will sort an integer array by use of an Heap sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Incrementor
//! \return Sorted Array
//!
//!
void heapSort(int arr[], int N, int& counter){
    for(int i = N / 2 - 1; i >= 0; i--){
        heapify(arr, N, i, counter);
    }

    for(int i = N - 1; i > 0; i--){
        swap(arr[0], arr[i]);
        counter++;
        heapify(arr, i, 0, counter);
    }
}

//! \brief getMax
//! This function will find the max integer in an array
//! \param Integer Array
//! \param Size of Integer Array
//! \param Incrementor
//! \return Integer of max value
//!
//!
int getMax(int arr[], int n, int& counter){
    int mx = arr[0];
    for(int i = 1; i< n; i++){
        if(arr[i] > mx)
            mx = arr[i];
        counter++;
    }
    return mx;
}

//! \brief Count Sort
//! This function will sort an integer array by use of a count sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Integer for exponent
//! \param Incrementor
//! \return Sorted Array
//!
//!
void countSort(int arr[], int n, int exp, int& counter){
    int output[n];
    int i, count[10] = {0};

    for(i = 0; i < n; i++){
        count[(arr[i] / exp) % 10]++;
        counter++;
    }

    for(i = 1; i < 10; i++){
        count[i] += count[i - 1];
        counter++;
    }

    for(i = n - 1; i >= 0; i--){
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        counter++;
    }

    for(i = 0; i < n; i++){
        arr[i] = output[i];
        counter++;
    }
}

//! \brief Radix Sort
//! This function will sort an integer array by use of a Radix sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Incrementor
//! \return Sorted Array
//!
//!
void radixSort(int arr[], int n, int& counter){
    int m = getMax(arr, n, counter);

    for(int exp = 1; m / exp > 0; exp *= 10){
        countSort(arr, n, exp, counter);
        counter++;
    }
}

//! \brief Selection Sort
//! This function will sort an integer array by use of a Selection sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Incrementor
//! \return Sorted Array
//!
//!
void selectionSort(int arr[], int n, int& counter){
    int i, j, min_idx;

    for(i = 0; i < n - 1; i++){
        min_idx = i;
        for(j = i + 1; j < n; j++){
            if(arr[j] < arr[min_idx]){
                min_idx = j;
            }
            counter++;
        }

        if(min_idx != i){
            swap(arr[min_idx], arr[i]);
        }
        counter++;
    }
}

//! \brief Insert Tim Sort
//! This function will sort an array via insertion for the Tim Sort function.
//! \param Integer Array
//! \param Integer for left end
//! \param Integer for right end
//! \param Incrementor
//! \return Sorted Array
//!
//!
void insertTimSort(int arr[], int left, int right, int& counter){
    for(int i = left + 1; i <= right; i++){
        int temp = arr[i];;
        int j = i - 1;
        while(j >= left && arr[j] > temp){
            arr[j + 1] = arr[j];
            j--;
            counter++;
        }
        arr[j + 1] = temp;
        counter++;
    }
}

//! \brief Merge Tim Sort
//! This function will sort an array via merging for the Tim Sort function.
//! \param Integer Array
//! \param Left integer
//! \param Middle Integer
//! \param Right Integer
//! \param Incrementor
//! \return Sorted Array
//!
//!
void mergeTim(int arr[], int l, int m, int r, int& counter){
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for(int i = 0; i < len1; i++){
        left[i] = arr[l + 1];
        counter++;
    }
    for(int i = 0; i < len2; i++){
        right[i] = arr[m + 1 + i];
        counter++;
    }

    int i = 0;
    int j = 0;
    int k = l;

    while(i < len1 && j < len2){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
        counter++;
    }

    while(i < len1){
        arr[k] = left[i];
        k++;
        i++;
        counter++;
    }

    while(j < len2){
        arr[k] = right[j];
        k++;
        j++;
        counter++;
    }
}

//! \brief Tim Sort
//! This function will sort an integer array by use of a Tim Sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Incrementor
//! \return Sorted Array
//!
//!
void timSort(int arr[], int n, int& counter){
    for(int i = 0; i < n; i += RUN){
        insertTimSort(arr, i, min((i + RUN - 1), (n - 1)), counter);
        counter++;
    }

    for(int size = RUN; size < n; size = 2 * size) {
        for(int left = 0; left < n; left += 2 * size){
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1),(n - 1));

            if(mid < right)
                mergeTim(arr, left, mid, right, counter);
            counter++;
        }
    }
}

//! \brief Pigeonhole Sort
//! This function will sort an integer array by use of a Pigeonhole sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Incrementor
//! \return Sorted Array
//!
//!
void pigeonHoleSort(int arr[], int n, int& counter){
    int min = arr[0], max = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] < min)
            min = arr[i];
        if(arr[i] > max)
            max = arr[i];
        counter++;
    }

    int range = max - min + 1;

    vector<int> holes[range];

    for(int i = 0; i < n; i++){
        holes[arr[i] - min].push_back(arr[i]);
        counter++;
    }

    int index = 0;
    for(int i = 0; i < range; i++){
        vector<int>::iterator it;
        for(it = holes[i].begin(); it != holes[i].end(); ++it){
            arr[index++] = *it;
            counter++;
        }
        counter++;
    }
}

//! \brief CompAndSwap
//! This function will compare two integers and swap if necessary
//! \param Integer Array
//! \param Integer for first comparison
//! \param Integer for second comparison
//! \param Direction sort is going
//! \param Incrementor
//! \return Swapped values in array if applicable
//!
//!
void compAndSwap(int arr[], int i, int j, int dir, int& counter){
    if(dir==(arr[i]>arr[j]))
        swap(arr[i],arr[j]);
    counter++;
}

//! \brief Bitronic Merge
//! This function will merge two arrays as needed for the Bitronic Sort
//! \param Integer Array
//! \param Left end of array
//! \param Middle of array
//! \param Direction integer
//! \param Incrementor
//! \return Merged arrays
//!
//!
void bitronicMerge(int arr[], int low, int mid, int dir, int& counter){
    if(mid > 1)
    {
        int k = mid / 2;
        for(int i = low; i < low + k; i++){
            compAndSwap(arr, i, i + k, dir, counter);
        }
        bitronicMerge(arr, low, k, dir, counter);
        bitronicMerge(arr, low + k, k, dir, counter);
        counter++;
    }
}

//! \brief Bitronic Sort
//! This function will sort an integer array by use of a Bitronic Sort
//! \param Integer Array
//! \param left end integer
//! \param Middle integer
//! \param direction integer
//! \param Incrementor
//! \return Sorted Array
//!
//!
void bitronicSort(int arr[], int low, int mid, int dir, int& counter){
    if(mid > 1)
    {
        int k = mid / 2;
        bitronicSort(arr, low, k, 1, counter);
        counter++;

        bitronicSort(arr, low + k, k, 0, counter);
        counter++;

        bitronicMerge(arr, low, mid, dir, counter);
        counter++;
    }
}

//! \brief Bit Sort
//! This function calls on the bitronic sort function to add in the applicable values
//! \param Integer Array
//! \param Size of Integer Array
//! \param Up integer
//! \param Incrementor
//! \return Sorted Array
//!
//!
void bitSort(int arr[], int N, int up, int& counter){
    bitronicSort(arr, 0, N, up, counter);
}

//! \brief getNextGap
//! This function will get the next gap as required for the comb sort
//! \param Integer for previous gap
//! \param Incrementor
//! \return Integer for new gap
//!
//!
int getNextGap(int gap, int& counter){
    gap = (gap*10)/13;
    counter ++;

    if(gap < 1)
        return 1;
    return gap;
}

//! \brief Comb Sort
//! This function will sort an integer array by use of an Comb sort
//! \param Integer Array
//! \param Size of Integer Array
//! \param Incrementor
//! \return Sorted Array
//!
//!
void combSort(int arr[], int n, int& counter){
    int gap = n;

    bool swapped = true;

    while(gap != 1 || swapped == true){
        gap = getNextGap(gap, counter);
        swapped = false;

        for(int i = 0; i < n - gap; i++){
            if(arr[i] > arr[i + gap]){
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
            counter++;
        }
    }
}

int main() {
    //opening file containing numbers
    ifstream input ("random_numbers.txt");

    //error checking for if file does not open
    if(!input){
        cout << "Error opening file" << endl;
        return 1;
    }

    //declaring integers used in program
    // e used for the size of the array
    int e = 10000;
    int numbers[e];
    int reset[e];
    int number_size = sizeof(numbers) / sizeof(numbers[0]);
    int num;
    int i = 0;
    int up = 1;

    // using input file to initalize the first array
    while (input >> num) {
        reset[i] = num;
        i++;
    }

    // closing input stream
    input.close();

    // declaring menu integer and tracking integer for operations
    int track;
    int choice;

    // menu for UI
    cout << "Sorting Options: " << endl;
    cout << "1: Insertion Sort" << endl;
    cout << "2: Bubble Sort" << endl;
    cout << "3: Merge Sort" << endl;
    cout << "4: Heap Sort" << endl;
    cout << "5: Radix Sort" << endl;
    cout << "6: Selection Sort" << endl;
    cout << "7 TimSort" << endl;
    cout << "8: Pigeonhole Sort" << endl;
    cout << "9: Bitronic Sort" << endl;
    cout << "10: Comb Sort" << endl;
    cout << "Enter option: ";
    cin >> choice;
    while(choice < 1 || choice > 10){
        cout << "Invalid. Please choose a different option: ";
        cin >> choice;
    }

    while(choice >= 1 && choice <= 10){

        for(int p = 0; p < number_size; p++){
            numbers[p] = reset[p];
        }
        track = 0;
        switch(choice)
        {
            case 1:
            {
                auto start = high_resolution_clock::now();
                insertionSort(numbers, number_size, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Insertion sort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
            case 2:
            {
                auto start = high_resolution_clock::now();
                bubbleSort(numbers, number_size, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Bubble Sort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
            case 3:
            {
                auto start = high_resolution_clock::now();
                mergeSort(numbers, 0, number_size - 1, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Merge Sort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
            case 4:
            {
                auto start = high_resolution_clock::now();
                heapSort(numbers, number_size, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Heap Sort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
            case 5:
            {
                auto start = high_resolution_clock::now();
                radixSort(numbers, number_size, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Radix Sort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
            case 6:
            {
                auto start = high_resolution_clock::now();
                selectionSort(numbers, number_size, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Selection Sort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
            case 7:
            {
                auto start = high_resolution_clock::now();
                timSort(numbers, number_size, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "TimSort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
            case 8:
            {
                auto start = high_resolution_clock::now();
                pigeonHoleSort(numbers, number_size, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Pigeonhole Sort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
            case 9:
            {
                auto start = high_resolution_clock::now();
                bitSort(numbers, number_size, up, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Bitronic Sort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
            case 10:
            {
                auto start = high_resolution_clock::now();
                combSort(numbers, number_size, track);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Comb Sort has " << track << " number of operations in " << duration.count() << " microseconds." << endl;
                break;
            }
        }
        cout << "Enter another option (number not listed to exit): ";
        cin >> choice;

    }
    return 0;
}
