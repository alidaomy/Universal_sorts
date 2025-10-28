#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// ПРЕДВАРИТЕЛЬНЫЕ ОБЪЯВЛЕНИЯ ФУНКЦИЙ СОРТИРОВКИ
// (каждый участник команды должен реализовать свою функцию)

// Сортировка вставками (фамилия)
//template<typename T>
//void insertion_sort_familyname(vector<T>& aVector);

// Сортировка Шелла (фамилия)
template<typename T>
void aboyan_shell(vector<T>& aVector);

// Быстрая сортировка (фамилия)
//template<typename T>
//void quicksort_familyname(vector<T>& arr);


// Сортировка слиянием (Канева)
template<typename T>
void kaneva_merge(vector<T>& arr);


// РЕАЛИЗАЦИЯ ФУНКЦИИ СОРТИРОВКИ ШЕЛЛА АБОЯН
template<typename T>
void aboyan_shell(vector<T>& aVector) {
    int n = aVector.size();

    // Последовательность gaps - начинаем с n/2 и делим на 2 каждую итерацию
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Выполняем сортировку вставками для этого gap
        for (int i = gap; i < n; i++) {
            T temp = aVector[i];
            int j;

            // Сдвигаем элементы, пока не найдем правильную позицию для aVector[i]
            for (j = i; j >= gap && aVector[j - gap] > temp; j -= gap) {
                aVector[j] = aVector[j - gap];
            }

            // Вставляем элемент на правильную позицию
            aVector[j] = temp;
        }
    }
}

// РЕАЛИЗАЦИЯ ФУНКЦИИ СОРТИРОВКИ СЛИЯНИЕМ КАНЕВА
template<typename T>
void mergesort_kaneva(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<T> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
        
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template<typename T>
void merge_kaneva(vector<T>& arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    merge_kaneva(arr, left, mid);
    merge_kaneva(arr, mid + 1, right);
    mergesort_kaneva(arr, left, mid, right);
}

template<typename T>
void kaneva_merge(vector<T>& arr) {
    if (arr.size() <= 1) return;
    merge_kaneva(arr, 0, arr.size() - 1);
}


// Вспомогательные функции 
vector<string> readDataFromFileUnity(const string& filename) {
    vector<string> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return data;
    }

    string token;
    while (file >> token) {
        data.push_back(token);
    }

    file.close();
    return data;
}

template<typename T>
float measureSortTimeUnity(void (*sortFunction)(vector<T>&), vector<T>& data) {
    auto start = chrono::high_resolution_clock::now();
    sortFunction(data);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<float, milli>(end - start).count();
}

// Проверка отсортированности массива 
template<typename T>
bool isSorted(const vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Файлы для тестирования
    vector<string> files = {
        "test_double.txt", "test_int.txt", "test_letter.txt", "test_string.txt", "test_time.txt", "test_one.txt"
    };

    // Алгоритмы сортировки
    vector<pair<string, void (*)(vector<string>&)>> algorithms = {
        //пример: {"MergeSort (фамилия)", mergeSort_byKaneva<string>}
        //{"InsertionSort (фамилия)", },
        //{"QuickSort (фамилия)", },
        {"ShellSort (Абоян)", aboyan_shell<string>},
        {"MergeSort (Канева)", kaneva_merge<string>}
    };

    // Тестирование каждого файла
    for (const auto& filename : files) {
        cout << "=========================================" << endl;
        cout << "Testing file: " << filename << endl;

        vector<string> originalData = readDataFromFileUnity(filename);

        if (originalData.empty()) {
            cout << "File not found or empty, skipping..." << endl;
            continue;
        }

        cout << "Elements count: " << originalData.size() << endl;

        // Тестирование каждого алгоритма
        for (const auto& [algoName, algoFunc] : algorithms) {
            vector<string> testData = originalData; // Копия для теста

            cout << "  " << algoName << ": ";
            cout.flush();

            float time = measureSortTimeUnity(algoFunc, testData);

            // Проверка корректности сортировки
            if (isSorted(testData)) {
                cout << time << " ms ✓" << endl;
            }
            else {
                cout << time << " ms ✗ (Неверно отсортированно!)" << endl;
            }
        }
        cout << endl;
    }

    return 0;

}
