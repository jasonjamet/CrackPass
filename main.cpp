//
// Created by etudiant on 06/10/15.
//

#include "Functions.h"
using namespace std;

int main(int argc, char *argv[]) {

    if(argc >1) {
        if(atoi(argv[1]) == 0) {
            Functions * F = new Functions();

            int rank;
            MPI_Init(&argc, &argv);

            MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Rank
            char * message = (char *) malloc(100);

            if(rank == 0) {
                map<string, string> userAndPass = F->readShadowFile("shadow");
                F->setPasswordEncryptedByName(userAndPass, argv[2]);
                strcpy(message, F->getHash().c_str());
            }
            MPI_Bcast(message, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

            if (rank==0) {
                MPI_Recv(message, 100, MPI_CHAR, MPI_ANY_SOURCE, 7, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                cout << "Password found: " << message << endl;
                MPI_Abort(MPI_COMM_WORLD, MPI_SUCCESS);

            }
            else {

                F->setHash(message);
                cout << F->getHash() << endl;
                if(atoi(argv[3]) == 1) {
                    F->launchSimpleBruteForce();
                } else {
                    F->launchDictionaryBruteForce();
                }
            }

            MPI_Barrier(MPI_COMM_WORLD);
            MPI_Finalize();
        } else if(atoi(argv[1]) == 1) {
            
        }


    } else {
        cout << "arguments are missing" << endl;
        return 1;
    }

    return 0;
}

