#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOITURES 50
#define MAX_DESCRIPTION 100
#define MAX_LOCATIONS 100
#define MAX_CLIENTS 50

typedef struct {
    char marque[MAX_DESCRIPTION];
    char modele[MAX_DESCRIPTION];
    int annee;
    float prix_journalier;
    int disponible;
    int en_panne;
} Voiture;

typedef struct {
    char client[MAX_DESCRIPTION];
    char voiture[MAX_DESCRIPTION];
    char date[MAX_DESCRIPTION];
} Location;

typedef struct {
    char client[MAX_DESCRIPTION];
    float coutTotal;
} CoutClient;

Voiture voitures[MAX_VOITURES];
Location locations[MAX_LOCATIONS];
CoutClient coutClients[MAX_CLIENTS];
int nombreVoitures = 0;
int nombreLocations = 0;
int nombreClients = 0;

void louerVoiture() {
    char nomClient[MAX_DESCRIPTION];
    int choixVoiture;
    int joursLocation;

    printf("Voitures disponibles :\n");
    for (int i = 0; i < nombreVoitures; i++) {
        if (voitures[i].disponible && !voitures[i].en_panne) {
            printf("%d. %s %s (%d) - %.2f EUR/jour\n", i + 1, voitures[i].marque, voitures[i].modele, voitures[i].annee, voitures[i].prix_journalier);
        }
    }

    printf("Choisissez le numero de la voiture a louer : ");
    scanf("%d", &choixVoiture);

    if (choixVoiture < 1 || choixVoiture > nombreVoitures || !voitures[choixVoiture - 1].disponible || voitures[choixVoiture - 1].en_panne) {
        printf("Choix invalide. La voiture n'est pas disponible.\n");
        return;
    }

    printf("Entrez votre nom : ");
    scanf("%s", nomClient);

    printf("Pendant combien de jours voulez-vous louer la voiture ? ");
    scanf("%d", &joursLocation);

    strcpy(locations[nombreLocations].client, nomClient);
    strcpy(locations[nombreLocations].voiture, voitures[choixVoiture - 1].marque);

    strcpy(locations[nombreLocations].date, "DateActuelle");
    nombreLocations++;

    voitures[choixVoiture - 1].disponible = 0;

    printf("Location réussie!\n");
    printf("Client : %s\n", nomClient);
    printf("Voiture louée : %s %s (%d)\n", voitures[choixVoiture - 1].marque, voitures[choixVoiture - 1].modele, voitures[choixVoiture - 1].annee);
    printf("Prix total : %.2f EUR\n", joursLocation * voitures[choixVoiture - 1].prix_journalier);
}

void afficherDescription() {
    int choixVoiture;

    printf("Voitures disponibles :\n");
    for (int i = 0; i < nombreVoitures; i++) {
        printf("%d. %s %s (%d) - %.2f EUR/jour\n", i + 1, voitures[i].marque, voitures[i].modele, voitures[i].annee, voitures[i].prix_journalier);
    }

    printf("Choisissez le numero de la voiture pour afficher sa description : ");
    scanf("%d", &choixVoiture);

    if (choixVoiture < 1 || choixVoiture > nombreVoitures) {
        printf("Choix invalide. Veuillez choisir un numero valide.\n");
        return;
    }

    printf("Description de la voiture :\n");
    printf("Marque : %s\n", voitures[choixVoiture - 1].marque);
    printf("Modele : %s\n", voitures[choixVoiture - 1].modele);
    printf("Annee : %d\n", voitures[choixVoiture - 1].annee);
    printf("Prix journalier : %.2f EUR\n", voitures[choixVoiture - 1].prix_journalier);
    printf("Disponible : %s\n", voitures[choixVoiture - 1].disponible ? "Oui" : "Non");
    printf("En panne : %s\n", voitures[choixVoiture - 1].en_panne ? "Oui" : "Non");

}

void supprimerVoiturePanne() {
    int choixVoiture;

    printf("Voitures en panne :\n");
    for (int i = 0; i < nombreVoitures; i++) {
        if (voitures[i].en_panne) {
            printf("%d. %s %s (%d)\n", i + 1, voitures[i].marque, voitures[i].modele, voitures[i].annee);
        }
    }

    printf("Choisissez le numero de la voiture en panne a supprimer : ");
    scanf("%d", &choixVoiture);

    if (choixVoiture < 1 || choixVoiture > nombreVoitures || !voitures[choixVoiture - 1].en_panne) {
        printf("Choix invalide. Veuillez choisir une voiture en panne.\n");
        return;
    }

    for (int i = choixVoiture - 1; i < nombreVoitures - 1; i++) {
        voitures[i] = voitures[i + 1];
    }

    nombreVoitures--;

    printf("Voiture en panne supprimee avec succes.\n");
}

void modifierVoiture() {
     int choixVoiture;
    int choixModification;

    printf("Voitures disponibles :\n");
    for (int i = 0; i < nombreVoitures; i++) {
        printf("%d. %s %s (%d)\n", i + 1, voitures[i].marque, voitures[i].modele, voitures[i].annee);
    }

    printf("Choisissez le numero de la voiture a modifier : ");
    scanf("%d", &choixVoiture);

    if (choixVoiture < 1 || choixVoiture > nombreVoitures) {
        printf("Choix invalide. Veuillez choisir un numero valide.\n");
        return;
    }

    printf("Que souhaitez-vous modifier pour la voiture %s %s (%d) ?\n", voitures[choixVoiture - 1].marque, voitures[choixVoiture - 1].modele, voitures[choixVoiture - 1].annee);
    printf("1. Description (marque, modele, annee)\n");
    printf("2. Etat (disponible/en panne)\n");
    printf("Choix : ");
    scanf("%d", &choixModification);

    switch (choixModification) {
        case 1:
            printf("Entrez la nouvelle description de la voiture :\n");
            printf("Marque : ");
            scanf("%s", voitures[choixVoiture - 1].marque);
            printf("Modele : ");
            scanf("%s", voitures[choixVoiture - 1].modele);
            printf("Annee : ");
            scanf("%d", &voitures[choixVoiture - 1].annee);
            break;
        case 2:
            printf("La voiture est-elle disponible ? (1 pour Oui / 0 pour Non) : ");
            scanf("%d", &voitures[choixVoiture - 1].disponible);
            if (!voitures[choixVoiture - 1].disponible) {
                voitures[choixVoiture - 1].en_panne = 0;
            } else {
                printf("La voiture est-elle en panne ? (1 pour Oui / 0 pour Non) : ");
                scanf("%d", &voitures[choixVoiture - 1].en_panne);
            }
            break;
        default:
            printf("Choix invalide. Aucune modification effectuee.\n");
            return;
    }

    printf("Modification de la voiture %s %s (%d) effectuee avec succes.\n", voitures[choixVoiture - 1].marque, voitures[choixVoiture - 1].modele, voitures[choixVoiture - 1].annee);

}

void afficherHistoriqueLocations() {
    if (nombreLocations == 0) {
        printf("Aucun historique de locations disponible.\n");
        return;
    }

    printf("Historique des locations :\n");
    printf("%-20s %-20s %-20s\n", "Client", "Voiture", "Date");

    for (int i = 0; i < nombreLocations; i++) {
        printf("%-20s %-20s %-20s\n", locations[i].client, locations[i].voiture, locations[i].date);
    }
}

void retourVoitureReclamation() {
    char nomClient[MAX_DESCRIPTION];
    int found = 0;

    printf("Entrez votre nom : ");
    scanf("%s", nomClient);

    for (int i = 0; i < nombreLocations; i++) {
        if (strcmp(locations[i].client, nomClient) == 0) {
            printf("Voiture louée : %s\n", locations[i].voiture);
            printf("Date de location : %s\n", locations[i].date);

            for (int j = 0; j < nombreVoitures; j++) {
                if (strcmp(voitures[j].marque, locations[i].voiture) == 0) {
                    voitures[j].disponible = 1;
                    found = 1;
                    break;
                }
            }

            for (int k = i; k < nombreLocations - 1; k++) {
                locations[k] = locations[k + 1];
            }

            nombreLocations--;

            printf("Retour de la voiture effectué avec succès.\n");
            break;
        }
    }

    if (!found) {
        printf("Aucune location en cours pour le client %s.\n", nomClient);
    }
}

void tacheSupplementaire() {
   float coutTotal = 0;

    for (int i = 0; i < nombreClients; i++) {
        coutTotal = 0;

        for (int j = 0; j < nombreLocations; j++) {
            if (strcmp(locations[j].client, coutClients[i].client) == 0) {
                for (int k = 0; k < nombreVoitures; k++) {
                    if (strcmp(voitures[k].marque, locations[j].voiture) == 0) {
                        coutTotal += voitures[k].prix_journalier;
                        break;
                    }
                }
            }
        }

        coutClients[i].coutTotal = coutTotal;

        printf("Client : %s, Cout Total : %.2f EUR\n", coutClients[i].client, coutClients[i].coutTotal);
    }

    if (nombreClients == 0) {
        printf("Aucun client n'a effectué de location.\n");
    }
}

int main() {

    // Ajouter qlq voitures au tableau
    strcpy(voitures[nombreVoitures].marque, "Volvo");
    strcpy(voitures[nombreVoitures].modele, "EX90");
    voitures[nombreVoitures].annee = 2015;
    voitures[nombreVoitures].prix_journalier = 150;
    voitures[nombreVoitures].disponible = 1;
    voitures[nombreVoitures].en_panne = 0;
    nombreVoitures++;

    strcpy(voitures[nombreVoitures].marque, "Skoda");
    strcpy(voitures[nombreVoitures].modele, "Fabia");
    voitures[nombreVoitures].annee = 2010;
    voitures[nombreVoitures].prix_journalier = 100;
    voitures[nombreVoitures].disponible = 1;
    voitures[nombreVoitures].en_panne = 1;
    nombreVoitures++;

    strcpy(voitures[nombreVoitures].marque, "Kia");
    strcpy(voitures[nombreVoitures].modele, "Picanto");
    voitures[nombreVoitures].annee = 2011;
    voitures[nombreVoitures].prix_journalier = 90;
    voitures[nombreVoitures].disponible = 1;
    voitures[nombreVoitures].en_panne = 0;
    nombreVoitures++;

    strcpy(voitures[nombreVoitures].marque, "Renault");
    strcpy(voitures[nombreVoitures].modele, "Espace vi");
    voitures[nombreVoitures].annee = 2013;
    voitures[nombreVoitures].prix_journalier = 220;
    voitures[nombreVoitures].disponible = 0;
    voitures[nombreVoitures].en_panne = 0;
    nombreVoitures++;

    strcpy(voitures[nombreVoitures].marque, "Citroen");
    strcpy(voitures[nombreVoitures].modele, "C3");
    voitures[nombreVoitures].annee = 2010;
    voitures[nombreVoitures].prix_journalier = 180;
    voitures[nombreVoitures].disponible = 1;
    voitures[nombreVoitures].en_panne = 0;
    nombreVoitures++;

    strcpy(voitures[nombreVoitures].marque, "Wolkswagen");
    strcpy(voitures[nombreVoitures].modele, "Golf sw");
    voitures[nombreVoitures].annee = 2010;
    voitures[nombreVoitures].prix_journalier = 200;
    voitures[nombreVoitures].disponible = 1;
    voitures[nombreVoitures].en_panne = 0;
    nombreVoitures++;

    int choix;

    do {
        // Afficher le menu
        printf("\n===== Menu E-Cars =====\n");
        printf("1. Louer une voiture\n");
        printf("2. Afficher la description d'une voiture\n");
        printf("3. Supprimer une voiture en panne\n");
        printf("4. Modifier la description et l'etat d'une voiture\n");
        printf("5. Afficher l'historique des locations\n");
        printf("6. Retour d'une voiture en cas de reclamation\n");
        printf("7. Tache supplementaire\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        // Exécuter la fonction correspondant au choix de l'utilisateur
        switch (choix) {
            case 1:
                louerVoiture();
                break;
            case 2:
                afficherDescription();
                break;
            case 3:
                supprimerVoiturePanne();
                break;
            case 4:
                modifierVoiture();
                break;
            case 5:
                afficherHistoriqueLocations();
                break;
            case 6:
                retourVoitureReclamation();
                break;
            case 7:
                tacheSupplementaire();
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez choisir une option valide.\n");
        }
    } while (choix != 0);

    return 0;
}
