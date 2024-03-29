#include "String.cpp"

template <class T>
class SmarterArray
{
private:
	T* A; //The dynamic array to store the elements
	int size; //The number of elements in the array

public:
	//Constructors
	SmarterArray(); 
	SmarterArray(const SmarterArray<T>&); //Copy constructor. Deep copy of the argument

	//Assignment operator
	SmarterArray<T>& operator = (const SmarterArray<T>&); //Memory cleanup and deep copy of the argument

	//Destructor
	~SmarterArray(); 

	//Getters, Setters, operators and other functions
	int getSize() const; //Return the number of elements in the container
	T& operator[](const int&) const; //Assert index and then return the element at the given index
	int find(const T&) const; //Return the index of the first element that is == to the argument. 
								//Return -1 if not found.
	void insert(const int& index, const T&); //Assert index >= 0 && index <= size and then insert the T
										//type argument into the calling object at the index. If index is
										//equal to size, then insert as a last element
	void append(const T&);  //Insert T as a last element
	bool remove(const int&); //If the index is valid, then remove the element at the index argument

	bool operator == (const SmarterArray<T>&) const; //Return true if sizes are equal and elements at the
														//same indexes are equal. Otherwise return false

	template <class T1> 
	friend ostream& operator << (ostream&, const SmarterArray<T1>&); 
};
template <class T>
SmarterArray<T>::SmarterArray()
{
	this->A = nullptr;
	this->size = 0;
}
template <class T>
SmarterArray<T>::~SmarterArray()
{
	if (this->getSize() > 0)
	{
		delete[] this->A;
		A = nullptr;
		this->size = 0;
	}
}
template <class T>
ostream& operator << (ostream& out, const SmarterArray<T>& L)
{
	if (L.getSize() == 0)
		out << "[Empty List]";
	else
	{
		cout << endl;
		for (int i = 0; i < L.getSize() - 1; i++)
			out << L[i] << endl;
		out << L[L.getSize() - 1] << endl;
	}
	return out;
}



template <class T>
SmarterArray<T>::SmarterArray(const SmarterArray<T>& L) {
	this->size = L.getSize();
	if (this->getSize() > 0)
	{
		this->A = new T[this->getSize()];
		for (int i = 0; i < this->getSize(); i++)
		{
			this->A[i] = L[i];
		}
	}
}

template <class T>
SmarterArray<T>& SmarterArray<T>::operator = (const SmarterArray<T>& L) {
	this->size = L.getSize();
	if (this->getSize() > 0)
	{
		this->A = new T[this->getSize()];
		for (int i = 0; i < this->getSize(); i++)
		{
			this->A[i] = L[i];
		}
	}
	return *this;
}

template <class T>
int SmarterArray<T>::getSize() const {
	return this->size;
}

template <class T>
T& SmarterArray<T>::operator[](const int& index) const {
	assert(index >= 0 && index <= this->getSize());
	return this->A[index];

}

template <class T>
int SmarterArray<T>::find(const T& e) const {
	for (int i = 0; i < this->getSize(); i++) {
		if (this->A[i] == e) {
			return i;
		}
	}
	return -1;
}

template <class T>
void SmarterArray<T>::append(const T& e) {
	T* temp = new T[this->getSize() + 1];
	for (int i = 0; i < this->getSize(); i++) {
		temp[i] = this->A[i];
	}
	temp[this->getSize()] = e;
	if (this->getSize() > 0) {
		delete[] this->A;
	}
	this->A = temp;
	this->size += 1;
}

template <class T>
void SmarterArray<T>::insert(const int& index, const T& e) {
	assert(index >= 0 && index <= this->getSize());
	T* temp = new T[this->getSize() + 1];
	for (int i = 0; i < index; i++) {
		temp[i] = this->A[i];
	}
	temp[index] = e;
	for (int i = index + 1; i < this->getSize() + 1; i++) {
		temp[i] = this->A[i - 1];
	}
	if (this->getSize() > 0) {
		delete[] this->A;
	}
	this->A = temp;
	this->size += 1;
}


template <class T>
bool SmarterArray<T>::remove(const int& index) {
	if (index >= 0 && index <= this->getSize()) {
		T* temp = new T[this->getSize() - 1];
		for (int i = 0; i < index; i++) {
			temp[i] = A[i];
		}
		for (int i = index + 1; i < this->getSize(); i++) {
			temp[i - 1] = A[i];
		}
		if (this->getSize() > 0) {
			delete[] this->A;
		}

		this->A = temp;
		this->size--;
		return true;
	}
	return false;
}

template <class T>
bool SmarterArray<T>::operator == (const SmarterArray<T>& L) const {
	if (this->getSize() == L.getSize()) {
		for (int i = 0; i < this->getSize(); i++) {
			if (this->A[i] != L[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}