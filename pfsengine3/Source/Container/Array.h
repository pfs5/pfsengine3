#pragma once
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Math/Math.h"
#include "Misc/PFSEngineString.h"
// ----------------------------------------------------------------------------
#define INDEX_NONE -1
// ----------------------------------------------------------------------------
typedef unsigned int psize;
// ----------------------------------------------------------------------------
template <typename T>
class PArray
{
public:
	typedef T*			PArrayIterator;
	typedef const T*	PConsArrayIterator;

public:
	PArray();
	PArray(const std::initializer_list<T>& elements);
	PArray(psize size);
	PArray(const PArray<T>& other);
	~PArray();

	void Add(const T& element);
	
	/**
	 * Remove element by value, if exists. Move last item in array in place of removed element.
	 * Return true on success, false otherwise.
	 */
	bool RemoveSwap(const T& element);

	/**
	 * Remove element at given index, if valid. Move last item in array in place of removed element.
	 * Return true on success, false otherwise.
	 */
	bool RemoveAtSwap(psize index);

	/**
	 * Remove element by value, if exists. Move all elements by one step.
	 * Return true on success, false otherwise.
	 */
	bool Remove(const T& element);

	/**
	 * Remove element at given index, if valid. Move all elements by one step.
	 * Return true on success, false otherwise.
	 */
	bool RemoveAt(psize index);

	/**
	 * Removes all elements from array and initializes with capacity.
	 */
	void Clear(psize slack = 0);

	/**
	 * Find element in array by value and return index if success.
	 * Return INDEX_NONE if not exists.
	 */
	psize Find(const T& element);

	/**
	 * Check is given index is valid for this array.
	 */
	bool IsValidIndex(psize index) const;

	/**
	 * Reserve size in memory.
	 */
	void Reserve(psize size) const;
	
	/**
	 * Get element at index. Throw std::out_of_range exception if invalid index.
	 */
	const T& At(psize index) const;
		  T& At(psize index);

	/**
	 * Unchecked version of At. Doesn't check for index validity.
	 */
	const T& AtUnchecked(psize index) const;
		  T& AtUnchecked(psize index);

	/**
	 * Get size of array.
	 */
	psize Size() const;

	/**
	 * Constructs string representing the array.
	 */
	PString ToString() const;

// Iterator interface
public:
	PArrayIterator begin() const	{ 
		return _elements; 
	}
	PArrayIterator end() const		{ 
		return _elements + _size; 
	}

public:
	const T& operator[] (psize idx) const	{ return At(idx); }
		  T& operator[] (psize idx)			{ return At(idx); }

	PArray<T> operator=(const PArray<T>& other);

private:
	mutable T* _elements;
	mutable psize _capacity;

	psize _size;

private:
	/**
	 * Copy from other array to this one.
	 */
	void CopyOther(const PArray<T>& other);

	/**
	 * Initialize empty of size.
	 */
	void InitEmpty(psize size) const;

	/**
	 * Increase reserved memory and move current memory to new location.
	 */
	bool IncreaseReservedMemory(psize newSize) const;

	/**
	 * Clear all elements and memory.
	 */
	void ClearInternal();

	psize GetNewCapacity() const;
};
// ----------------------------------------------------------------------------
template <typename T>
PArray<T>::PArray():
	_elements(nullptr),
	_size(0u),
	_capacity(0u)
{

}
// ----------------------------------------------------------------------------
template <typename T>
PArray<T>::PArray(const std::initializer_list<T>& elements)
{
	Reserve((psize)elements.size());

	for (psize i = 0; i < elements.size(); ++i)
	{
		AtUnchecked(i) = *(elements.begin() + i);
	}

	_size = (psize)elements.size();
}
// ----------------------------------------------------------------------------
template <typename T>
PArray<T>::PArray(psize size):
	_size(size)
{
	InitEmpty(size);
}
// ----------------------------------------------------------------------------
template <typename T>
PArray<T>::PArray(const PArray<T>& other):
	_size(0u),
	_capacity(0u),
	_elements(nullptr)
{
	CopyOther(other);
}
// ----------------------------------------------------------------------------
template <typename T>
PArray<T>::~PArray()
{
	ClearInternal();
}
// ----------------------------------------------------------------------------
template <typename T>
void PArray<T>::Add(const T& element)
{
	if (_size >= _capacity)
	{
		if (!IncreaseReservedMemory(GetNewCapacity()))
		{
			return;
		}
	}

	T* newElement = new(_elements + _size) T(element);
	if (newElement != nullptr)
	{
		_size++;
	}
}
// ----------------------------------------------------------------------------
template <typename T>
bool PArray<T>::RemoveSwap(const T& element)
{
	return RemoveAtSwap(Find(element));
}
// ----------------------------------------------------------------------------
template <typename T>
bool PArray<T>::RemoveAtSwap(psize index)
{
	if (!IsValidIndex(index))
	{
		return false;
	}

	(_elements + index)->~T();
	std::memcpy(_elements + index, _elements + _size - 1, sizeof(T));

	_size--;

	return true;
}
// ----------------------------------------------------------------------------
template <typename T>
bool PArray<T>::Remove(const T& element)
{
	return RemoveAt(Find(element));
}
// ----------------------------------------------------------------------------
template <typename T>
bool PArray<T>::RemoveAt(psize index)
{
	if (!IsValidIndex(index))
	{
		return false;
	}

	(_elements + index)->~T();

	std::memcpy(_elements + index, _elements + index + 1, sizeof(T) * (_size - index - 1));

	_size--;

	return true;
}
// ----------------------------------------------------------------------------
template <typename T>
void PArray<T>::Clear(psize slack/* = 0*/)
{
	ClearInternal();

	_capacity = 0u;
	_size = 0u;

	Reserve(slack);
}
// ----------------------------------------------------------------------------
template <typename T>
psize PArray<T>::Find(const T& element)
{
	for (psize i = 0; i < Size(); ++i)
	{
		if (At(i) == element)
		{
			return i;
		}
	}

	return INDEX_NONE;
}
// ----------------------------------------------------------------------------
template <typename T>
bool PArray<T>::IsValidIndex(psize index) const
{
	return index < _size;
}
// ----------------------------------------------------------------------------
template <typename T>
void PArray<T>::Reserve(psize size) const
{
	if (size <= 0u)
	{
		return;
	}

	IncreaseReservedMemory(size);
}
// ----------------------------------------------------------------------------
template <typename T>
PArray<T> PArray<T>::operator=(const PArray<T>& other)
{
	ClearInternal();
	_size = 0u;
	_capacity = 0u;

	CopyOther(other);
}
// ----------------------------------------------------------------------------
template <typename T>
void PArray<T>::CopyOther(const PArray<T>& other)
{
	Reserve(other.Size());
	for (const T& e : other)
	{
		Add(e);
	}
}
// ----------------------------------------------------------------------------
template <typename T>
void PArray<T>::InitEmpty(psize size) const
{
	Reserve(size);
	new(_elements) T[size];
}
// ----------------------------------------------------------------------------
template <typename T>
bool PArray<T>::IncreaseReservedMemory(psize newSize) const
{
	if (newSize <= _capacity)
	{
		return false;
	}

	T* newBlock = (T*)std::malloc(sizeof(T) * newSize);

	if (_size > 0)
	{
		// Move to new memory block
		std::memcpy(newBlock, _elements, sizeof(T) * _size);
		std::free(_elements);
	}

	_elements = newBlock;

	_capacity = newSize;

	return true;
}
// ----------------------------------------------------------------------------
template <typename T>
const T& PArray<T>::At(psize index) const
{
	if (!IsValidIndex(index))
	{
		throw std::out_of_range("PArray index out of range.");
	}

	return AtUnchecked(index);
}
// ----------------------------------------------------------------------------
template <typename T>
T& PArray<T>::At(psize index)
{
	if (!IsValidIndex(index))
	{
		throw std::out_of_range("PArray index out of range.");
	}

	return AtUnchecked(index);
}
// ----------------------------------------------------------------------------
template <typename T>
const T& PArray<T>::AtUnchecked(psize index) const
{
	return *(_elements + index);
}
// ----------------------------------------------------------------------------
template <typename T>
T& PArray<T>::AtUnchecked(psize index)
{
	return *(_elements + index);
}
// ----------------------------------------------------------------------------
template <typename T>
psize PArray<T>::Size() const
{
	return _size;
}
// ----------------------------------------------------------------------------
template <typename T>
PString PArray<T>::ToString() const
{
	std::stringstream sstream;
	for (psize i = 0; i < Size(); ++i)
	{
		sstream << At(i);
		if (i != Size() - 1)
		{
			sstream << " ";
		}
	}

	return PString(sstream.str());
}
// ----------------------------------------------------------------------------
template <typename T>
psize PArray<T>::GetNewCapacity() const
{
	//return _capacity + 1u;
	return PMath::Max(_capacity * 2u, 1u);
}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template <typename T>
void PArray<T>::ClearInternal()
{
	for (psize i = 0; i < Size(); ++i)
	{
		At(i).~T();
	}

	std::free(_elements);
	_elements = nullptr;
}
// ----------------------------------------------------------------------------