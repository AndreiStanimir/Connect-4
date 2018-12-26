#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <time.h>
#define WIDTH 7
#define HEIGHT 6 
#define ID_PLAYER 1
#define ID_CALCULATOR 2
#define MAXDEPTH 10
using namespace std;

const int mutari[] = { 3,2,4,1,5,0,6 }; //Explorez mai intai mutarile din mijloc, deoarece ,in general,acestea sunt mai bune

class Pozitie
{
public:
	Pozitie();

	int matrice[HEIGHT][WIDTH];
	int lungime[WIDTH];
	int moves;

	bool EsteValida(int mutare)
	{
		if (lungime[mutare] == HEIGHT)
			return false;
		if (mutare < 0)
			return false;
		if (mutare >= WIDTH)
			return false;
		return true;
	}

	void Muta(int mutare)
	{
		int jucator = 1 + moves % 2;
		matrice[lungime[mutare]][mutare] = jucator;
		lungime[mutare]++;
		moves++;
	}

	void Undo(int mutare)
	{
		lungime[mutare]--;
		matrice[lungime[mutare]][mutare] = 0;
		moves--;
	}
	int CeaMaiLungaConexiune(int pozitieC)
	{
		int pozitieL = lungime[pozitieC] - 1;
		int jucator = matrice[pozitieL][pozitieC];
		int orizontala = 1;
		int verticala = 1;
		int diagonala1 = 1;
		int diagonala2 = 1;
		for (int i = pozitieL; i + 1 < HEIGHT; i++)
		{
			if (matrice[i + 1][pozitieC] == jucator)
				verticala++;
			else break;
		}
		for (int i = pozitieL; i - 1 >= 0; i--)
		{
			if (matrice[i - 1][pozitieC] == jucator)
				verticala++;
			else break;
		}

		for (int i = pozitieC; i + 1 < WIDTH; i++)
		{
			if (matrice[pozitieL][i + 1] == jucator)
				orizontala++;
			else break;
		}
		for (int i = pozitieC; i - 1 >= 0; i--)
		{
			if (matrice[pozitieL][i - 1] == jucator)
				orizontala++;
			else break;
		}
		//diagonala1
		for (int i = pozitieL, j = pozitieC; i + 1 < HEIGHT&& j + 1 < WIDTH; i++, j++)
		{
			if (matrice[i + 1][j + 1] == jucator)
				diagonala1++;
			else break;
		}
		for (int i = pozitieL, j = pozitieC; i - 1 >= 0 && j - 1 >= 0; i--, j--)
		{
			if (matrice[i - 1][j - 1] == jucator)
				diagonala1++;
			else break;
		}
		//diagonala2
		for (int i = pozitieL, j = pozitieC; i + 1 < HEIGHT&& j - 1 >= 0; i++, j--)
		{
			if (matrice[i + 1][j - 1] == jucator)
				diagonala2++;
			else break;
		}
		for (int i = pozitieL, j = pozitieC; i - 1 >= 0 && j + 1 < WIDTH; i--, j++)
		{
			if (matrice[i - 1][j + 1] == jucator)
				diagonala2++;
			else break;
		}
		return max(max(orizontala, verticala), max(diagonala1, diagonala2));
	}
	bool EsteCastigatoare(int mutare)
	{
		int jucator = 1 + (moves) % 2;
		Muta(mutare);
		if (CeaMaiLungaConexiune(mutare) >= 4) {
			Undo(mutare);
			return true;
		}
		Undo(mutare);
		return false;
	}
	void Afiseaza()
	{
		for (int i = HEIGHT - 1; i >= 0; i--)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				cout << matrice[i][j] << " ";
			}
			cout << endl;
		}
		cout << "~~~~~~~~~~~~~~~~~~~~\n";
	}
	bool MaiSuntMutariValide()
	{
		return moves < WIDTH*HEIGHT;
		for (int i = 0; i < WIDTH; i++)
		{
			if (matrice[HEIGHT - 1][i] == 0)
				return true;
		}
		return false;
	}
private:

};

Pozitie::Pozitie()
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			matrice[i][j] = 0;
	for (int j = 0; j < WIDTH; j++)
		lungime[j] = 0;
	moves = 0;
}

/*
int MutareOptima(int jucator)
{
int mutareOptima = 3;
int valoareMutareOptima = 1;
for (int i = 0; i < WIDTH; i++)
{
if (EsteValida(i)) {
Muta(i, jucator);

int valoareMutare = CeaMaiLungaConexiune(i, jucator);

//if (valoareMutare == 4)
//return i;
if (valoareMutare > valoareMutareOptima)
mutareOptima = i,
valoareMutareOptima = valoareMutare;
Undo(i);
}
}
return mutareOptima;
}

int ContraCalculator()
{
int mutare = MutareOptima(ID_PLAYER);
return mutare;
}
int MutareCalculator()
{
int mutareCalculator = MutareOptima(ID_CALCULATOR);
Muta(mutareCalculator, ID_CALCULATOR);
if (EsteCastigatoare(mutareCalculator, ID_CALCULATOR))
{
Undo(mutareCalculator);
return mutareCalculator;
}
//prevad urmatoarea mutare
int mutareOptimaJucator = MutareOptima(ID_PLAYER);
Muta(mutareOptimaJucator, ID_PLAYER);
if (EsteCastigatoare(mutareOptimaJucator, ID_PLAYER) && mutareCalculator != mutareOptimaJucator)
{	// Aleg o mutare diferita
Undo(mutareOptimaJucator);
Undo(mutareCalculator);
mutareCalculator = ContraCalculator();
}
else {
Undo(mutareOptimaJucator);
Undo(mutareCalculator);
}
return mutareCalculator;
}
*/

int EvalueazaEuristic(Pozitie p)
{
	return 0; // "evaluare"
}

int AlphaBetaPruning(Pozitie &p, int alpha, int beta, int depth)
{
	if (depth > MAXDEPTH)
		return EvalueazaEuristic(p);
	//	return alpha;
	if (!p.MaiSuntMutariValide())
		return 0; // remiza
				  //Verific daca jucatorul poate castiga intr-o singura mutare
	for (int i = 0; i < WIDTH; i++)
		if (p.EsteValida(mutari[i]))
			if (p.EsteCastigatoare(mutari[i]))
				return (WIDTH*HEIGHT + 1 - p.moves) / 2;
	int max = (WIDTH*HEIGHT - 1 - p.moves) / 2;
	if (beta > max) {
		beta = max;
		if (alpha >= beta)
			return beta;
	}
	// Incerc toate mutarile
	for (int i = 0; i < WIDTH; i++)
		if (p.EsteValida(mutari[i]))
		{
			Pozitie p2(p);

			p2.Muta(mutari[i]);
			int score = -AlphaBetaPruning(p2, -beta, -alpha, depth + 1);
			if (score >= beta)
				return score;
			if (score > alpha)
				alpha = score;
		}
	return alpha;
}

int AlegeMutareaOptima(Pozitie &p, bool solutieSlaba)
{
	int score;
	int bestScore = -40;
	int bestMove = 7;
	//evaluez toate mutarile si o aleg pe cea mai buna
	for (int i = 0; i < WIDTH; i++)
	{
		Pozitie p2(p);
		if (!p2.EsteValida(mutari[i]))
			continue;
		if (p2.EsteCastigatoare(mutari[i])) {
			//cout << "Ai: Casting intr-o mutare" << "\n";
			return mutari[i];
		}
		else
			p2.Muta(mutari[i]);
		if (solutieSlaba)
			score = -AlphaBetaPruning(p2, -1, 1, 0);
		else
			score = -AlphaBetaPruning(p2, -WIDTH*HEIGHT / 2, WIDTH*HEIGHT / 2, 0);
		//cout << score << " ";
		if (bestScore < score)
			bestScore = score,
			bestMove = mutari[i];
	}

	while (!p.EsteValida(bestMove)) {
		cout << "random \n";
		bestMove = rand() % 7;
	}
	if (bestScore > 0)
		cout << "Calculatorul castiga in maxim " << -(bestScore * 2 - WIDTH*HEIGHT - 1) - p.moves << " mutari " << endl;
	else if (bestScore < 0)
		cout << "Jucatorul poate castiga in maxim" << -(-bestScore * 2 - WIDTH*HEIGHT - 1) - p.moves << " mutari" << endl;
	return bestMove;
}

int MutaJucatorul(Pozitie &p, int &mutare, int &retflag);

int MutaCalculatorul(int &mutare, Pozitie &p, bool &retflag);

int main()
{
	srand(1);
	int mutare;
	Pozitie p = Pozitie();
	p.Afiseaza();
	while (true)
	{
		int retflag;
		int retval = MutaJucatorul(p, mutare, retflag);
		if (retflag == 3) continue;
		if (retflag == 1) return retval;
		//bool retflag1;
		//int retval = MutaCalculatorul(mutare, p, retflag1);
		//if (retflag1) return retval;

		p.Afiseaza();
		//mutare = p.MutareCalculator();
		bool retflag1;
		retval = MutaCalculatorul(mutare, p, retflag1);
		if (retflag1) return retval;
		p.Afiseaza();
	}

}

int MutaCalculatorul(int &mutare, Pozitie &p, bool &retflag)
{
	retflag = true;
	mutare = AlegeMutareaOptima(p, 0);
	p.Muta(mutare);
	cout << "Mutare calculator: " << mutare << endl;;
	if (p.CeaMaiLungaConexiune(mutare) >= 4) {
		p.Afiseaza();
		cout << "Castigator este calculatorul" << endl;
		return 1;
	}
	retflag = false;
	return {};
}

int MutaJucatorul(Pozitie &p, int &mutare, int &retflag)
{
	retflag = 1;
	if (!p.MaiSuntMutariValide()) {
		cout << "Remiza";
		return 0;
	}

	cout << "Introduceti mutare:";
	cin >> mutare;
	if (!p.EsteValida(mutare)) {
		cout << "Introduce un numar intre 0 si 6\n";
		{ retflag = 3; return {}; };
	}
	p.Muta(mutare);
	if (p.CeaMaiLungaConexiune(mutare) >= 4) {
		p.Afiseaza();
		cout << "Castigator este jucatorul" << endl;
		return 1;
	}
	
	retflag = 0;
	return {};
}	