#pragma once
// ----------------------------------------------------------------------------
template <class T>
class PUniquePtr
{
public:
	PUniquePtr() = default;
	PUniquePtr(T* rawPtr);
	~PUniquePtr();

	/**
	 * Transferring ownership from other pointer to this.
	 */
	PUniquePtr<T>& operator= (const PUniquePtr<T>& other);

	T* operator->() const;

	/**
	 * Clears the internal pointer, sets to new value and deletes memory.
	 */
	void Reset(T* newRawPtr = nullptr);

	/**
	 * Clears the internal pointer and sets to new value WITHOUT deleting the memory.
	 */
	void Clear(T* newRawPtr = nullptr);

	/**
	 * Checks if pointed to resource is valid.
	 */
	bool IsValid() const;

private:
	T* _rawPtr;
	
};
// ----------------------------------------------------------------------------
template <class T>
PUniquePtr<T>& PUniquePtr<T>::operator=(const PUniquePtr<T>& other)
{
	Reset(other._rawPtr);
	other.Clear();
}
// ----------------------------------------------------------------------------
template <class T>
T* PUniquePtr<T>::operator->() const
{
	return _rawPtr;
}
// ----------------------------------------------------------------------------
template <class T>
PUniquePtr<T>::PUniquePtr(T* rawPtr):
	_rawPtr(rawPtr)
{

}
// ----------------------------------------------------------------------------
template <class T>
PUniquePtr<T>::~PUniquePtr()
{
	delete _rawPtr;
}
// ----------------------------------------------------------------------------
template <class T>
void PUniquePtr<T>::Reset(T* newRawPtr/* = nullptr*/)
{
	delete _rawPtr;
	_rawPtr = newRawPtr;
}
// ----------------------------------------------------------------------------
template <class T>
void PUniquePtr<T>::Clear(T* newRawPtr/* = nullptr*/)
{
	_rawPtr = newRawPtr;
}
// ----------------------------------------------------------------------------
template <class T>
bool PUniquePtr<T>::IsValid() const
{
	return _rawPtr == nullptr;
}
// ----------------------------------------------------------------------------