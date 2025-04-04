#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> // For formatting output

using namespace std;

// Function to read matrix data from a file
void readMatrixFromFile(const string& filename, vector<vector<int>>& matrixA, vector<vector<int>>& matrixB, int& N) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    file >> N; // Read matrix size
    matrixA.assign(N, vector<int>(N));
    matrixB.assign(N, vector<int>(N));

    // Read Matrix A
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            file >> matrixA[i][j];

    // Read Matrix B
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            file >> matrixB[i][j];

    file.close();
}

// Function to print a matrix neatly
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row)
            cout << setw(4) << val; // Align output for better readability
        cout << endl;
    }
}

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int N = A.size();
    vector<vector<int>> result(N, vector<int>(N));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            result[i][j] = A[i][j] + B[i][j];

    return result;
}

// Function to multiply two matrices
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int N = A.size();
    vector<vector<int>> result(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) { // Iterate through rows of A
        for (int j = 0; j < N; j++) { // Iterate through columns of B
            for (int k = 0; k < N; k++) { // Sum product of A row and B column
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Function to compute the sum of the main and secondary diagonals
int sumDiagonals(const vector<vector<int>>& matrix) {
    int N = matrix.size();
    int sum = 0;

    for (int i = 0; i < N; i++) {
        sum += matrix[i][i]; // Main diagonal
        sum += matrix[i][N - 1 - i]; // Secondary diagonal
    }

    if (N % 2 == 1) // If N is odd, middle element is counted twice
        sum -= matrix[N / 2][N / 2];

    return sum;
}

// Function to swap two rows
void swapRows(vector<vector<int>>& matrix, int row1, int row2) {
    int N = matrix.size();
    if (row1 >= 0 && row1 < N && row2 >= 0 && row2 < N) {
        swap(matrix[row1], matrix[row2]);
    } else {
        cout << "Invalid row indices!" << endl;
    }
}

// Function to swap two columns
void swapColumns(vector<vector<int>>& matrix, int col1, int col2) {
    int N = matrix.size();
    if (col1 >= 0 && col1 < N && col2 >= 0 && col2 < N) {
        for (int i = 0; i < N; i++)
            swap(matrix[i][col1], matrix[i][col2]);
    } else {
        cout << "Invalid column indices!" << endl;
    }
}

// Function to update an element in the matrix
void updateElement(vector<vector<int>>& matrix, int row, int col, int newValue) {
    int N = matrix.size();
    if (row >= 0 && row < N && col >= 0 && col < N) {
        matrix[row][col] = newValue;
    } else {
        cout << "Invalid indices!" << endl;
    }
}

// Main function
int main() {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    int N;
    vector<vector<int>> matrixA, matrixB;

    // Read matrices from file
    readMatrixFromFile(filename, matrixA, matrixB, N);

    cout << "\nMatrix A:\n";
    printMatrix(matrixA);
    cout << "\nMatrix B:\n";
    printMatrix(matrixB);

    // Matrix Addition
    vector<vector<int>> sumMatrix = addMatrices(matrixA, matrixB);
    cout << "\nMatrix Sum (A + B):\n";
    printMatrix(sumMatrix);

    // Matrix Multiplication
    vector<vector<int>> productMatrix = multiplyMatrices(matrixA, matrixB);
    cout << "\nMatrix Product (A * B):\n";
    printMatrix(productMatrix);

    // Diagonal Sum
    cout << "\nSum of diagonals in Matrix A: " << sumDiagonals(matrixA) << endl;

    // Row Swap
    int row1, row2;
    cout << "\nEnter two row indices to swap: ";
    cin >> row1 >> row2;
    swapRows(matrixA, row1, row2);
    cout << "\nMatrix A after row swap:\n";
    printMatrix(matrixA);

    // Column Swap
    int col1, col2;
    cout << "\nEnter two column indices to swap: ";
    cin >> col1 >> col2;
    swapColumns(matrixA, col1, col2);
    cout << "\nMatrix A after column swap:\n";
    printMatrix(matrixA);

    // Update Element
    int r, c, newValue;
    cout << "\nEnter row index, column index, and new value: ";
    cin >> r >> c >> newValue;
    updateElement(matrixA, r, c, newValue);
    cout << "\nMatrix A after update:\n";
    printMatrix(matrixA);

    return 0;
}
