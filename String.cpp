#include <iostream>
#include <fstream>
#include <cassert>
#include <ctime>
#include <iomanip>
using namespace std;

class String
{
private:
	char* buffer; //The dynamic array to store the printable characters and a null terminating character 
public:
	String(); //The buffer is initialized to nullptr value
	String(const char*); //A non-default constructor with a null terminated char array argument
	String(const String&); //Deep copy constructor
	~String();  //Delete any heap memory and assign buffer nullptr value
	String& operator = (const String&); //Memory cleanup and deep copy assignment
	int length() const; //Return the number of printable characters. Return zero if buffer is nullptr
	bool empty() const;  //Return true if length is 0. Otherwise return false
	char& operator [] (const int&) const;  //Assert index and then return the char at the index
	String operator + (const char&) const; //Return *this appended with the argument character
	String& operator += (const char&); //Append the character argument to *this and return it
	bool operator == (const String&) const; //Case sensitive equality comparison
	bool operator != (const String&) const; //Case sensitive not equality comparison
	friend istream& operator >> (istream&, String&); 
	friend ostream& operator << (ostream&, const String&); 
};
istream& operator >> (istream& in, String& s)
{

#define SPACE ' '
#define TAB '\t'
#define	EOL	'\n'

//Delete the old value of s
	s.~String();

	//Skip leading spaces, tabs, and empty lines
	char ch;
	while (!in.eof())
	{
		in.get(ch);
		if (ch == SPACE || ch == TAB || ch == EOL)
			continue;
		break;
	}

	if (in.eof())
		return in;

	//Append ch to s
	if (ch != SPACE && ch != TAB && ch != EOL)
		s += ch;

	//Read characters into s until a TAB or EOL or EOF is reached
	while (!in.eof())
	{
		in.get(ch);
		if (ch == TAB || ch == EOL || in.eof())
			break;
		else
			s += ch;
	}

	//Remove trailing spaces if any
	int trailingSpacesCount = 0;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		if (s[i] != SPACE)
			break;
		trailingSpacesCount++;
	}
	if (trailingSpacesCount > 0)
	{
		String temp;
		for (int i = 0; i < s.length() - trailingSpacesCount; i++)
			temp += s[i];
		s = temp;
	}

	return in;
}
ostream& operator << (ostream& out, const String& s)
{
	for (int i = 0; i < s.length(); i++)
		out << s[i];
	return out;
}

String::String() {
	buffer = nullptr;
}

String::String(const char* cStr) {
	int size = 0;
	if (cStr != nullptr) {
		while (cStr[size] != '\0') {
			size++;
		}
	}
	this->buffer = new char[size + 1];
	for (int i = 0; i < size; i++) {
		this->buffer[i] = cStr[i];
	}
	this->buffer[size] = '\0';
}

int String::length() const {
	if (buffer == nullptr) {
		return 0;
	}
	else {
		int count = 0;
		while (buffer[count] != '\0') {
			count++;
		}
		return count;
	}
}

String::String(const String& s) {
	this->buffer = new char[s.length() + 1];
	for (int i = 0; i < s.length(); i++) {
		this->buffer[i] = s[i];
	}
	this->buffer[s.length()] = '\0';
}

String::~String() {
	if (this->buffer != nullptr) {
		delete[] buffer;
		buffer = nullptr;
	}
}

String& String::operator = (const String& s) {
	if (s == *this) {
		return *this;
	}
	else {
		if (this->length() > 0) {
			delete[] this->buffer;
		}
	}
	this->buffer = new char[s.length() + 1];
	for (int i = 0; i < s.length(); i++) {
		this->buffer[i] = s[i];
	}
	this->buffer[s.length()] = '\0';
	return *this;
}

bool String::empty() const {
	return(this->length() == 0);
}

char& String::operator[](const int& index) const {
	assert(index < this->length() && index >= 0);
	return buffer[index];
}

String String::operator+(const char& c) const {
	char* newArr = new char[this->length() + 2];
	for (int i = 0; i < this->length(); i++) {
		newArr[i] = this->buffer[i];
	}
	newArr[this->length()] = c;
	newArr[this->length() + 1] = '\0';
	String output(newArr);
	return output;
}

String& String::operator += (const char& c) {
	char* newArr = new char[this->length() + 2];
	for (int i = 0; i < this->length(); i++) {
		newArr[i] = this->buffer[i];
	}
	newArr[this->length()] = c;
	newArr[this->length() + 1] = '\0';
	this->buffer = newArr;
	return *this;
}

bool String::operator == (const String& s) const {
	int count = 0;
	if (s.length() == this->length()) {
		for (int i = 0; i < this->length(); i++) {
			if (s[i] == buffer[i]) {
				count++;
			}
		}
	}
	return count == this->length();
}

bool String::operator != (const String& s) const {
	int count = 0;
	if (s.length() == this->length()) {
		for (int i = 0; i < this->length(); i++) {
			if (s[i] == buffer[i]) {
				count++;
			}
		}
	}
	return count != this->length();
}



