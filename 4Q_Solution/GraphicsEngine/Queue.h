#pragma once

template<typename T>
class Queue
{
public:
	Queue();
	~Queue();

public:
	void push(const T& value);
	void pop();
	T& front();
	bool empty();

private:
	T* _array{ nullptr };
	unsigned int _front{ 0 };
	unsigned int _real{ 0 };
	unsigned int _size{ 0 };
	unsigned int _capacity{ 0 };
};

template<typename T>
inline Queue<T>::Queue()
{
	_array = new T[32]{};
	_capacity = 32;
}

template<typename T>
inline Queue<T>::~Queue()
{
	delete[] _array;
}

template<typename T>
inline void Queue<T>::push(const T& value)
{
	assert(_array);

	if (_capacity < _size)
	{
		unsigned int newSize = _capacity * 2;
		T* temp = new T[newSize]{};
		memcpy(temp, _array, _capacity);
		delete[] _array;
		_array = temp;
		_capacity = newSize;
	}

	_array[_real] = value;
	_real = (_real + 1) % _capacity;
	_size++;
}

template<typename T>
inline void Queue<T>::pop()
{
	assert(_array);
	assert(_size);
	assert(_real == _front);

	_front = (_front + 1) % _capacity;
	_size--;
}

template<typename T>
inline T& Queue<T>::front()
{
	assert(_array);
	return _array[_front];
}

template<typename T>
inline bool Queue<T>::empty()
{
	assert(_array);
	return 0 == _size;
}
