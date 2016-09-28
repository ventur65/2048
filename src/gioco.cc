/**@file 
* File contenente il modulo Gioco.
* Esso sviluppa la logica di gioco ad esempio gestendo gli spostamenti (funzione ::fai_somme), 
* o l'inserimento di nuovi numeri ::inserisci_random. Sono inoltre presenti le funzioni di controllo di gameover e di vittoria
* (::Controlla_GameOver e ::controlla_vittoria).
*
* @author Andrea Venturi
*/

#include <iostream>
#include <cassert>
#include <cstdlib> 
#include <allegro5/allegro.h>

#include "strutt_dati.h"
#include "gioco.h"

using namespace std;

/*Inizio Definizioni modulo Gioco */

/** Inizializzazione mappa di gioco.
*
* Da invocarsi prima di una nuova partita.
* Il valore 0 indica che la casella è vuota.
*
* @param[in] mappa Matrice della mappa di gioco.
*
*/
void inizializza_mappa(int mappa[][DIM])
{
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			mappa[i][j] = 0;
}

/** Funzione che conta quante caselle sono libere.
*
* Da invocarsi per controlli prima di inserire un nuovo numero nella mappa.
*
* @param[in] mappa Matrice della mappa di gioco.
* @return Numero caselle libere.
*/
int quante_libere(const int mappa[][DIM])
{
	int libere = 0;
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			if (mappa[i][j] == 0)
				libere++;
	
	DBG(cout<<"Libere trovate: "<<libere<<endl);
	return libere;
}

/**Cerca una casella libera random. 
* 
* Ricerca una casella libera randomicamente. Serve per l'inserimento di numeri
* random. Effettua i controlli sul numero di caselle libere tramite l'invocazione
* di ::quante_libere (se sono 0 non si può fare l'inserimento).
* @param[in] mappa Matrice della mappa di gioco.
* @param[out] i Indice di riga della casella libera se trovata.
* @param[out] j Indice di colonna della casella libera se trovata.
* @return true se la ricerca è andata a buon fine, false altrimenti.
*/
bool cerca_libera (const int mappa[][DIM], int &i, int &j)
{
	if (quante_libere(mappa) == 0) {
		i = -1;
		j = -1;
		return false;
	}
	
	bool trovato = false;
	assert(quante_libere(mappa)!=0);
	while(!trovato) {
		i = rand()%4;
		j = rand()%4;
		DBG(cout<<"mappa["<<i<<"]"<<"["<<j<<"]: "<<mappa[i][j]<<endl);
		if (mappa[i][j] == 0) {
			assert(mappa[i][j] == 0);
			DBG(cout<<"i e j trovati da cerca_libera: "<<i<<" "<<j<<endl);
			trovato = true; 
		}
	}
	return true;
}
/** Funzione che ritorna 2 o 4.
*
* Funzione di supporto per l'inserimento casuale di numeri nella mappa di gioco.
* 80% di probabilità che ritorni 2, 20% che ritorni 4.
*
* @return 2 o 4.
*/
int quale_numero()
{
	if (rand()%100 <= 80)
		return 2;
	else
		return 4;
}

void libera_mappa(int mappa[][DIM])
{
	inizializza_mappa(mappa);
	
	GameOver = false;
	Vittoria = false;
	Punteggio = 0;
}

bool inserisci_random(int mappa[][DIM])
{
	int i = 0, j = 0;
	int libere = quante_libere(mappa);
	if (libere == 0)
		return false;
	
	assert(libere != 0);
	int inserimenti;
	libere > 10 ? inserimenti = 2 : inserimenti = 1;
	DBG(cout<<"Numero Inserimenti: "<<inserimenti<<endl);
	
	while (inserimenti > 0) {
		if (!cerca_libera(mappa, i, j))
			return false;

		DBG(cout<<"i dopo cerca_libera: "<<i<<endl);
		DBG(cout<<"j dopo cerca_libera: "<<j<<endl);
	
		int numero = quale_numero();
		DBG(cout<<"Effettuato inserimenti di "<<numero<<" in mappa["<<i<<"]["<<j<<"]"<<endl);
		assert(mappa[i][j] == 0); //Assicuro che l'inserimento avvenga in una casella libera
		mappa[i][j] = numero;
		inserimenti--;
	}

	return true;
}

bool Controlla_GameOver(const int mappa[][DIM])
{
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			if (i-1 >= 0) {
				if (mappa[i-1][j] == mappa[i][j])
					return false;
			}
			if (i+1 < DIM) {
				if (mappa[i+1][j] == mappa[i][j])
					return false;
			}
			if (j-1 >= 0) {
				if (mappa[i][j-1] == mappa[i][j])
					return false;
			}
			if (j+1 < DIM) {
				if (mappa[i][j+1] == mappa[i][j])
					return false;
			}
			if (mappa[i][j] == 0)
				return false;
		}
	}
	
	return true;
}

bool controlla_vittoria(int mappa[][DIM])
{
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			if (mappa[i][j] == 2048) {
				DBG(cout<<"Trovato 2048"<<endl);
				return true;
			}
	
	DBG(cout<<"Nessun 2048 trovato"<<endl);
	return false;
}

void fai_somme (int mappa[][DIM], direzione_t direzione)
{
	switch (direzione) {
		case SU:
			for (int j = 0; j < DIM; j++) {
				for (int i = 0; i < DIM; i++) {
					for (int k = i+1; k < DIM; k++) {
						//Caso in cui la casella "iteratore" è vuota. (primo if)
						if (mappa[k][j] == 0)
							continue;
						//Caso in cui devo fare la somma. (secondo if)
						else if (mappa[i][j] == mappa[k][j]) {
							mappa[i][j] *= 2;
							Punteggio += mappa[i][j];
							mappa[k][j] = 0;
							break;
						}
						else {
							//Caso in cui devo semplicemente scorrere.
							//i-- necessario per fare ricominciare i controlli
							//dopo lo spostamento.
							//Non accedo fuori da array anche se i = 0
							//perchè con il break l'istruzione successiva è i++.
							//(terzo if)
							if (mappa[i][j] == 0 && mappa[k][j] != 0) {
								mappa[i][j] = mappa[k][j];	
								mappa[k][j] = 0;
								i--;
								break;
							}
							//Caso in cui sono diversi. (quarto if)
							else if (mappa[i][j] != 0)
								break;	
						}//Fine else
					}//fine for k
				}//Fine for i
			}//Fine for j
			break;

		case SINISTRA:
			for (int i = 0; i < DIM; i++) {
				for (int j = 0; j < DIM; j++) {
					for (int k = j+1; k < DIM; k++) {
						//caso in cui la casella "iteratore" è vuota. (primo if)
						if (mappa[i][k] == 0)
							continue;
						//caso in cui devo fare la somma. (secondo if)
						else if (mappa[i][j] == mappa[i][k]) {
							mappa[i][j] *= 2;
							Punteggio += mappa[i][j];
							mappa[i][k] = 0;
							break;
						}
						else {
							//caso in cui devo semplicemente scorrere.
							//j-- necessario per fare ricominciare i controlli
							//dopo lo spostamento.
							//Non accedo fuori da array anche se j = 0
							//perchè con il break l'istruzione successiva è j++.
							//(terzo if)
							if (mappa[i][j] == 0 && mappa[i][k] != 0){
								mappa[i][j] = mappa[i][k];
								mappa[i][k] = 0;
								j--;
								break;
							}
							//Caso in cui sono diversi. (quarto if)
							else if (mappa[i][j] != 0)
								break;
						}//Fine else
					}//Fine for k
				}//Fine for j
			}//Fine for i
			break;
		
		case GIU:
			for (int j = 0; j < DIM; j++) {
				for (int i = DIM-1; i >= 0; i--) {
					for (int k = i-1; k >= 0; k--) {
						//Caso in cui la casella "iteratore" è vuota. (Primo if)
						if (mappa[k][j] == 0)
							continue;
						//caso in cui devo fare la somma. (secondo if)
						else if (mappa[k][j] == mappa[i][j]) {
							mappa[i][j] *= 2;
							Punteggio += mappa[i][j];
							mappa[k][j] = 0;
							break;
						}
						else {
							//caso in cui devo semplicemente scorrere.
							//i++ necessario per fare ricominciare i controlli
							//dopo lo spostamento.
							//Non accedo fuori da array anche se i = 3
							//perchè con il break l'istruzione successiva è i--.
							//(terzo if)
							if (mappa[i][j] == 0 && mappa[k][j] != 0) {
								mappa[i][j] = mappa[k][j];
								mappa[k][j] = 0;
								i++;
								break;
							}
							//caso in cui sono diversi. (quarto if)
							else if (mappa[i][j] != 0)
								break;
						}//Fine else
					}//Fine for k
				}//Fine for i
			}//Fine for j
			break;

		case DESTRA:
			for (int i = 0; i < DIM; i++) {
				for (int j = DIM-1; j >= 0; j--) {
					for (int k = j-1; k >= 0; k--) {
						//Caso in cui la casella "iteratore" è vuota. (primo if)
						if (mappa[i][k] == 0)
							continue;
						//Caso in cui devo fare la somma. (secondo if)
						else if (mappa[i][j] == mappa[i][k]) {
							mappa[i][j] *= 2;
							Punteggio += mappa[i][j];
							mappa[i][k] = 0;
							break;
						}
						else {
							//caso in cui devo semplicemente scorrere.
							//j++ necessario per fare ricominciare i controlli
							//dopo lo spostamento.
							//Non accedo fuori da array anche se j = 3
							//perchè con il break l'istruzione successiva è j--.
							//(terzo if)
							if (mappa[i][j] == 0 && mappa[i][k] != 0) {
								mappa[i][j] = mappa[i][k];
								mappa[i][k] = 0;
								j++;
								break;	
							}
							//Caso in cui sono diversi. (quarto if)
							else if (mappa[i][j] != 0) {
								break;
							}
						}//Fine else
					}//Fine for k
				}//Fine for j
			}//Fine for i
			break;
	}//Fine switch
	
}

//Fine Definizioni del modulo Gioco
