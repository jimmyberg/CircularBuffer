
#ifndef _CIRCULARBUFFER_HPP_
#define _CIRCULARBUFFER_HPP_

//#define DEBUG_CIRCULARBUFFER

#ifdef DEBUG_CIRCULARBUFFER
#include <iostream>
using namespace std;
#endif //DEBUG_CIRCULARBUFFER

#include <cstddef>

/**
 * @brief      Class for FIFO type circular buffer.
 *
 * @note       Tip: This buffer has almost the same behavior as read and writing
 *             a file.
 *
 * @tparam     T     Type of data to store in buffer
 * @tparam     size  Size of buffer
 */
template<typename T, size_t sizeBuffer>
class CircularBuffer{
public:
	/**
	 * @brief      Get one number from the buffer
	 *
	 * @param      data  Pointer where the data will be stored
	 *
	 * @return     Number of numbers stored. Max 1.
	 */
	size_t get(T* data);
	/**
	 * @brief      Gets up to size number of numbers from the buffer.
	 *
	 * @param      data  Pointer to the array where the numbers will be stored.
	 * @param[in]  size  The size of the buffer. May also be smaller to limit the number of bytes retrieved.
	 *
	 * @return     Number of numbers stored. Zero indicates an empty buffer.
	 */
	size_t get(T* data, size_t size);
	/**
	 * @brief      Stores one number in the buffer.
	 *
	 * @param[in]  newVal  Pointer to the new value to be stored.
	 *
	 * @return     Number of numbers retrieved from buffer.(1 or 0 when full)
	 */
	size_t set(const T* newVal);
	/**
	 * @brief      Stores up to size numbers in the buffer.
	 *
	 * @note       This function will never store more numbers that available in
	 *             buffer.
	 *
	 * @param[in]  data  Pointer to then numbers to be stored.
	 * @param[in]  size  The size
	 *
	 * @return     Number of numbers actually stored. Smaller that size
	 *             indicates a full buffer.
	 */
	size_t set(const T* data, size_t size);
	/**
	 * @brief      Gets how many numbers are stored in the buffer.
	 *
	 * @return     Amount of numbers stored.
	 */
	unsigned int getStored();
	/**
	 * @brief      Gets free places in buffer.
	 *
	 * @return     Free space.
	 */
	unsigned int getFree();
	/**
	 * @brief      Determines if full.
	 *
	 * @return     True if full, False otherwise.
	 */
	bool isFull(){
		return ((setIndex + 1) % sizeBuffer == getIndex);
	}
	/**
	 * @brief      Determines if empty.
	 *
	 * @return     True if empty, False otherwise.
	 */
	bool isEmpty(){
		return (setIndex == getIndex);
	}
private:
	T dataArray[sizeBuffer];
	unsigned int getIndex = 0;
	unsigned int setIndex = 0;
	unsigned int storedData = 0;
};

template<typename T, size_t sizeBuffer>
size_t CircularBuffer<T, sizeBuffer>::get(T* data){
	if(storedData != 0){
		#ifdef DEBUG_CIRCULARBUFFER
		cout << "CircularBuffer get " << dataArray[getIndex] << " at index " << getIndex << endl;
		#endif //DEBUG_CIRCULARBUFFER
		*data = dataArray[getIndex = (getIndex + 1) % sizeBuffer];
		storedData--;
		return 1;
	}
	else{
		#ifdef DEBUG_CIRCULARBUFFER
		cerr << "Error. CircularBuffer is empty." << endl << "available = " << available << endl << "size = " << size << endl;
		#endif //DEBUG_CIRCULARBUFFER
		return 0;
	}
}
template<typename T, size_t sizeBuffer>
size_t CircularBuffer<T, sizeBuffer>::get(T* data, size_t size){
	// Adjust size. Size will be the amount of data that will be retrieved.
	if(size > storedData){
		size = storedData;
	}
	for (unsigned int i = 0; i < size; ++i){
		data[i] = dataArray[getIndex = (getIndex + 1) % sizeBuffer];
	}
	storedData -= size;
	return size;
}

template<typename T, size_t sizeBuffer>
size_t CircularBuffer<T, sizeBuffer>::set(const T* data){
	if(getFree() != 0){
		#ifdef DEBUG_CIRCULARBUFFER
		cout << "CircularBuffer set " << *data << " at index " << setIndex << endl;
		#endif //DEBUG_CIRCULARBUFFER
		dataArray[setIndex = (setIndex + 1) % sizeBuffer] = *data;
		storedData++;
		return 1;
	}
	else{
		#ifdef DEBUG_CIRCULARBUFFER
		cerr << "Error. CircularBuffer is full." << endl << "available = " << available << endl << "size = " << size << endl;
		#endif //DEBUG_CIRCULARBUFFER
		return 0;
	}	
}

template<typename T, size_t sizeBuffer>
size_t CircularBuffer<T, sizeBuffer>::set(const T* data, size_t size){
	unsigned int currentFree = getFree();
	if(size > currentFree){
		size = currentFree;
	}
	for (unsigned int i = 0; i < size; ++i){
		dataArray[setIndex = (setIndex + 1) % sizeBuffer] = dataArray[i];
	}
	storedData += size;
	return size;
}

template<typename T, size_t sizeBuffer>
unsigned int CircularBuffer<T, sizeBuffer>::getStored(){ 
	return storedData;
}

template<typename T, size_t sizeBuffer>
unsigned int CircularBuffer<T, sizeBuffer>::getFree(){ 
	return sizeBuffer - storedData;
}

#endif //_CIRCULARBUFFER_HPP_
