#ifndef ETUDIANT_H
#define ETUDIANT_H

struct Etudiant
{
    char nom[30];
    char prenom[40];
    char adresse[60];
    float notes[3];  // 3 notes, pas 5 !
};

#endif