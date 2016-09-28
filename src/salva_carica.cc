/** @file
* File contenente il modulo Salva/Carica.
* Contiene le funzioni necessarie per il Caricamento e Salvataggio da e su file di testo (::carica e ::salva).
* Sono inoltre presenti le funzioni che mostrano le finestre di dialogo e il filechooser (::save_dialog e ::load_dialog)
*
* @author Andrea Venturi
*/

#include <iostream>
#include <fstream>
#include <allegro5/allegro_native_dialog.h>

#include "strutt_dati.h"
#include "salva_carica.h"

using namespace std;

//Inizio definizioni modulo Salva/Carica

/**Funzione che controlla che il numero letto sia tra quelli corretti per il gioco.
*
* Sfruttata dalla funzione ::carica per la lettura da file di testo.
* @param[in] num Valore da controllare.
* @return true o false in caso di errore trovato o no.
*/
bool controlla_errore(int num)
{
	if (num != 2 && num != 4 && num != 8 && num != 16 && num != 32
		&& num != 64 && num != 128 && num != 256 && num != 512 
		&& num != 1024 && num != 2048)
		return true;
	else return false;

}

/** Salva la mappa e il punteggio su un file di testo.
*
* @param[in] mappa Matrice della mappa di gioco.
* @param[in] nomefile Nome del file in cui salvare la partita.
* @return f stato dello stream una volta terminate le operazioni.
*/
bool salva(int mappa[][DIM], const char nomefile[])
{
	ofstream f(nomefile);
	if (!f) { 
		cerr<<"Errore apertura file"<<endl;
		return false;
	}

	f<<GameOver<<endl;
	f<<Punteggio<<endl;
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			f<<mappa[i][j]<<endl;

	return f;
}

/** Carica la mappa e il punteggio da un file di testo.
*
* @param[in] mappa Matrice della mappa di gioco.
* @param[in] nomefile Nome del file di testo da cui caricare la partita.
* @return f stato dello stream una volta terminate le operazioni.
*/
bool carica(int mappa[][DIM], const char nomefile[])
{
	ifstream f(nomefile);
	if (!f) {
		cerr<<"Errore apertura file"<<endl;
		return false;
	}
	
	f>>GameOver;
	f>>Punteggio;
	int num;
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++) {
			f>>num;
			if (controlla_errore(num))
				mappa[i][j] = 0;
			else 
				mappa[i][j] = num;
		}
	return f;
}

void save_dialog(int mappa[][DIM])
{
	ALLEGRO_FILECHOOSER *fc = al_create_native_file_dialog("../salvataggi/",
								"Salvataggio", "*.txt",
								ALLEGRO_FILECHOOSER_SAVE);
	assert(fc);
	if (al_show_native_file_dialog(display, fc)) {
		int numfile = al_get_native_file_dialog_count(fc);
		if (numfile == 0) { //Utente ha annullato l'operazione.
			al_show_native_message_box(display, "Salvataggio",
				"Salvataggio annullato", "", NULL, ALLEGRO_MESSAGEBOX_WARN);
		}		
		else if (numfile > 1) { //Utente ha scelto più di 1 file.
			al_show_native_message_box(display, "Salvataggio",
				"Seleziona un solo file.", "Il salvataggio sarà annullato.",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
		}
		else if (numfile == 1) { //Utente ha scelto un solo file.
			const char *file = al_get_native_file_dialog_path(fc, 0);
			DBG(cout<<"Nome File: "<<file<<endl);
			if (al_filename_exists(file)) { //Se il file esiste, chiedo se sovrascrivere.
				int button = al_show_native_message_box(display, "File Esistente",
							"File già esistente. Sovrascriverlo?", "", NULL,
							ALLEGRO_MESSAGEBOX_YES_NO);
				if (button != 1) { //Utente annulla operazione.
					al_show_native_message_box(display, "Salvataggio",
						"Salvataggio annullato.", "", NULL, ALLEGRO_MESSAGEBOX_WARN);
					return;
				}
			}
			if (salva(mappa, file)) {
				al_show_native_message_box(display, "Salvataggio",
					"Salvataggio effettuato con successo", "", NULL,
					0);
				//successo = true;
				DBG(cout<<"Salvataggio corretto"<<endl);
			}
			else { //Errore nel salvataggio.
				al_show_native_message_box(display, "Salvataggio",
					"Errore nel salvataggio", "Il salvataggio sarà annullato.",
					NULL, ALLEGRO_MESSAGEBOX_ERROR); 
				DBG(cout<<"Errore nel salvataggio"<<endl);
			}
		}
	}
	
	al_destroy_native_file_dialog(fc); //Deallocazione filechooser
}

bool load_dialog(int mappa[][DIM])
{
	bool successo = false;

	ALLEGRO_FILECHOOSER *fc = al_create_native_file_dialog("../salvataggi/", 
								"Caricamento", "*.txt", 
								ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
	assert(fc);
	if (al_show_native_file_dialog(display, fc)) {
		int numfile = al_get_native_file_dialog_count(fc);
		if (numfile == 0) { //Utente ha annullato l'operazione.
			al_show_native_message_box(display, "Caricamento",
				"Caricamento annullato", "", NULL, ALLEGRO_MESSAGEBOX_WARN);
		}
		else if (numfile > 1) { //Utente ha scelto più di un file.
			al_show_native_message_box(display, "Caricamento",
				"Seleziona un solo file.", "Il caricamento sarà annullato.",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
		}
		else if (numfile == 1) { //Utente ha scelto un file solo.
			const char *file = al_get_native_file_dialog_path(fc, 0);
			DBG(cout<<"Nome File: "<<file<<endl);
			if (carica(mappa, file)) {
				al_show_native_message_box(display, "Caricamento",
					"Caricamento effettuato con successo", "", NULL,
					0);
				successo = true;
				DBG(cout<<"Fatto il caricamento"<<endl);
			}
			else {
				al_show_native_message_box(display, "Caricamento",
					"Errore nel caricamento:",
					"Assicurati che il file scelto abbia il formato giusto.",
					NULL, ALLEGRO_MESSAGEBOX_ERROR);			
				DBG(cout<<"Errore nel caricamento"<<endl);
			}		
		}
	}
	
	al_destroy_native_file_dialog(fc);
	return successo;
}

//Fine definizioni modulo Salva/Carica
