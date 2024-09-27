export module main;

import std;
import engine;

export
int main(int argc, char** argv) {
	int a = 5;
	int b = 10;
	int c = sum(a, b);

	std::cout << "Sum of " << a << " and " << b << " is " << c << std::endl;

	return 0;
}