//
// Created by etudiant on 06/10/15.
//

#include "Functions.h"
using namespace std;

int main(int argc, char *argv[]) {

    if(argc == 4) {
        Functions *F = new Functions();

        if(strcmp(argv[1], "MPI") == 0) {

            int rank;
            MPI_Init(&argc, &argv);

            MPI_Comm_rank(MPI_COMM_WORLD, &rank); // get current rank


            char *message = (char *) malloc(100);

            if (rank == 0) {
                map<string, string> userAndPass = F->readShadowFile("shadow"); // get hashed password of the selected user
                F->setPasswordEncryptedByName(userAndPass, argv[2]);
                strcpy(message, F->getHash().c_str());
            }
            MPI_Bcast(message, 100, MPI_CHAR, 0, MPI_COMM_WORLD); // alloc the hashed password for all users

            if (rank == 0) {
                MPI_Recv(message, 100, MPI_CHAR, MPI_ANY_SOURCE, 7, MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE); // lock!! wait to receive the password
                cout << "Password found: " << message << endl;
                MPI_Abort(MPI_COMM_WORLD, MPI_SUCCESS);
            }
            else {
                F->setHash(message);
                if (atoi(argv[3]) == 1) {
                    F->launchSimpleBruteForceMPI();
                } else {
                    F->launchDictionaryBruteForceMPI();
                }
            }

            MPI_Barrier(MPI_COMM_WORLD);
            MPI_Finalize();
        } else {
            map<string, string> userAndPass = F->readShadowFile("shadow"); // get hashed password of the selected user
            F->setPasswordEncryptedByName(userAndPass, argv[2]);
            if (atoi(argv[3]) == 1) {
                F->launchSimpleBruteForce();
            } else {
                F->launchDictionaryBruteForce();
            }
            if (F->getFind()) {
                cout << "Password found: " << F->getPassword() << endl;
            } else {
                cout << "Password not found !" << endl;
            }
        }

    } else {
        cout << "arguments are missing" << endl;
        return 1;
    }

    return 0;
}
