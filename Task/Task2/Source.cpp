#include<iostream>

unsigned long long int factorial(int n) {
	unsigned long long int result = 1;
	for (int i = 2; i <= n; i++) {
		result *= i;
	}
	return result;
}

int main()
{
	int n;
	std::cout << "Enter a positive integer number <= 20: ";
	while (std::cin >> n && n <= 0) {
		std::cout << "Enter a positive integer number <= 20: ";
	}
	std::cout << n << "!= " << factorial(n);
	return 0;
}

