//
// Created by etudiant on 06/10/15.
//

#include "QT/Crack/Functions.h"
using namespace std;

int main(int argc, char *argv[]) {

    if(argc >1) {
        Functions * F = new Functions();
        map<string, string> userAndPass = F->readShadowFile("shadow");
        F->setPasswordEncryptedByName(userAndPass, argv[1]);


        int rank, size;
        int tag = 7;
        MPI_Status status;
        char message[20];
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Rank

        if (rank==0) {
            MPI_Recv(message, 100, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            cout << "Password found: " << message << endl;
            MPI_Abort(MPI_COMM_WORLD, 0)

        }
        else {
            if(atoi(argv[2]) == 1) {
                F->launchSimpleBruteForce();
            } else {
                F->launchDictionaryBruteForce();
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Finalize();

    } else {
        cout << "arguments are missing" << endl;
        return 1;
    }

    return 0;
}

