#include "vector.h"
#include <iostream>
#include <cassert>

int main() {
	
	Vector<int> array;
	std::cout << "array: ";
	for (int i = 0; i < 1024; ++i) {
		array.push_back(i);
		std::cout << array[i] << ' ';
	}
	std::cout << "\n";

	Vector<int> other;
	std::cout << "other: ";
	for (int i = 0; i < 1023; ++i) {
		other.push_back(i);
		std::cout << other[i] << ' ';
	}
	std::cout << "\n";

	//test1_operator[]
	assert(array[3] == 3);
	if (array[3] == 3) {
		std::cout << "'operator[]' has passed the test1: array[3] = 3" << "\n";
	}
	else {
		std::cout << "'operator[]' hasn't pass the test1" << "\n";
	}
	//test1_array.front()
	assert(array.front() == 0);
	if (array.front() == 0) {
		std::cout << "'array.front()' has passed the test1: array.front() = 0" << "\n";
	}
	else {
		std::cout << "'array.front()' hasn't pass the test1" << "\n";
	}
	//test1_array.back()
	assert(array.back() == 1023);
	if (array.back() == 1023) {
		std::cout << "'array.back()' has passed the test1: array.back() = 1023" << "\n";
	}
	else {
		std::cout << "'array.back()' hasn't pass the test1" << "\n";
	}
	//test1_array.empty()
	assert(array.empty() == false);
	if (array.empty() == false) {
		std::cout << "'array.empty()' has passed the test1: array.empty() not empty" << "\n";
	}
	else {
		std::cout << "'array.empty()' hasn't pass the test1" << "\n";
	}
	//test1_array.size()
	assert(array.size() == 1024);
	if (array.size() == 1024) {
		std::cout << "'array.size()' has passed the test1: array.size() = 1024" << "\n";
	}
	else {
		std::cout << "'array.size()' hasn't pass the test1" << "\n";
	}
	//test1_array.max_size()
	assert(array.size() == 1024);
	if (array.max_size() == 1024) {
		std::cout << "'array.max_size()' has passed the test1: array.max_size() = 1023" << "\n";
	}
	else {
		std::cout << "'array.max_size()' hasn't pass the test1" << "\n";
	}
	//test1_array.capacity()
	assert(array.size() == 1024);
	if (array.capacity() == 1024) {
		std::cout << "'array.capacity()' has passed the test1: array.capacity() = 1023" << "\n";
	}
	else {
		std::cout << "'array.capacity()' hasn't pass the test1" << "\n";
	}
	//test1_operator==
	bool ret = (array == other);
	assert(ret == false);
	if (!ret) { 
		std::cout << "'operator==' has passed the test1" << "\n"; 
	}
	else {
		std::cout << "'operator==' hasn't pass the test1" << "\n";
	}
	//test1_array.erase()
	array.erase(6);
	assert(array[6] == 7);
	if (array[6] == 7) {
		std::cout << "'array.erase(6)' has passed the test1" << "\n";
	}
	else {
		std::cout << "'array.erase()' hasn't pass the test1" << "\n";
	}
	std::cout << "array: ";
	for (int i = 0; i < array.size(); ++i) {
		std::cout << array[i] << ' ';
	}
	std::cout << "\n";

	//test1_array.insert()
	array.insert(6, 6);
	assert(array[6] == 6);
	if (array[6] == 6) {
		std::cout << "'array.insert(6, 6)' has passed the test1: array[6] = 6" << "\n";
	}
	else {
		std::cout << "'array.capacity()' hasn't pass the test1" << "\n";
	}
	std::cout << "array: ";
	for (int i = 0; i < array.size(); ++i) {
		std::cout << array[i] << ' ';
	}
	std::cout << "\n";

	//test1_array.push_back()
	array.push_back(1024);
	assert(array[1024] == 1024);
	if (array[1024] == 1024) {
		std::cout << "'array.push_back(1024)' has passed the test1: array[1024] = 1024" << "\n";
	}
	else {
		std::cout << "'array.push_back()' hasn't pass the test1" << "\n";
	}

	//test1_array.pop_back()
	array.pop_back();
	assert(array.size() == 1024 );
	if (array.size() == 1024 && array.back() == 1023) {
		std::cout << "'array.pop_back()' has passed the test1: array.size() = 1024 and array.back() == 1023" << "\n";
	}
	else {
		std::cout << "'array.pop_back()' hasn't pass the test1" << "\n";
	}

	//test1_array.swap()
	array.swap(other);
	assert(array.size() == 1023 && other.size() == 1024);
	if (array.size() == 1023 && other.size() == 1024) {
		std::cout << "'array.swap(other)' has passed the test1: array.size() = 1023 and other.size() == 1024" << "\n";
	}
	else {
		std::cout << "'array.swap()' hasn't pass the test1" << "\n";
	}

	//test1_array.pop_back()
	array.clear();
	assert(array.empty());
	if (array.empty()) {
		std::cout << "'array.clear()' has passed the test1" << "\n";
	}
	else {
		std::cout << "'array.clear()' hasn't pass the test1" << "\n";
	}


	return 0;
}



