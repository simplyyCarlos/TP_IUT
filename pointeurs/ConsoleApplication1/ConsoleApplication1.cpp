#include <iostream>
#include <ctime>
using namespace std;
const char voyelle[6] = { 'a','e','i','o','u','y'};

void compte(char ch[], int& voy, int& cons) {
	int j=0, i = 0; bool check = true;
	while (ch[j] != '\0') {
		if (ch[j] != ' ') {
			check = true;
			for (i = 0; i < 6; i++) {
				if (ch[j] == voyelle[i]) {
					voy++;
					check = false;
				}
			}
			if (check == true) {
				cons++;
			}
			
		}
		j++;
	}
}

void compte_(char ch[], int* pvoy, int* pcons) {
	int j = 0, i = 0; bool check = true;
	*pvoy = 0; *pcons = 0;
	while (ch[j] != '\0') {
		if (ch[j] != ' ') {
			check = true;
			for (i = 0; i < 6; i++) {
				if (ch[j] == voyelle[i]) {
					(*pvoy)++;
					check = false;
				}
			}
			if (check == true) {
				(*pcons)++;
			}

		}
		j++;
	}
}

void min_max(int* tab, int taille, int* pmin, int* pmax) {
	int i;
	*pmin = *tab; *pmax = *tab;
	for (i = 0; i < taille; i++) {
		if (*(tab + i) >= *pmax) {
			*pmax = *(tab + i);
		}
		else if ((*tab)+i <= *pmin) {
			*pmin = *(tab + i);
		}
	}

}

void init_alea(int *ch, int taille) {
	srand(time(NULL));
	for (int i = 0; i < taille; i++) {
		*(ch + i) = 1+ rand()%5;
	}
}



int main() {
	int min, max;
	const int N = 15;
	int ch[N];
	init_alea(ch, N);
	min_max(ch, N, &min, &max);
	cout << "\nLe minimum est " << min << "\nLe maximum est " << max << endl;
}

