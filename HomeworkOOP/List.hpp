/*
* @author Alexander Asenov
* @idnumber 2MI0600422
* @compiler VCC
*/
#pragma once
#include <stdexcept>
#include <fstream>
#include "Role.h"

class SystemEmail;

template <typename T>
class List {
public:
	List();
	List(const T* items, size_t length);
	List(const List<T>& other);
	List(List<T>&& other) noexcept;
	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);
	~List();

	bool contains(const T& item) const;
	int indexOf(const T& item) const;

	template<typename CallableType>
	int indexOf(CallableType func) const;

	template<typename CallableType>
	T& FirstOrDefault(CallableType func);

	template<typename CallableType>
	const T& FirstOrDefault(CallableType func) const;

	void add(const T& item);
	void removeAt(size_t index);
	void remove(const T& item);
	void clear();
	size_t getLength() const;
	
	template <typename U>
	friend std::ofstream& operator<<(std::ofstream& stream, const List<U>& list);

	template <typename U>
	friend std::ifstream& operator>>(std::ifstream& stream, List<U>& list);

	bool operator==(const List<T>& other) const;
	bool operator!=(const List<T>& other) const;
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
private:
	static double resizeFactor;
	static size_t defaultStartCapacity;
	T* content;
	size_t length;
	size_t capacity;

	void copyFrom(const List<T>& other);
	void free();
	void resizeUp();
	void resizeDown();
};

template<class T>
double List<T>::resizeFactor = 1.5;

template<class T>
size_t List<T>::defaultStartCapacity = 8;

template<class T>
inline List<T>::List() : length(0), capacity(defaultStartCapacity) {
	this->content = new T[this->capacity];
}

template<class T>
inline List<T>::List(const T* items, size_t length) : length(0), capacity(defaultStartCapacity) {
	this->content = new T[this->capacity];

	for (size_t i = 0; i < length; i++) {
		this->add(items[i]);
	}
}

template<class T>
inline List<T>::List(const List<T>& other) {
	copyFrom(other);
}

template<class T>
inline List<T>::List(List<T>&& other) noexcept {
	this->length = other.length;
	this->capacity = other.capacity;
	this->content = other.content;
	other.content = nullptr;
	other.length = 0;
	other.capacity = 0;
}

template<class T>
inline List<T>& List<T>::operator=(const List<T>& other) {
	if (this != &other) {
		this->free();
		this->copyFrom(other);
	}

	return *this;
}

template<class T>
inline List<T>& List<T>::operator=(List<T>&& other) {
	if (this != &other) {
		this->free();
		this->length = other.length;
		this->capacity = other.capacity;
		this->content = other.content;
		other.content = nullptr;
		other.length = 0;
		other.capacity = 0;
	}

	return *this;
}

template<class T>
inline List<T>::~List() {
	this->free();
}

template<class T>
inline bool List<T>::contains(const T& item) const {
	if (this->indexOf(item) == -1) {
		return false;
	}

	return true;
}

template<class T>
inline int List<T>::indexOf(const T& item) const {
	for (int i = 0; i < this->length; i++) {
		if (item == this->content[i]) {
			return i;
		}
	}

	return -1;
}

template<class T>
inline void List<T>::add(const T& item) {
	if (this->length == this->capacity) {
		this->resizeUp();
	}

	this->content[this->length] = item;
	this->length++;
}

template<class T>
inline void List<T>::removeAt(size_t index) {
	if (index >= length) {
		throw std::out_of_range("Index out of range");
	}
	
	for (size_t i = index; i < this->length - 1; i++) {
		this->content[i] = this->content[i + 1];
	}
	this->length--;

	if (static_cast<size_t>(this->capacity / this->resizeFactor) > this->length) {
		resizeDown();
	}
}

template<class T>
inline void List<T>::remove(const T& item) {
	int index = this->indexOf(item);
	if (index == -1) {
		return;
	}

	this->removeAt(index);
}

template<class T>
inline void List<T>::clear() {
	delete[] this->content;
	this->capacity = List<T>::defaultStartCapacity;
	this->length = 0;
	this->content = new T[this->capacity];
}

template<class T>
inline size_t List<T>::getLength() const {
	return this->length;
}

template<typename T>
inline std::ofstream& operator<<(std::ofstream& stream, const List<T>& list) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.write(reinterpret_cast<const char*>(&list.length), sizeof(size_t));
	stream.write(reinterpret_cast<const char*>(&list.capacity), sizeof(size_t));
	for (size_t i = 0; i < list.length; i++) {
		stream << list.content[i];
	}

	return stream;
}

template<>
inline std::ofstream& operator<<(std::ofstream& stream, const List<size_t>& list) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.write(reinterpret_cast<const char*>(&list.length), sizeof(size_t));
	stream.write(reinterpret_cast<const char*>(&list.capacity), sizeof(size_t));
	for (size_t i = 0; i < list.length; i++) {
		stream.write(reinterpret_cast<const char*>(&list.content[i]), sizeof(size_t));
	}

	return stream;
}

template<>
inline std::ofstream& operator<<(std::ofstream& stream, const List<Role>& list) {
	if (!stream.is_open()) {
		return stream;
	}

	stream.write(reinterpret_cast<const char*>(&list.length), sizeof(size_t));
	stream.write(reinterpret_cast<const char*>(&list.capacity), sizeof(size_t));
	for (size_t i = 0; i < list.length; i++) {
		stream.write(reinterpret_cast<const char*>(&list.content[i]), sizeof(Role));
	}

	return stream;
}

template<typename T>
inline std::ifstream& operator>>(std::ifstream& stream, List<T>& list) {
	if (!stream.is_open()) {
		return stream;
	}

	list.free();

	stream.read(reinterpret_cast<char*>(&list.length), sizeof(size_t));
	stream.read(reinterpret_cast<char*>(&list.capacity), sizeof(size_t));
	list.content = new T[list.capacity];
	for (size_t i = 0; i < list.length; i++) {
		stream >> list.content[i];
	}

	return stream;
}

template<>
inline std::ifstream& operator>>(std::ifstream& stream, List<size_t>& list) {
	if (!stream.is_open()) {
		return stream;
	}
	list.free();
	stream.read(reinterpret_cast<char*>(&list.length), sizeof(size_t));
	stream.read(reinterpret_cast<char*>(&list.capacity), sizeof(size_t));
	list.content = new size_t[list.capacity];
	for (size_t i = 0; i < list.length; i++) {
		stream.read(reinterpret_cast<char*>(&list.content[i]), sizeof(size_t));
	}

	return stream;
}

template<>
inline std::ifstream& operator>>(std::ifstream& stream, List<Role>& list) {
	if (!stream.is_open()) {
		return stream;
	}
	list.free();
	stream.read(reinterpret_cast<char*>(&list.length), sizeof(size_t));
	stream.read(reinterpret_cast<char*>(&list.capacity), sizeof(size_t));
	list.content = new Role[list.capacity];
	for (size_t i = 0; i < list.length; i++) {
		stream.read(reinterpret_cast<char*>(&list.content[i]), sizeof(Role));
	}

	return stream;
}

template<class T>
inline bool List<T>::operator==(const List<T>& other) const {
	if (this == &other) {
		return true;
	}

	if (this->length != other.length) {
		return false;
	}

	for (size_t i = 0; i < this->length; i++) {
		if (this->content[i] != other.content[i]) {
			return false;
		}
	}

	return true;
}

template<class T>
inline bool List<T>::operator!=(const List<T>& other) const {
	return !(*this == other);
}

template<class T>
inline const T& List<T>::operator[](size_t index) const {
	if (index >= length) {
		throw std::out_of_range("Index out of range");
	}

	return this->content[index];
}

template<class T>
inline T& List<T>::operator[](size_t index) {
	if (index >= length) {
		throw std::out_of_range("Index out of range");
	}

	return this->content[index];
}

template<class T>
inline void List<T>::copyFrom(const List<T>& other) {
	this->length = other.length;
	this->capacity = other.capacity;
	this->content = new T[this->capacity];
	for (size_t i = 0; i < this->length; i++) {
		this->content[i] = other.content[i];
	}
}

template<class T>
inline void List<T>::free() {
	delete[] this->content;
	this->content = nullptr;
	this->length = 0;
	this->capacity = 0;
}

template<class T>
inline void List<T>::resizeUp() {
	this->capacity = static_cast<size_t>(this->capacity * resizeFactor);
	T* newContent = new T[this->capacity];

	for (size_t i = 0; i < this->length; i++) {
		newContent[i] = this->content[i];
	}

	delete[] this->content;
	this->content = newContent;
}

template<class T>
inline void List<T>::resizeDown() {
	this->capacity = static_cast<size_t>(this->capacity / resizeFactor);
	T* newContent = new T[this->capacity];

	for (size_t i = 0; i < this->length; i++) {
		newContent[i] = this->content[i];
	}

	delete[] this->content;
	this->content = newContent;
}

template<class T>
template<typename CallableType>
inline int List<T>::indexOf(CallableType func) const {
	for (int i = 0; i < length; i++) {
		if (func(this->content[i])) {
			return i;
		}
	}

	return -1;
}

template<class T>
template<typename CallableType>
inline T& List<T>::FirstOrDefault(CallableType func) {
	for (size_t i = 0; i < length; i++) {
		if (func(this->content[i])) {
			return this->content[i];
		}
	}

	return this->content[0];
}

template<class T>
template<typename CallableType>
inline const T& List<T>::FirstOrDefault(CallableType func) const {
	for (size_t i = 0; i < length; i++) {
		if (func(this->content[i])) {
			return this->content[i];
		}
	}

	if (this->length == 0) {
		throw std::out_of_range("No elements");
	}

	return this->content[0];
}
