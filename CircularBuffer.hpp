
#ifndef _CIRCULARBUFFER_HPP_
#define _CIRCULARBUFFER_HPP_

//#define DEBUG_CIRCULARBUFFER

#ifdef DEBUG_CIRCULARBUFFER
#include <iostream>
using namespace std;
#endif //DEBUG_CIRCULARBUFFER


template<typename T, int size>
class CircularBuffer{
public:
	T get();
	void set(T newVal);
private:
	T data[size];
	int getPointer = 0;
	int setPointer = 0;
	int available = 0;
};

template<typename T, int size>
T CircularBuffer<T, size>::get(){
	if(available > 0){
		available--;
		T ret = data[getPointer];
		#ifdef DEBUG_CIRCULARBUFFER
		cout << "CircularBuffer get " << ret << " at index " << getPointer << endl;
		#endif //DEBUG_CIRCULARBUFFER
		getPointer = (getPointer+1) % size;
		return ret;
	}
	else{
		#ifdef DEBUG_CIRCULARBUFFER
		cerr << "Error. CircularBuffer is empty." << endl << "available = " << available << endl << "size = " << size << endl;
		#endif //DEBUG_CIRCULARBUFFER
		return 0;
	}
}

template<typename T, int size>
void CircularBuffer<T, size>::set(T newVal){
	if(available < size){
		available++;
		data[setPointer] = newVal;
		#ifdef DEBUG_CIRCULARBUFFER
		cout << "CircularBuffer set " << newVal << " at index " << setPointer << endl;
		#endif //DEBUG_CIRCULARBUFFER
		setPointer = (setPointer+1) % size;
	}
	#ifdef DEBUG_CIRCULARBUFFER
	else{
		cerr << "Error. CircularBuffer is full." << endl << "available = " << available << endl << "size = " << size << endl;
	}
	#endif //DEBUG_CIRCULARBUFFER
}

#endif //_CIRCULARBUFFER_HPP_
