#include <iostream>
using namespace std;
/*
char lettre_max(char ch[]) {
	int indice;
	int nb[26] = {0};
	for (int i = 0; i <= strlen(ch);i++) {
		if (ch[i] >= 'a' && ch[i] <= 'z') {
			indice = ch[i] - 'a';
			nb[indice]++;
		}
	}
	int max = nb[0], imax = 0;
	for (int i = 1; i < 26; i++) {
		if (nb[i] > max) {
			max = nb[i];
			imax = i;
		}		
	}
	return(imax + 'a');
}

int main() {
	char ch[100];
	cout << "Entrez une chaîne de caracteres"<< endl;
	cin.getline(ch, 100);
	cout << "\nLa lettre qui revient le plus est " << lettre_max(ch);
	return 0;
}

*/


const int N = 3;

void init_carree(int carre[N][N]) {
	bool deja_fourni[N * N+1] = {false};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			do {
				cout << "case " << i + 1 << ", " << j + 1 << " = ";
				cin >> carre[i][j];
			} while (carre[i][j] <1 || carre[i][j] > N * N || deja_fourni[carre[i][j]]!=false);
			deja_fourni[carre[i][j]] = true;
		}
	}
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << carre[i][j]<<" ";
		}
		cout << endl;
	}	
}

bool presque_magique(int carr[N][N]) {
	int sum1 = 0;
	int sum2 = 0;
	int tmp = 0;
	for (int i = 0; i < N; i++) {
		tmp += carr[i][i];
	}
	for (int i = 0; i < N; i++) {
		sum1 = 0; sum2 = 0;
		for (int j = 0; j < N; j++) {
			sum1 += carr[i][j];
			sum2 += carr[j][i];
		}
		if (sum1 != tmp || sum2 != tmp) {
			return false;
		}
	}
	sum1 = 0;
	for (int i = 0; i<N; i++) {
		sum1 += carr[i][N-1-i];
	}
	if (sum1 != tmp) {
		return false;
	}
	return true;
}

bool is_magic(int carr[N][N]) {
	int cpt = 0, nb[N * N] = { 0 };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (carr[i][j] < 1 || carr[i][j] > N * N) {
				return false;
			}
			nb[carr[i][j] - 1]++;
			cpt++;
		}
	}

	for (int i = 0; i < N * N; i++) {
		if (nb[i] < 1) {
			return false;
		}
	}

	if (cpt == N * N && presque_magique(carr)) {
		return true;
	}
	return false;
}

int main() {
	int carree[N][N];
	init_carree(carree);
	cout << is_magic(carree);
	return 0;
}