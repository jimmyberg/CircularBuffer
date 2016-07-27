#include <iostream>
#include "CircularBuffer.hpp"

using namespace std;

int main(int argc, char** argv){
	CircularBuffer<float, 4> test;
	test.set(5.2);
	test.set(5.3);
	test.set(5.4);
	test.set(5.5);
	test.set(5.6);
	cout << test.get() << ", ";
	cout << test.get() << ", ";
	cout << test.get() << ", ";
	cout << test.get() << ", ";
	cout << test.get() << endl;
	return 0;
}
