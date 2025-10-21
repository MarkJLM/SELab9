//Matrix Manipulation Program
//No external sources used.
//Created 10/20/25 Mark Lammers-Meis

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void displayMatrix(int* data, int size) {
    for (int i = 0; i < size*size; i ++) {
        cout << ((*(data+i)<10)?" ":"") << *(data+i) << (((i+1)%size==0)?"\n":" ");
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
    matrixFile.close();
    displayMatrix(data+1, matrixSize);
    cout << endl;
    displayMatrix(data+1+matrixSize*matrixSize, matrixSize);
    return 0;
}
