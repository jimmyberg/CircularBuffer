
#ifndef _CIRCULARBUFFER_HPP_
#define _CIRCULARBUFFER_HPP_

#define DEBUG_CIRCULARBUFFER

#ifdef DEBUG_CIRCULARBUFFER
#include <iostream>
using namespace std;
#endif //DEBUG_CIRCULARBUFFER

#include <stddef.h>

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
	size_t set(T newVal);
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
	 * @brief      Determines if full.
	 *
	 * @return     True if full, False otherwise.
	 */
	bool isFull(){
		return nextSetP() == getP;
	}
	/**
	 * @brief      Determines if empty.
	 *
	 * @return     True if empty, False otherwise.
	 */
	bool isEmpty(){
		return (setP == getP);
	}
	/**
	 * @brief      Clears all data in buffer.
	 *
	 *             This is done by moving the getP and mark available bytes
	 *             to zero.
	 */
	void clear(){
		setP = getP;
	}
private:
	T* end(){return &dataArray[sizeBuffer];}
	T* begin(){return dataArray;}
	T* nextSetP(){
		T* ret = setP + 1;
		if(ret == end())
			return begin();
		else
			return ret;
	}
	T* nextGetP(){
		T* ret = getP + 1;
		if(ret == end())
			return begin();
		else
			return ret;
	}
	T dataArray[sizeBuffer];
	T* getP = dataArray;
	T* setP = dataArray;
};

template<typename T, size_t sizeBuffer>
size_t CircularBuffer<T, sizeBuffer>::get(T* data){
	if(!isEmpty()){
		#ifdef DEBUG_CIRCULARBUFFER
		cout << "CircularBuffer get " << *getP << " at index " << getP << endl;
		#endif //DEBUG_CIRCULARBUFFER
		*data = *getP;
		getP = nextGetP();
		return 1;
	}
	else{
		#ifdef DEBUG_CIRCULARBUFFER
		cerr << "Error. CircularBuffer is empty." << endl;
		#endif //DEBUG_CIRCULARBUFFER
		return 0;
	}
}
template<typename T, size_t sizeBuffer>
size_t CircularBuffer<T, sizeBuffer>::get(T* data, size_t size){
	// Adjust size. Size will be the amount of data that will be retrieved.
	size_t ret = 0;
	while(!isEmpty() && size != ret++){
		*data++ = *getP;
		getP = nextGetP();
	}
	return ret;
}

template<typename T, size_t sizeBuffer>
size_t CircularBuffer<T, sizeBuffer>::set(T data){
	T* nextSet = nextSetP();
	if(nextSet != getP){
		#ifdef DEBUG_CIRCULARBUFFER
		cout << "CircularBuffer set " << data << " at index " << setP << endl;
		#endif //DEBUG_CIRCULARBUFFER
		*setP = data;
		setP = nextSet;
		return 1;
	}
	else{
		#ifdef DEBUG_CIRCULARBUFFER
		cerr << "Error. CircularBuffer is full." << endl;
		#endif //DEBUG_CIRCULARBUFFER
		return 0;
	}
}

template<typename T, size_t sizeBuffer>
size_t CircularBuffer<T, sizeBuffer>::set(const T* data, size_t size){
	size_t ret = 0;
	T* nextSet;
	while((nextSet = nextSetP()) != getP && size != ret++){
		*setP = *data++;
		setP = nextSet;
	}
	return size;
}

#endif //_CIRCULARBUFFER_HPP_
