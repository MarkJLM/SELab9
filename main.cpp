//Matrix Manipulation Program
//No external sources used.
//Created 10/20/25 Mark Lammers-Meis

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void displayMatrix(int* data, int size, int digits) {
    string spaces;
    int curDigits;
    for (int i = 0; i < size*size; i ++) {
        spaces = "";
        curDigits = *(data+i);
        while (digits>curDigits) {
            curDigits *= 10;
            spaces = spaces + " ";
        }
        cout << spaces << *(data+i) << (((i+1)%size==0)?"\n":" ");
    }
}

void add(int* matrix1, int* matrix2, int size) {
    cout << "Sum of input matrices:" << endl;
    int output[size*size];
    int maxDigits = 10;
    for (int i = 0; i < size * size; i ++) {
        output[i] = *(matrix1+i) + *(matrix2+i);
        while (maxDigits < output[i]) {
            maxDigits *= 10;
        }
    }
    displayMatrix(output, size, maxDigits/10);
}

void multiply(int* matrix1, int* matrix2, int size) {
    cout << "Product of input matrices:" << endl;
    int output[size*size];
    int maxDigits = 10;
    for (int i = 0; i < size * size; i ++) {
        output[i] = 0;
        for (int j = 0; j < size; j ++) {
            output[i] += (*(matrix1+(i/size)*size+j)) * (*(matrix2+i%size+j*size));
        }
        while (maxDigits < output[i]) {
            maxDigits *= 10;
        }
    }
    displayMatrix(output, size, maxDigits/10);
}

void trace(int* matrix, int size) {
    int output = 0;
    for (int i = 0; i < size; i ++) {
        output += *(matrix+i*(size+1));
    }
    cout << "Sum of main diagonal: " << output << endl;
    output = 0;
    for (int i = 0; i < size; i ++) {
        output += *(matrix+(i+1)*(size-1));
    }
    cout << "Sum of secondary diagonal: " << output;
}

void swapRows(int* matrix, int row1, int row2, int size) {
    if (row1 >= 0 && row1 < size && row2 >= 0 && row2 < size) {
        cout << "Row-swapped matrix:" << endl;
        int buffer[size];
        for (int i = 0; i < size; i ++) {
            buffer[i] = *(matrix+size*row1+i);
            *(matrix+size*row1+i) = *(matrix+size*row2+i);
            *(matrix+size*row2+i) = buffer[i];
        }
        displayMatrix(matrix, size, 10);
    } else {
        cout << "Invalid row numbers.";
    }
}

int main() {
    //Open a file
    string fileName;
    cout << "Input file name: ";
    cin >> fileName;
    ifstream matrixFile(fileName);
    //Get matrix size
    string fileLine;
    getline(matrixFile, fileLine);
    int matrixSize = 0;
    for (int i = 0; fileLine[i] > 47 && fileLine[i] < 58; i ++) {
        //Turn a character of the size into an integer's digit
        matrixSize = matrixSize*10 + fileLine[i] - 48;
    }
    //Start saving matrix data
    int dataLength = matrixSize*matrixSize*2+1;
    int data[dataLength];
    data[0] = matrixSize;
    //Read empty line
    getline(matrixFile, fileLine);
    //Read matrix values
    for (int i = 0; i < matrixSize*2; i ++) {
        getline(matrixFile, fileLine);
        //Check every character in the input string
        for (int j = 0; j < matrixSize; j ++) {
            //Add the digits in the string to the data row
            data[i*matrixSize+j+1] = (fileLine[j*3] - 48)*10 + fileLine[j*3+1] - 48;
        }
    }
    int* matrix1 = data+1;
    int* matrix2 = data+1+matrixSize*matrixSize;
    matrixFile.close();
    //Display input matrices
    displayMatrix(matrix1, matrixSize, 10);
    cout << endl;
    displayMatrix(matrix2, matrixSize, 10);
    cout << endl;
    //Start asking for more actions
    int choice = 8;
    int row1 = 0;
    int row2 = 0;
    while (choice > 1) {
        cout << "1. Quit\n2. Add\n3. Multiply\n4. Get Diagonals\n5. Swap Rows\n6. Swap Columns\n7. Change Entry\n";
        cout << "Please enter a choice: ";
        cin >> choice;
        //Get choice action
        cout << endl;
        if (choice == 1) {
            //Exit
            cout << "Goodbye!";
        } else if (choice == 2) {
            //Add the input matrices
            add(matrix1, matrix2, matrixSize);
        } else if (choice == 3) {
            //Multiply the input matrices
            multiply(matrix1, matrix2, matrixSize);
        } else if (choice == 4) {
            //Print the sums of the diagonals
            trace(matrix1, matrixSize);
        } else if (choice == 5) {
            //Ask for rows to swap
            cout << "First row to swap: ";
            cin >> row1;
            cout << "Second row to swap: ";
            cin >> row2;
            swapRows(matrix1, row1, row2, matrixSize);
        } else {
            cout << "Invalid choice.";
        }
        cout << endl << endl;
    }
    return 0;
}
