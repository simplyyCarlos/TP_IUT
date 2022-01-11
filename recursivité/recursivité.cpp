#include <iostream>
using namespace std; 

int t[30] = { 21,-432,-77,84,91,74,45,899,301,2,-1,-987,-456,87,745,79,-4,-56,754,32,145,156,54,-2,-89,963,71,-222,-333,7 };
const int N = 4;
const int v[N + 1] = { 0,1,2,5,10 };
int S = 14;
int pgcd(int a, int b, int& compteur) {
	compteur++;
	if (b==0 || a % b == 0) {
		return b;
	}
	return pgcd(b, a % b,compteur);
}

void tri_selectif(int tab[]) {
	int min, i = 0, ind, tmp;
	while (i != 30) {
		min = tab[i];
		for (int j = i; j < 30; j++) {
			if (tab[j] < min) {
				min = tab[j];
				ind = j;
			}
		}
		tmp = tab[i];
		tab[i] = min; tab[ind] = tmp;
		i++;
	}
}

void affiche(int tab[]) {
	for (int j = 0; j < 30; j++) {
		cout << tab[j]<< ",";
	}
}

int recherche_dicho(int t[], int v, int indice_debut, int indice_fin){
	if (indice_fin - indice_debut >= 0) {
		int i1 = (indice_debut + indice_fin) / 2;
		if (t[i1] == v) {
			return i1;
		}
		else if (t[i1]>v) {
			recherche_dicho(t, v, indice_debut, i1 - 1);
		}
		else {
			recherche_dicho(t, v, i1 + 1, indice_fin);
		}
	}
	else {
		return -1;
	}
}

int monnaie() {

}

int main() {
	int compteur;
	/*
	int var, max = -1, bmax = 0;
	for (int j = 2; j < 243;j++) {
		compteur = 0;
		pgcd(244, j,compteur);
		if (compteur > max) {
			bmax = j;
			max = compteur;
		}
	}
	cout << bmax;
	*/
	tri_selectif(t);
	affiche(t);
	cout << endl <<recherche_dicho(t,963,0,29);
}