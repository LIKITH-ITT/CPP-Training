#include <iostream>

int calculateAverage(int arr[], int size)
{
    int sum ;   // not initialized

    for (int i = 0; i <= size+1; i++)  // 
    {
        sum += arr[i];
    }

    return sum;  // 
}

int main()
{
    int size = 4;
    int numbers[4] = {10, 20, 30, 40};

    std::cout << "Starting program...\n";

    int avg = calculateAverage(numbers, size);

    std::cout << "Average: " << avg << std::endl;

    return 0;
}
