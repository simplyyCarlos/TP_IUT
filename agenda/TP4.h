#include<iostream>
const int TAILLE=100;

struct Horaire{
	int h,m;
};

struct Date{
	int jour,mois,annee;
};

struct Evenement{
	char titre[50];
	Date date;
	Horaire horaire;
	int duree; //en minutes
};

/***** HORAIRES *****/
void initHoraire(Horaire&horaire, int h, int m);
int horComp(Horaire& h1, Horaire& h2);

/***** DATES *****/
void initDate(Date&d, int j, int m, int a);
int dateComp(Date& d1, Date& d2);

/***** EVENEMENTS *****/
void initEvenement(Evenement&e, const char titre[], int jour, int mois, int annee, int heure_debut, int minute_debut, int duree);
void initEvenement(Evenement&e, const char titre[], int jour, int mois, int annee, int heure_debut, int minute_debut, int heure_fin, int minute_fin);
void afficheEvenement(Evenement&e);
void copieEvenement(Evenement&dest, Evenement&src);

/***** AGENDA *****/
bool ajouterEvenement (Evenement agenda[], int&compteur, Evenement&e) ;
void afficheAgenda(Evenement agenda[], int compteur);
void exportHTML(Evenement agenda[], int compteur, char nom_fichier[]);
bool supprimerEvenement(Evenement agenda[], int& compteur,  char titre[], Date& d);