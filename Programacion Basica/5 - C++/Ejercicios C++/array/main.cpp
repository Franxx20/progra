#include <iostream>
#include "array.h"

int main() {
	Array<int> int_vec(7);

	for(int i = 0; i < 7; i++) {
		int_vec.push(i+1);
	}

	for(int i = 0; i < 3; i++) {
		int_vec.push(i*4+1);
	}

	std::cout << "contents: " << int_vec << std::endl;
	std::cout << "size: " << int_vec.size() << std::endl;

	Array<int> copy_vec(int_vec);
	copy_vec.pull(0);

	std::cout << "contents: " << copy_vec << std::endl;
	std::cout << "size: " << copy_vec.size() << std::endl;

	std::cout << copy_vec.get(0) << std::endl;

	return 0;
}