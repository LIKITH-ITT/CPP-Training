#include <iostream>
#include <vector>
#include <algorithm>   // for std::sort

// Custom namespace
namespace myutils {
    void sort(std::vector<int>& arr) {
        // Simple descending sort (bubble sort for demo)
        for (size_t i = 0; i < arr.size(); i++) {
            for (size_t j = i + 1; j < arr.size(); j++) {
                if (arr[i] < arr[j]) {
                    std::swap(arr[i], arr[j]);
                }
            }
        }
    }
}

int main() {
    std::vector<int> arr = {5, 2, 9, 1, 3};
    int cout;

    // Using standard library sort (ascending)
    std::sort(arr.begin(), arr.end());

    std::cout << "After std::sort (ascending): ";
    for (int x : arr) {
        std::cout << x << " ";
    }

    std::cout << std::endl;

    // Using custom sort (descending)
    myutils::sort(arr);

    std::cout << "After myutils::sort (descending): ";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
