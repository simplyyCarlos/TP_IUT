#include <iostream>
#include "TP4.h"
#include <fstream>
using namespace std;


void initHoraire(Horaire& horaire, int h, int m) {
	horaire.h = h;
	horaire.m = m;
}


int horComp(Horaire& h1, Horaire& h2) {
	if (h1.h == h2.h && h1.m == h2.m) {
		return 0;
	}
	else if (h1.h < h2.h || (h1.h < h2.h && h1.m < h2.m) ) {
		return -1;
	}
	else {
		return 1;
	}
}

void initDate(Date& date, int j, int m, int a) {
	date.jour = j;
	date.mois = m;
	date.annee =a;
}

int dateComp(Date& d1, Date& d2) {
	if (d1.jour == d2.jour && d1.mois == d2.mois && d1.annee == d2.annee) {
		return 0;
	}
	else if (d1.annee < d2.annee || (d1.annee == d2.annee && d1.mois < d2.mois)||(d1.annee == d2.annee && d1.mois == d2.mois && d1.jour < d2.jour)) {
		return -1;
	}
	else {
		return 1;
	}
}


void initEvenement(Evenement& e, const char titre[], int jour, int mois, int annee, int heure_debut, int minute_debut, int duree) {
	strcpy_s(e.titre, titre);
	e.date.jour = jour;e.date.mois = mois;e.date.annee = annee;
	e.horaire.h = heure_debut;e.horaire.m = minute_debut;
	e.duree = duree;
}


void initEvenement(Evenement& e, const char titre[], int jour, int mois, int annee, int heure_debut, int minute_debut, int heure_fin, int minute_fin) {
	if (heure_debut <= heure_fin || heure_debut == heure_fin && minute_debut <= minute_fin) {
		strcpy_s(e.titre, titre);
		e.date.jour = jour; e.date.mois = mois; e.date.annee = annee;
		e.horaire.h = heure_debut; e.horaire.m = minute_debut;
		e.duree = (heure_fin * 60 + minute_fin) - (heure_debut * 60 + minute_debut);
	}
}


void afficheEvenement(Evenement& e) {
	cout <<endl<< e.titre << endl;
	cout <<"Date : " << e.date.jour << "/" << e.date.mois << "/" << e.date.annee << endl;
	cout << "Horaire : " << e.horaire.h << "h" << e.horaire.m << endl;
	cout << "Duree : " << e.duree<< " minutes \n";
}


void copieEvenement(Evenement& dest, Evenement& source) {
	strcpy_s(dest.titre, source.titre);
	dest.horaire.h = source.horaire.h; dest.horaire.m = source.horaire.m;
	dest.duree = source.duree;
	dest.date.jour = source.date.jour; dest.date.mois = source.date.mois; dest.date.annee = source.date.annee;
}

bool ajouterEvenement(Evenement agenda[], int& compteur, Evenement& e) {
	if (compteur == TAILLE) {
		return false;
	}
	if (compteur == 0) {
		copieEvenement(agenda[0], e);
		compteur++;
		return true;
	}
	int i =0;
	int min = agenda[i].horaire.h * 60 + agenda[i].horaire.m;
	int _min = e.horaire.h*60+ e.horaire.m;
	int fin = agenda[i].horaire.h * 60 + agenda[i].horaire.m + agenda[i].duree;
	int _fin = e.horaire.h * 60 + e.horaire.m + e.duree;
	for (i = 0; i < compteur; i++) {
		if (dateComp(e.date, agenda[i].date) == 0) {
			if (!(_fin <min || _min > fin)) {
				return false;
			}
		}
	}
	copieEvenement(agenda[compteur], e);
	compteur++;
	return true;
	
}


void afficheAgenda(Evenement agenda[], int compteur) {
	for (int i = 0; i < compteur; i++) {
		afficheEvenement(agenda[i]);
	}
}

void exportHTML(Evenement agenda[], int compteur, const char nom_fichier[]){
	ofstream sortie(nom_fichier, ios::out);
	char mois [12][20] = { " janvier "," fevrier "," mars "," avril "," mai "," juin "," juillet "," aout "," septembre "," octobre "," novembre "," decembre " };
	sortie << "<html>\n<head><title>MON AGENDA PERSONNEL</title></head>\n<body>\n<h1><center>MON AGENDA PERSONNEL</center></h1>\n<table border = '1'><tr>\n<th>Date</th>\n<th>Nom</th>\n<th>Heure debut</th>\n<th>Heure fin</th><br/>\n</tr>\n";
	for (int i = 0; i < compteur; i++) {
		int finh = agenda[i].horaire.h;
		int finm = agenda[i].horaire.m;
		sortie << "<tr>\n<td>";
		if (agenda[i].date.jour < 10) {
			sortie << "0";
		}
		sortie << agenda[i].date.jour << mois[agenda[i].date.mois-1] << agenda[i].date.annee << "</td>\n";
		sortie << "<td>" << agenda[i].titre << "</td>\n";
		sortie << "<td>";
		if (agenda[i].horaire.h < 10)
			sortie << "0";
		sortie << agenda[i].horaire.h << ":";
		if (agenda[i].horaire.m < 10) 
			sortie << "0";
		sortie << agenda[i].horaire.m << "</td>\n";
		sortie << "<td>" << finh << ":" << finm << "</td>\n";
	}	
}

int main() {
	Evenement t[TAILLE];
	Evenement e;
	Date date;
	int n = 0;
	initEvenement(e, "Soiree reveillon", 1, 1, 2017, 1, 0, 9, 0);
	ajouterEvenement(t, n, e);
	initEvenement(e, "RDV medecin", 12, 10, 2016, 8, 0, 120);
	ajouterEvenement(t, n, e);
	initEvenement(e, "TP algo", 12, 11, 2016, 14, 0, 120);
	ajouterEvenement(t, n, e);
	initEvenement(e, "Soutien", 12, 11, 2016, 11, 0, 90);
	ajouterEvenement(t, n, e);
	initEvenement(e, "Resto avec Pauline", 12, 11, 2016, 12, 45, 14, 0);
	ajouterEvenement(t, n, e);
	initEvenement(e, "CM Reseau", 11, 12, 2016, 11, 0, 90);
	ajouterEvenement(t, n, e);


	//ne doit pas s'ajouter (recouvrement avec rdv medecin)
	initEvenement(e, "erreur3", 12, 10, 2016, 9, 0, 30);
	ajouterEvenement(t, n, e);
	//ne doit pas s'ajouter (recouvrement avec rdv medecin)
	initEvenement(e, "erreur4", 12, 10, 2016, 9, 0, 120);
	ajouterEvenement(t, n, e);
	//ne doit pas s'ajouter (recouvrement avec rdv medecin)
	initEvenement(e, "erreur5", 12, 10, 2016, 7, 0, 120);
	ajouterEvenement(t, n, e);
	//ne doit pas s'ajouter (recouvrement avec rdv medecin)
	initEvenement(e, "erreur6", 12, 10, 2016, 7, 0, 240);
	ajouterEvenement(t, n, e);

	initEvenement(e, "Resto avec Alain", 12, 8, 2017, 12, 45, 14, 0);
	ajouterEvenement(t, n, e);
	initEvenement(e, "Repas grand maman", 1, 1, 2017, 12, 0, 110);
	ajouterEvenement(t, n, e);
	afficheAgenda(t,n);
	exportHTML(t,n,"index.html");
	return 0;
}