//
// Created by etudiant on 06/10/15.
//

#include <vector>
#include "QT/Crack/Functions.h"

int GetFileSize (string name)
{
    FILE *fp =  fopen(name.c_str(), "r");
    if (fp) {
        int n=0, c;

        while ((c = fgetc(fp)) != EOF)
        {
            if (c == '\n')
            {
                n++;
            }
        }

        fclose(fp);
        return n;
    } else {
        return -1;
    }
}

int main(int argc, char *argv[]) {


    Functions *F = new Functions();
    F->getPasswordEncryptedByName(F->readShadowFile("shadow"), "jason");

    cout <<  F->m_hash << endl;

    long taille = GetFileSize("database.txt");

    std::ifstream fichier ("database.txt");

    std::string ligne;

    std::vector<string> v(taille);

    if (fichier)
    {
        int i = 0;
        while (std::getline(fichier, ligne)) {
            v.push_back(ligne);

            i++;
            if (i == 5)
                break;
        }
    } else {
        cout << "ERROR" << endl;
    }

    fichier.close();

    cout <<  F->m_hash << endl;

    for (int i = 0; i < taille; i++){
        //cout << tab[i] << endl;
    }

    //F->launchDictionaryBruteForce();
    delete (F);
    return 0;
}
