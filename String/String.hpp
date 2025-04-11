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
Çàäàíèå 1
	Ðåàëèçîâàòü ìåòîäû ñòðóêòóðû-àëëîêàòîðà èñïîëüçóÿ ëèáî
	îïåðàòîðû new è delete, ëèáî ôóíêöèè óïðàâëåíèÿ ïàìÿòè 
	èç áèáëèîòåêè stdlib.h
Çàäàíèå 2
	Ðåàëèçîâàòü âñå êîíñòðóêòîðû êëàññà String
	Â òåëå êîíñòðóêòîðîâ íå äîëæíû ôèãóðèðîâàòü îïåðàòîðû
	new/delete èëè ôóíêöèè óïðàâëåíèÿ ïàìÿòè 
	èç áèáëèîòåêè stdlib.h
Çàäàíèå 3
	Ðåàëèçîâàòü äåñòðóêòîð êëàññà è îïåðàòîðû ïðèñâàèâàíèÿ.
	Â òåëå ìåòîäîâ íå äîëæíû ôèãóðèðîâàòü îïåðàòîðû
	new/delete èëè ôóíêöèè óïðàâëåíèÿ ïàìÿòè
	èç áèáëèîòåêè stdlib.h
Çàäàíèå 4
	×àñòü 1
	Ðåàëèçîâàòü íå çàêîììåíòèðîâàííûå Îïåðàòîðû.
	Â òåëå ìåòîäîâ íå äîëæíû ôèãóðèðîâàòü îïåðàòîðû
	new/delete èëè ôóíêöèè óïðàâëåíèÿ ïàìÿòè
	èç áèáëèîòåêè stdlib.h
	×àñòü 2
	Ïîäêëþ÷èòü âàø êëàññ â îñíîâíîé ðàáî÷èé êîä ïðîãðàììû 
	è ïðîäåìîíñòðèðîâàòü ðàáîòîñïîñîáíîñòü ðàíåå ðåàëèçîâàííîãî êîäà
	Â ôóíêöèè main
Çàäàíèå 5
	×àñòü 1
	Ðåàëèçîâàòü íå çàêîììåíòèðîâàííûå ìåòîäû êëàññà
	Â òåëå ìåòîäîâ íå äîëæíû ôèãóðèðîâàòü îïåðàòîðû
	new/delete èëè ôóíêöèè óïðàâëåíèÿ ïàìÿòè
	èç áèáëèîòåêè stdlib.h
	×àñòü 2
	Ïîäêëþ÷èòü âàø êëàññ â îñíîâíîé ðàáî÷èé êîä ïðîãðàììû
	è ïðîäåìîíñòðèðîâàòü ðàáîòîñïîñîáíîñòü ðàíåå ðåàëèçîâàííîãî êîäà
	Â ôóíêöèè main
Çàäàíèå 6* 
	Íàïèñàòü ïðîåêò unit-òåñòèðîâàíèÿ äëÿ âàøåãî êëàññà String

13.02.2025 Çàäàíèå ÷åòâ¸ðòîé íåäåëè
*/

#endif // !STRING_HPP
