#include <iostream>
#include <gmpxx.h>

template <typename T>
void insertion_sort(T arr[], int N)
{
    for (int i = 1; i < N; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j-1]) {
                auto temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            }
            else break;
        }
    }
    return;
}

int main() 
{
    int size;
    std::cin >> size;
    std::cin.ignore(100, '\n'); // tell the input to ignore the first newline character
    mpz_class arr[size];
    std::string in;

    // read the numbers line by line
    for (int i = 0; i < size; i++) {
        std::getline(std::cin, in);
        arr[i] = in;
    }

    std::cout << "Array before sorting: " << '\n';
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << '\n';
    }

    insertion_sort(arr, size);
    std::cout << "Array after sorting: " << '\n';
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << '\n';
    }

    return 0;
}
