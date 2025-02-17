#include "String.hpp"

String::String() : str_(nullptr), capacity_(0) {}


String::String(int size) {
	capacity_ = size;
	str_ = allocator_.allocate(size);
	str_[size] = '\0';
}


String::String(const char* str) {
	int size = static_cast<int>(strlen(str));

	capacity_ = size;
	str_ = allocator_.allocate(size);
	str_[size] = '\0';
	for (int i = 0; i < size; i++) {
		str_[i] = str[i];
	}
}


String::String(const String& obj) {
	this->capacity_ = obj.capacity_;
	char* temp = allocator_.allocate(capacity_);
	strcpy_s(obj.str_, capacity_, temp);
	this->str_ = temp;
}


String::~String() {
	if (str_ != nullptr || capacity_ != 0) {
		allocator_.deallocate(str_);
	}
}


String& String::operator=(const String& obj) {
	if (this != &obj) {
		allocator_.deallocate(str_);
		capacity_ = obj.capacity_;
		str_ = allocator_.allocate(capacity_);
		strcpy_s(obj.str_, capacity_, this->str_);
	}
	return *this;
}


String::String(String&& obj) noexcept : str_(obj.str_), capacity_(obj.capacity_) {
	obj.str_ = nullptr;
}


String& String::operator=(String&& obj) noexcept {
	allocator_.deallocate(str_);
	capacity_ = obj.size();
	str_ = obj.str_;
	obj.str_ = nullptr;
	return *this;
}


String operator+(const String& lhs, const String& rhs) {
	int new_size = lhs.capacity_ + rhs.capacity_;
	String result(new_size);
	strcpy_s(result.str_, new_size, lhs.str_);
	
	for (int i = 0; i < rhs.capacity_; i++) {
		result.str_[lhs.capacity_ + i] = rhs.str_[i];
	}

	return result;
}


String operator+(char lhs, const String & rhs) {
	String result(rhs.capacity_ + 1);

	result.str_[0] = lhs;

	for (int i = 1; i < result.capacity_; i++) {
		result.str_[i] = rhs.str_[i - 1];
	}

	return result;
}


String operator+(const String& lhs, char rhs) {
	String result(lhs.capacity_ + 1);

	result.str_[result.capacity_] = rhs;

	for (int i = 1; i < result.capacity_; i++) {
		result.str_[i] = lhs.str_[i - 1];
	}

	return result;
}


String& String::operator+=(const String& rhs) {
	int size = this->size() + rhs.size();

	this->allocator_.reallocate(this->str_, capacity_, size);

	for (int i = capacity_; i < size; i++) {
		this->str_[i] = rhs.str_[i - capacity_];
	}
	this->capacity_ = size;

	return *this;
}


String& String::operator+=(char rhs) {
	int size = this->size() + 1;

	this->allocator_.reallocate(this->str_, capacity_, size);

	this->str_[size-1] = rhs;
	this->capacity_ = size;

	return *this;
}


bool operator==(const String& lhs, const String& rhs) {
	return std::strcmp(lhs.str_, rhs.str_) == 0;
}


bool operator!=(const String& lhs, const String& rhs) {
	return !(lhs == rhs);
}


bool operator<(const String& lhs, const String& rhs) {
	return std::strcmp(lhs.str_, rhs.str_) < 0;
}


bool operator<=(const String& lhs, const String& rhs) {
	return !(rhs < lhs);
}


bool operator>(const String& lhs, const String& rhs) {
	return rhs < lhs;
}


bool operator>=(const String& lhs, const String& rhs) {
	return !(lhs < rhs);
}


auto String::operator[](int i) noexcept			-> char& {
	return str_[i];
}


auto String::operator[](int i) const noexcept	-> const char& {
	return str_[i];
}


auto String::at(int i) -> char& {
	return str_[i];
}


auto String::at(int i) const -> const char& {
	return str_[i];
}


int String::size() const {
	if (capacity_ == 0) {
		return 0;
	}

	return static_cast<int>(strlen(str_));
}


int String::capacity() const {
	return capacity_;
}


void String::reserve(int new_capacity) {
	if (new_capacity > capacity_) {
		int old_size = size();
		allocator_.reallocate(str_, capacity_, new_capacity);
		capacity_ = new_capacity;
	}
}


void String::shrink_to_fit() {
	int current_size = size();
	if (current_size < capacity_) {
		allocator_.reallocate(str_, capacity_, current_size);
		capacity_ = current_size;
	}
}


void String::clean() {
	if (str_) {
		allocator_.deallocate(str_);
		str_ = nullptr;
		capacity_ = 0;
	}
}


bool String::empty() const {
	return this->size() == 0;
}


const char* String::c_str() const {
	return this->str_;
}


char* String::data() {
	return str_;
}


void String::push_back(char ch) {
	allocator_.reallocate(str_, this->size(), this->size() + 1);

	this->str_[this->size() - 1] = ch;
}


void String::pop_back() {
	this->str_[size() - 1] = '\0';
	shrink_to_fit();
}


std::ostream& operator<<(std::ostream& out, const String& obj) {

	if (obj.str_ == nullptr) {
		return out;
	}

	out << obj.str_;
	return out;
}


std::istream& operator>>(std::istream& in, const String& obj) {
	String temp;
	//in >> temp;
	return in >> temp;
}