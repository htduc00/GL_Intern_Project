#include <iostream>

void swapByReference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapByPointer(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main()
{
    int a, b;
    std::cout << "Swap by reference" << std::endl;
    std::cin >> a >> b;
    swapByReference(a, b);
    std::cout << a <<" "<<b << std::endl;
    std::cout << "Swap by pointer" << std::endl;
    std::cin >> a >> b;
    swapByPointer(&a, &b);
    std::cout << a <<" "<< b << std::endl;

    return 0;
}

