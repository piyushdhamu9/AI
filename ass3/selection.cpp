#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}
int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    cout << "Original array:\n";
    for (int num : arr) cout << num << " ";
    cout << "\n\n";

    selectionSort(arr);

    cout << "Array after Selection Sort:\n";
    cout << "---------------------------\n";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    return 0;
}

