//
// Created by etudiant on 06/10/15.
//

#include "QT/Crack/Functions.h"

long GetFileSize(string name)
{
    std::ifstream fichier (name);
    int count = 0;
    while ( !fichier.eof() )
    {
        string line;
        fichier >> line;
        ++count;
    }

    fichier.close();
    return count;
}

int main(int argc, char *argv[]) {


    std::ifstream fichier ("database.txt");

    long taille = GetFileSize("database.txt");

    string tab[taille];

    if (fichier)
    {
        std::string ligne;
        int i  = 0;
        while (std::getline(fichier, ligne)) {
            tab[i++] = ligne;
        }
    } else {
        cout << "ERROR" << endl;
    }


    for (int i = 0; i < taille; i++){
        cout << tab[i] << endl;
    }
}
