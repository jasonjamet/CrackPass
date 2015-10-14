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


        int rank, size, rc, i;
        int tag = 7;
        int code;
        MPI_Status status;
        char message[20];
        code = MPI_Init(&argc, &argv);
        code = MPI_Comm_size(MPI_COMM_WORLD, &size);

        code = MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Rank

        /*if (rank==0) {
            strcpy(message, "Hello, world");
            for (int i=1;i<size;++i)
                code = MPI_Send(message, 13, MPI_CHAR, i, tag, MPI_COMM_WORLD);
        }
        else
            code = MPI_Recv(message, 13, MPI_CHAR, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout<<"node "<<rank<<": "<<message<< " size" << ":" << size << endl;*/
        code = MPI_Barrier(MPI_COMM_WORLD);
        code = MPI_Finalize();









        if(atoi(argv[2]) == 1) {
            F->launchSimpleBruteForce(3);
        } else {
            F->launchDictionaryBruteForce();
        }

        if (F->getFind()) {
            cout << "Password found: " << F->getPassword() << endl;
        } else {
            cout << "Password not found !" << endl;
        }
    } else {
        cout << "arguments are missing" << endl;
        return 1;
    }

    return 0;
}

