#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Configuration des couleurs ---
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

// Nom de l'exécutable à tester
const char* PROGRAMME = "./shell";
const char* FILE_IN   = "test_input.tmp";
const char* FILE_OUT  = "test_output.tmp";

// --- Fonction utilitaire pour lancer un test ---
void run_test(const char* nom_test, const char* commandes, const char* attendu) {
    FILE *fp;
    char buffer[4096]; // Buffer large pour stocker la sortie
    size_t bytes_read;
    int trouve = 0;

    // 1. Préparer le fichier d'entrée (Commandes + quit pour être sûr)
    fp = fopen(FILE_IN, "w");
    if (fp == NULL) { perror("Erreur fichier input"); exit(1); }
    fprintf(fp, "%s\nquit\n", commandes);
    fclose(fp);

    // 2. Construire la commande système : ./shell < input > output
    char sys_cmd[512];
    // 2>&1 permet de capturer aussi les erreurs (stderr)
    snprintf(sys_cmd, sizeof(sys_cmd), "%s < %s > %s 2>&1", PROGRAMME, FILE_IN, FILE_OUT);
    
    // 3. Exécuter le programme
    int ret = system(sys_cmd);
    if (ret != 0 && ret != 256) { // 256 arrive parfois si le exit(0) n'est pas clean, c'est pas grave ici
        // printf("Warning: Code retour programme = %d\n", ret); 
    }

    // 4. Lire le fichier de sortie pour vérifier le résultat
    fp = fopen(FILE_OUT, "r");
    if (fp == NULL) { perror("Erreur fichier output"); exit(1); }
    
    // On lit tout le fichier dans le buffer (attention au débordement dans un vrai projet)
    bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fp);
    buffer[bytes_read] = '\0'; // Fin de chaîne
    fclose(fp);

    // 5. Analyse : est-ce que "attendu" est dans "buffer" ?
    if (strstr(buffer, attendu) != NULL) {
        printf("%-50s %s[OK]%s\n", nom_test, COLOR_GREEN, COLOR_RESET);
    } else {
        printf("%-50s %s[FAIL]%s\n", nom_test, COLOR_RED, COLOR_RESET);
        printf("   Cmd: %s\n", commandes);
        printf("   Attendu: \"%s\"\n", attendu);
        printf("   Reçu (extrait): %.100s...\n", buffer); // Affiche les 100 premiers chars
    }
}

// --- Nettoyage des fichiers temporaires ---
void cleanup() {
    remove(FILE_IN);
    remove(FILE_OUT);
}

int main() {
    printf("%s=== TEST UNITAIRE EN C (Shell) ===%s\n\n", COLOR_BLUE, COLOR_RESET);

    // Vérifier si l'exécutable existe (astuce simple)
    FILE* f = fopen(PROGRAMME, "r");
    if (!f) {
        printf("%sErreur critique: L'exécutable '%s' n'existe pas.%s\n", COLOR_RED, PROGRAMME, COLOR_RESET);
        printf("Veuillez compiler le projet avant de lancer les tests.\n");
        return 1;
    }
    fclose(f);

    // --- Exercice 3.1 ---
    printf("--- Exercice 3.1 : Bases ---\n");
    run_test("Echo simple",           "echo Hello World",       "Echo: Hello World");
    run_test("Echo avec espaces",     "echo Bonjour a tous",    "Echo: Bonjour a tous");
    run_test("Commande inconnue",     "toto",                   "Commande non reconnue");
    
    // --- Exercice 3.2 ---
    printf("\n--- Exercice 3.2 : Commandes ---\n");
    run_test("Version",               "version",                "1.0.1");
    run_test("Help (Anglais)",        "help",                   "Help - Commandes disponibles");

    // --- Exercice 3.3 ---
    printf("\n--- Exercice 3.3 : Français ---\n");
    // Note: Pour que les accents passent bien, assure-toi que ton terminal est UTF-8
    run_test("Aide (Français)",       "aide",                   "Aide - Commandes disponibles");
    run_test("Echo (Français)",       "affiché TestFR",         "Affiché: TestFR");
    
    // --- Exercice 3.4 ---
    printf("\n--- Exercice 3.4 : Calculatrice ---\n");
    run_test("Addition",              "calc 2 + 3",             "5");
    run_test("Soustraction",          "calc 10 - 4",            "6");
    run_test("Multiplication",        "calc 2.5 * 2",           "5");
    run_test("Division par zéro",     "calc 5 / 0",             "Division par zéro");
    run_test("Resultat a virgule",    "calc 1.2 * 4.0",         "4.8");
    run_test("Priorité (simple)",     "calculer 10 / 2",        "5");
    run_test("Erreur syntaxe",        "calc 2 +",               "Erreur");


    // --- Exercice 4 (TP4) : Priorités et Parenthèses ---
    printf("\n%s--- TP4 : Expressions Complexes ---%s\n", COLOR_BLUE, COLOR_RESET);
    run_test("Priorité Opératoire (* > +)", "calc 3 + 4 * 5",   "23");
    run_test("Parenthèses simples",         "calc (3 + 4) * 5", "35");
    run_test("Parenthèses complexes",       "calc (10 + 2) / (4 - 1)", "4");
    run_test("Décimaux + Priorité",         "calc 10 - 2.5 * 2", "5");
    run_test("Calcul complexe (FR)",        "calculer 2 * (3 + 2)", "10");

    // Nettoyage final
    cleanup();
    
    printf("\n%s=== FIN DES TESTS ===%s\n", COLOR_BLUE, COLOR_RESET);
    return 0;
}