#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void createFile(ofstream& filename, int* numbers, int size);
int* readFromFile(ifstream& filename, int& size);
void writeToFile(ofstream& out, int* numbers, int size);
int countBinaryDifference(int num);
void findAndRemoveOddNegativeElements(int* numbers, int& size);
void bubbleSort(int* numbers, int size);

void createFile(ofstream& filename, int* numbers, int size) {
    if (!filename.is_open()) {
        throw "Failed to open the file.";
    }

    for (int i = 0; i < size; i++) {
        filename << numbers[i] << " ";
    }

    filename.close();
}

int* readFromFile(ifstream& fin, int& size) {
    if (!fin.is_open()) {
        throw "Failed to open the file.";
    }

    int tmp;
    size = 0;

    while (fin >> tmp) {
        size++;
    }

    int* numbers = new int[size];
    fin.clear();
    fin.seekg(0, ios::beg);

    int i = 0;
    while (fin >> numbers[i++]) {}

    fin.close();
    return numbers;
}

void writeToFile(ofstream& out, int* numbers, int size) {
    if (!out.is_open()) {
        throw "Output stream is not in a good state.";
    }

    for (int i = 0; i < size; i++) {
        out << numbers[i] << " ";
    }

    out.close();
}

int countBinaryDifference(int num) 
{
    int countOnes = 0;

    while (num != 0) {
        if (num % 2 == 1) {
            countOnes++;
        }

        num /= 2;
    }

    int countZeros = sizeof(int) * 8 - countOnes;

    return countOnes - countZeros;
}

void findAndRemoveOddNegativeElements(int* numbers, int& size) {
    int* temp = new int[size];
    int tempSize = 0;

    for (int i = 0; i < size; i++) {
        if (numbers[i] >= 0 || numbers[i] % 2 == 0) {
            temp[tempSize++] = numbers[i];
        }
    }

    size = tempSize;
    for (int i = 0; i < size; i++) {
        numbers[i] = temp[i];
    }

    delete[] temp;
}

void bubbleSort(int* numbers, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (countBinaryDifference(numbers[j + 1]) > countBinaryDifference(numbers[j])) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

int main() {
    string fileIn = "in.txt", fileOut = "out.txt";
    int size = 10;

    int* numbers = new int[size];

    cout << "Enter " << size << " elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> numbers[i];
    }

    ofstream outputFile(fileIn);
    createFile(outputFile, numbers, size);

    ifstream inputFile(fileIn);
    int* readNumbers = readFromFile(inputFile, size);

    findAndRemoveOddNegativeElements(readNumbers, size);
    bubbleSort(readNumbers, size);

    ofstream InOutFile(fileOut);
    writeToFile(InOutFile, readNumbers, size);

    return 0;
}