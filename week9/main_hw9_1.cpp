/*
 * Title: main_hw9_1.cpp
 * Abstract: Test the execution time for the insertion sort, merge sort, and quick
 * 			 sort algorithms for ascending, descending, or random lists of integers.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 04/15/2022
 */

#include <iostream>
#include <ctime>
#include <vector>
#include <deque>
#include <cmath>
#include <cstdio>
#include <chrono>
#include <random>
#include <set>

using namespace std::chrono;

namespace impl {
	/**
	 * @brief Conduct the merge operation from the merge sort algorithm.
	 * @source https://www.geeksforgeeks.org/merge-sort/?ref=gcse
	 * @param array The list to sort.
	 * @param left The left index.
	 * @param mid The middle index.
	 * @param right The right index.
	 */
	void merge(std::vector<int32_t>& array, uint32_t left, uint32_t mid, uint32_t right) {
		uint32_t subArrayOne = mid - left + 1;
		uint32_t subArrayTwo = right - mid;
		
		std::vector<int32_t> leftArray(subArrayOne), rightArray(subArrayTwo);
		
		for (uint32_t i = 0; i < subArrayOne; i++) leftArray[i] = array[left + i];
		for (uint32_t i = 0; i < subArrayTwo; i++) rightArray[i] = array[mid + i + 1];
		
		uint32_t indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
		uint32_t indexOfMergedArray = left;
		
		while (indexOfSubArrayOne < subArrayOne and indexOfSubArrayTwo < subArrayTwo) {
			array[indexOfMergedArray++] = leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo] ?
				leftArray[indexOfSubArrayOne++] : rightArray[indexOfSubArrayTwo++];
		}
		
		while (indexOfSubArrayOne < subArrayOne) array[indexOfMergedArray++] = leftArray[indexOfSubArrayOne++];
		while (indexOfSubArrayTwo < subArrayTwo) array[indexOfMergedArray++] = rightArray[indexOfSubArrayTwo++];
	}
} // namespace impl

/**
 * @brief Conduct the insertion sort algorithm.
 * @source https://www.geeksforgeeks.org/insertion-sort/?ref=gcse
 * @param vector the list to sort.
 */
void insertionSort(std::vector<int32_t> vector);

/**
 * @brief Conduct the merge sort algorithm.
 * @source https://www.geeksforgeeks.org/merge-sort/?ref=gcse
 * @param array The vector to sort.
 * @param begin The beginning index.
 * @param end The last index.
 */
void mergeSort(std::vector<int32_t>& array, uint32_t begin, uint32_t end);

/**
 * @brief Partition a C-style array.
 * @source https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
 * @param arr A C-style array to be partitioned.
 * @param low The left side pointer.
 * @param high The right side pointer.
 * @return The partition index.
 */
uint32_t partition(int* arr, uint32_t low, uint32_t high);

/**
 * @brief Partition a C-style array using a random pivot.
 * @source https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
 * @param arr A C-style array to be partitioned.
 * @param low The left side pointer.
 * @param high The right side pointer.
 * @return The partition index.
 */
uint32_t randomPartition(int *arr, uint32_t low, uint32_t high);

/**
 * @brief Conducts the quick sort algorithm.
 * @source https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
 * @param arr A C-style array to be sorted.
 * @param low The left side pointer.
 * @param high The right side pointer.
 */
void quickSort(int* arr, int32_t low, int32_t high);

int main() {
	uint64_t inputSize;
	uint32_t option;

	printf("Enter input size: ");
	std::cin >> inputSize;
	printf("========== Select Option for Input Numbers ==========\n");
	printf("\t1. Ascending Order\n");
	printf("\t2. Descending Order\n");
	printf("\t3. Random Order\n");
	printf("Choose option: ");
	std::cin >> option;

	std::vector<int32_t> vectorA(inputSize), vectorB(inputSize), vectorC(inputSize);
	if (option == 1) {
		int32_t i = 0;
		for (int32_t &x : vectorA) x = i++;
	}
	else if (option == 2) {
		int32_t i = static_cast<int32_t>(inputSize) - 1;
		for (int32_t &x : vectorA) x = i--;
	}
	else if (option == 3) {
		std::default_random_engine generator(std::random_device{}());
		std::uniform_int_distribution<int32_t> distribution(
			1, std::numeric_limits<int32_t>::max()
		);

		for (int32_t &x : vectorA) x = distribution(generator);
		for (int32_t &x : vectorB) x = distribution(generator);
		for (int32_t &x : vectorC) x = distribution(generator);
	}
	else {
		printf("Invalid option\n");
		return -1;
	}
	
	time_point<steady_clock, duration<double>> start, end;
	std::set<std::string> times;
	
	{
		printf("========================== 1st Run =========================\n");
		start = high_resolution_clock::now();
//		insertionSort(vectorA);
		end = high_resolution_clock::now();
		duration<double> a = end - start;
		printf("Insertion sort: %f milliseconds\n", a.count());
		
		std::vector<int32_t> mSortCopy(vectorA);
		start = std::chrono::high_resolution_clock::now();
		mergeSort(mSortCopy, 0, mSortCopy.size());
		end = std::chrono::high_resolution_clock::now();
		duration<double> b = end - start;
		printf("Merge sort:     %f milliseconds\n", b.count());
		
		int* qSortCopy = new int[vectorA.size()];
		std::copy(vectorA.begin(), vectorA.end(), qSortCopy);
		start = std::chrono::high_resolution_clock::now();
		quickSort(qSortCopy, 0, static_cast<int>(vectorA.size()) - 1);
		end = std::chrono::high_resolution_clock::now();
		duration<double> c = end - start;
		printf("Quick sort:     %f milliseconds\n", c.count());
		printf("============================================================\n");
		
		if (a.count() <= b.count()) {
			times.insert(a.count() <= c.count()? "Insertion Sort" : "Quick Sort");
		} else {
			times.insert(b.count() <= c.count()? "Merge Sort" : "Quick Sort");
		}
	}
	{
		if (option != 3) {
			vectorB = vectorA;
		}
		
		printf("========================== 2nd Run =========================\n");
		start = high_resolution_clock::now();
//		insertionSort(vectorB);
		end = high_resolution_clock::now();
		duration<double> a = end - start;
		printf("Insertion sort: %f milliseconds\n", a.count());
		
		std::vector<int32_t> mSortCopy(vectorB);
		start = std::chrono::high_resolution_clock::now();
		mergeSort(mSortCopy, 0, mSortCopy.size());
		end = std::chrono::high_resolution_clock::now();
		duration<double> b = end - start;
		printf("Merge sort:     %f milliseconds\n", b.count());
		
		int* qSortCopy = new int[vectorB.size()];
		std::copy(vectorB.begin(), vectorB.end(), qSortCopy);
		start = std::chrono::high_resolution_clock::now();
		quickSort(qSortCopy, 0, static_cast<int>(vectorB.size()) - 1);
		end = std::chrono::high_resolution_clock::now();
		duration<double> c = end - start;
		printf("Quick sort:     %f milliseconds\n", c.count());
		printf("============================================================\n");
		
		if (a.count() <= b.count()) {
			times.insert(a.count() <= c.count()? "Insertion Sort" : "Quick Sort");
		} else {
			times.insert(b.count() <= c.count()? "Merge Sort" : "Quick Sort");
		}
	}
	{
		if (option != 3) {
			vectorC = vectorA;
		}
		
		printf("========================== 3rd Run =========================\n");
		start = high_resolution_clock::now();
//		insertionSort(vectorC);
		end = high_resolution_clock::now();
		duration<double> a = end - start;
		printf("Insertion sort: %f milliseconds\n", a.count());
		
		std::vector<int32_t> mSortCopy(vectorC);
		start = std::chrono::high_resolution_clock::now();
		mergeSort(mSortCopy, 0, mSortCopy.size());
		end = std::chrono::high_resolution_clock::now();
		duration<double> b = end - start;
		printf("Merge sort:     %f milliseconds\n", b.count());
		
		int* qSortCopy = new int[vectorC.size()];
		std::copy(vectorC.begin(), vectorC.end(), qSortCopy);
		start = std::chrono::high_resolution_clock::now();
		quickSort(qSortCopy, 0, static_cast<int>(vectorC.size()) - 1);
		end = std::chrono::high_resolution_clock::now();
		duration<double> c = end - start;
		printf("Quick sort:     %f milliseconds\n", c.count());
		printf("============================================================\n");
		
		if (a.count() <= b.count()) {
			times.insert(a.count() <= c.count()? "Insertion Sort" : "Quick Sort");
		} else {
			times.insert(b.count() <= c.count()? "Merge Sort" : "Quick Sort");
		}
	}
	
	printf("========================== Ranking =========================\n");
	int32_t rank = 1;
	for (std::string const& s : times) {
		printf("(%d) %s\n", rank++, s.c_str());
	}
	printf("============================================================\n");
	
	return 0;
}

void insertionSort(std::vector<int32_t> vector) {
	uint64_t j;
	int32_t key;
	
	for (uint64_t i = 1; i < vector.size(); i++) {
		key = vector[i];
		j = i - 1;
		
		while (j >= 0 && vector[j] > key) {
			vector[j + 1] = vector[j];
			j = j - 1;
		}
		vector[j + 1] = key;
	}
}

void mergeSort(std::vector<int32_t>& array, uint32_t begin, uint32_t end) {
	if (begin >= end)
		return;
	
	uint32_t mid = begin + (end - begin) / 2;
	
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	impl::merge(array, begin, mid, end);
}

void quickSort(int* arr, int32_t low, int32_t high) {
	if (low < high) {
		auto pi = static_cast<int32_t>(randomPartition(arr, low, high));
		
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

uint32_t randomPartition(int *arr, uint32_t low, uint32_t high) {
	srand(time(nullptr));
	uint32_t random = low + rand() % (high - low);
	std::swap(arr[random], arr[high]);
	
	return partition(arr, low, high);
}

uint32_t partition(int* arr, uint32_t low, uint32_t high) {
	int32_t pivot = arr[high];
	uint32_t i = low - 1;
	
	for (uint32_t j = low; j <= high - 1; j++) {
		if (arr[j] <= pivot) {
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	
	std::swap(arr[i + 1], arr[high]);
	return i + 1;
}
