#include "string.hpp"

int main() {
	system("chcp 1251>NUL");

	String a = "aboba";
	a.clean();

	std::cout << a << "123";
}