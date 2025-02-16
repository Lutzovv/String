#pragma once

#ifndef STRING_HPP
#define STRING_HPP

#include <string.h>
#include <iostream>
#include <type_traits>

class String {
public:
	String();
	explicit String(int);
	String(const char*);
	
	~String();
	String(const String&);
	String& operator=(const String&);

	String(String&&) noexcept;
	String& operator=(String&&) noexcept;

	friend String operator+(const String& lhs, const String& rhs);
	friend String operator+(char lhs, const String& rhs);
	friend String operator+(const String& lhs, char rhs);

	String& operator+=(const String& rhs);
	String& operator+=(char rhs);

	friend bool operator	==	(const String& lhs, const String& rhs);
	friend bool operator	!=	(const String& lhs, const String& rhs);
	friend bool operator	<	(const String& lhs, const String& rhs);
	friend bool operator	<=	(const String& lhs, const String& rhs);
	friend bool operator	>	(const String& lhs, const String& rhs);
	friend bool operator	>=	(const String& lhs, const String& rhs);

	auto operator[](int i) noexcept			-> char&;
	auto operator[](int i) const noexcept	-> const char&;

	auto at(int i)			-> char&;
	auto at(int i) const	-> const char&;

	int size() const;
	int capacity() const;
	void reserve(int new_capacity);
	void shrink_to_fit();
	void clean();

	bool empty() const;

	//class iterator{};
	//class const_iterator{};
	//class right_iterator{};
	//class const_right_iterator{};

	//iterator begin();
	//iterator end();
	//const_iterator cbegin();
	//const_iterator cend();

	//right_iterator rbegin();
	//right_iterator rend();
	//const_right_iterator crbegin();
	//const_right_iterator crend();

	const char* c_str() const;
	char* data();

	void push_back(char ch);
	void pop_back();

	//void emplace_back(char ch);
	//
	//void insert(iterator& place, char ch);
	//void emplace(iterator& place, char ch);

	//void eraise(iterator& place);
	//void eraise(iterator& start,iterator& end);

	friend std::ostream& operator<<(std::ostream& out, const String& obj);
	friend std::istream& operator>>(std::istream& in, const String& obj);

private:
	struct{
		char* allocate(int size) {;
			return new char[++size] ;
		}


		void  deallocate(char* place) {
			delete[] place;
			place = nullptr;
		}


		void reallocate(char*& place, int old_size, int new_size) {
			char* new_arr = allocate(new_size);
			new_arr[new_size] = '\0';
			
			for (int i = 0; i < old_size; i++) {
				new_arr[i] = place[i];
			}

			//strcpy_s(new_arr, new_size, place);

			std::swap(place, new_arr);

			delete[] new_arr;
		}

	} allocator_;
	int capacity_;
	char* str_;
};

/*
Задание 1
	Реализовать методы структуры-аллокатора используя либо
	операторы new и delete, либо функции управления памяти 
	из библиотеки stdlib.h
Задание 2
	Реализовать все конструкторы класса String
	В теле конструкторов не должны фигурировать операторы
	new/delete или функции управления памяти 
	из библиотеки stdlib.h
Задание 3
	Реализовать деструктор класса и операторы присваивания.
	В теле методов не должны фигурировать операторы
	new/delete или функции управления памяти
	из библиотеки stdlib.h
Задание 4
	Часть 1
	Реализовать не закомментированные Операторы.
	В теле методов не должны фигурировать операторы
	new/delete или функции управления памяти
	из библиотеки stdlib.h
	Часть 2
	Подключить ваш класс в основной рабочий код программы 
	и продемонстрировать работоспособность ранее реализованного кода
	В функции main
Задание 5
	Часть 1
	Реализовать не закомментированные методы класса
	В теле методов не должны фигурировать операторы
	new/delete или функции управления памяти
	из библиотеки stdlib.h
	Часть 2
	Подключить ваш класс в основной рабочий код программы
	и продемонстрировать работоспособность ранее реализованного кода
	В функции main
Задание 6* 
	Написать проект unit-тестирования для вашего класса String

13.02.2025 Задание четвёртой недели
*/

#endif // !STRING_HPP
