#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// ПРЕДВАРИТЕЛЬНЫЕ ОБЪЯВЛЕНИЯ ФУНКЦИЙ СОРТИРОВКИ
// (каждый участник команды должен реализовать свою функцию)

// Сортировка вставками (фамилия)
template<typename T>
void insertion_sort_familyname(vector<T>& aVector);

// Сортировка Шелла (фамилия)
template<typename T>
// пример: void aboyan_shell(vector<T>& aVector);

// Быстрая сортировка (фамилия)
template<typename T>
void quicksort_familyname(vector<T>& arr);


// Сортировка слиянием (фамилия)
template<typename T>
void mergesort_familyname(vector<T>& arr);


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
        {"InsertionSort (фамилия)", },
        {"QuickSort (фамилия)", },
        {"ShellSort (фамилия)", },
        {"MergeSort (фамилия)", }
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