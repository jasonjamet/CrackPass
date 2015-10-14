//
// Created by etudiant on 06/10/15.
//

#include "QT/Crack/Functions.h"
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[]) {

    /*int rank, size, tag, rc, i;
    int code;
    MPI_Status status;
    char message[20];
    code = MPI_Init(&argc, &argv);
    cout << code << endl;
    code = MPI_Comm_size(MPI_COMM_WORLD, &size);
    cout << code << endl;

    code = MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Rank
    cout << code << endl;

    tag=7;
    if (rank==0) {
        strcpy(message, "Hello, world");
        for (int i=1;i<size;++i)
            code = MPI_Send(message, 13, MPI_CHAR, i, tag, MPI_COMM_WORLD);
    }
    else
        code = MPI_Recv(message, 13, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
    cout<<"node "<<rank<<": "<<message<< " size" << ":" << size << endl;
    code = MPI_Finalize();

*/


    Functions * F = new Functions();

    map<string, string> userAndPass = F->readShadowFile("shadow");
    map<int, string> numberUser;
    cout << "Please choose a user to crack (only numbers allowed): " << endl;
    int userNumber = 1;
    for (map<string ,string>::iterator it=userAndPass.begin(); it!=userAndPass.end(); ++it) {
        numberUser[userNumber] = it->first.c_str();
        cout << "\t" << userNumber << ": " << it->first.c_str() << endl;
        userNumber++;
    }


    //cin >> userNumber;
    userNumber = 1;
    F->setPasswordEncryptedByName(userAndPass, numberUser[userNumber]);
    cout << "Please choose a method \n \t1: Classical brute force\n \t2: Dictionary brute force" << endl;
    int algo;
    cin >> algo;

    if(algo == 1) {
        F->launchSimpleBruteForce(3);
    } else {
        F->launchDictionaryBruteForce();
    }

    if (F->getFind()) {
        cout << "Password found: " << F->getPassword() << endl;
    } else {
        cout << "Password not found !" << endl;
    }

    return 0;
}

