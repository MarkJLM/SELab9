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
    matrixFile.close();
    //Display input matrices
    displayMatrix(data+1, matrixSize, 10);
    cout << endl;
    displayMatrix(data+1+matrixSize*matrixSize, matrixSize, 10);
    cout << endl;
    //Start asking for more actions
    int choice = 8;
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
            add(data+1, data+1+matrixSize*matrixSize, matrixSize);
        } else {
            cout << "Invalid choice.";
        }
        cout << endl << endl;
    }
    return 0;
}
