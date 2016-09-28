/**@mainpage 2048
* @section intro_sec Introduzione
* 
* Programma creato come progetto personale per l'esame di Programmazione II del Professor Bertogna del CdL Informatica Unimore.
* Esso si sviluppa in 4 moduli principali:
* - 2048.cc : Contiene il ::main e funzioni per l'inizializzazione e distruzione di allegro e delle sue componenti ::init e ::distruggi.
* - disegno.cc : Modulo sviluppato per tutto cio' che riguarda la resa grafica del gioco. Non contiene alcun tipo di logica di gioco.
* - gioco.cc : Modulo che raccoglie tutte le routine necessarie al gioco per funzionare, come ad esempio la gestione del movimento
* e delle somme ::fai_somme, funzioni di controllo di gameover e vittoria ::Controlla_GameOver ::controlla_vittoria e l'inserimento
* nella mappa di gioco ::inserisci_random.
* - salva_carica.cc : Modulo per le funzioni di caricamento e salvataggio da e su file di testo. 
* 
* Il gioco sfrutta una libreria esterna per la parte grafica <A HREF="http://liballeg.org/">Allegro5</A>.
*
* @section Regolamento
*
* @subsection Obiettivo
* Obiettivo del gioco è raggiungere 2048 in una casella.
*
* @subsection Spostamenti
* La Mappa di gioco consiste in una matrice 4x4 di caselle. Ogni casella può contenere un numero (multiplo di 2) oppure essere vuota.
* All'inizio la mappa avrà solamente 2 caselle occupate.
* L'utente, tramite uso delle frecce direzionali, deciderà come muovere le caselle. Le caselle occupate da un numero
* si muoveranno lungo la direzione specificata finchè non incontrano la fine della mappa oppure un numero diverso.
* Nell'eventualità, invece, che incontrino un numero uguale, si sostituisce al numero più all'esterno la somma dei numeri, al numero più interno una
* casella vuota.
* Esempio: Consideriamo una riga di matrice fatta in questo modo: 2 4 X 4 dove la X è una casella vuota. Supponiamo che l'utente
* prema la freccia destra: il 4, che nella situazione iniziale era in seconda posizione nella riga, avendo alla sua destra una casella vuota
* scorre fino al 4 più esterno (quello in quarta posizione nella riga). Essendo ora il valore delle caselle vicine uguali,
* esse si sommano formando una casella di valore 8 che prende il posto del 4 più a destra. 
* Ora il 2 scorre fin alla terza posizione nella riga: non può più proseguire in quanto la quarta è occupata dal valore 8 (!=2). 
* Dopo lo spostamento a dx la riga avrà quindi questa forma: X X 2 8.
* In seguito ad ogni spostamento, infine, verranno scelte al più due caselle vuote (se ci sono) a caso per l'inserimento di un 2 o un 4 
* (anche questo a random).
*
* @subsection GameOver
* Il GameOver si raggiunge se non ci sono movimenti disponibili nelle 4 direzioni, cioè se non esistono caselle vuote e se nessuna casella
* ne ha una adiacente con lo stesso valore.
*/

/**@file
* File contenente il ::main e funzioni di inizializzazione e di distruzione di allegro e delle sue componenti ::init e ::distruggi.
* @author Andrea Venturi
*/

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include "strutt_dati.h"
#include "gioco.h"
#include "salva_carica.h"
#include "disegno.h"

using namespace std;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue; 

bool GameOver;
bool Vittoria; 
int Punteggio; 

/** Funzione di inizializzazione di allegro e delle sue componenti.
*
*/
void init(void) 
{
	if(!al_init()){
      		cerr<<"Failed to initialize Allegro.\n";
  	}
  	
  	al_init_font_addon(); // initialize the font addon
   	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
   	al_init_image_addon();
   	al_init_native_dialog_addon();
   	
   	display = al_create_display(640,480);
   	assert(display);
   	if (!display){
    	cerr<<"Failed to create display."<<endl;
   	}
   	
   	if (!al_install_keyboard())
        cerr<<"Failed to install keyboard"<<endl;
       
    event_queue = al_create_event_queue();
    assert(event_queue);
    if (!event_queue)
        cerr<<"Failed to create event queue"<<endl;
        
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
}

/** Funzione che dealloca le componenti di allegro usate dal programma.
*
* Invocata in caso di terminazione del programma.
*/
void distruggi(void)
{
	assert(display);
	if (display)
		al_destroy_display(display);
	
	assert(event_queue);
	if (event_queue)
		al_destroy_event_queue(event_queue);
}

/** Funzione principale.
*
* Crea la mappa di gioco come matrice di interi.
* Inizializza la partita iniziale e fa partire il ciclo while del gioco.
* Nel ciclo sono gestiti gli eventi di:
* - movimento (in caso di pressione della frecce direzionali da parte dell'utente),
* tramite la funzione ::fai_somme.
* - salvataggio (in caso l'utente prema S), tramite la funzione ::salva.
* - caricamento (in caso l'utente prema C), tramite la funzione ::carica.
* - nuova partita (in caso l'utente prema R), tramite la funzione ::libera_mappa.
*
* In caso di spostamento/somme viene ridisegnato il display tramite ::update_graphics.
* In caso di GameOver o Vittoria il display viene ridisegnato tramite ::dis_gameover e ::dis_vittoria.
*
*/
int main(int argc, char **argv)
{
	int mappa[DIM][DIM]; //Matrice della mappa di gioco
	libera_mappa(mappa); 
	
	init();
	
	srand(time(0));
	
	inserisci_random(mappa);
	ridisegna_mappa(mappa);
	update_graphics(mappa);
	DBG(cout<<"Mappa ridisegnata"<<endl);

	while(true) {
		
		ALLEGRO_EVENT event;
		bool redraw = false;
        
       	al_wait_for_event(event_queue, &event);
        
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	break;
        }
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP: 
					if(!GameOver && !Vittoria) {
						DBG(cout<<"scelto su"<<endl);
						fai_somme(mappa, SU);
						DBG(cout<<"Fatte le somme"<<endl);
						//Non c'è bisogno di controllare che ci siano caselle libere,
						//perchè lo fa già inserisci_random().
						if (inserisci_random(mappa))
							DBG(cout<<"Fatto inserimento"<<endl);
						redraw = true;
					}
					break;
				case ALLEGRO_KEY_DOWN:
					if (!GameOver && !Vittoria) {
						DBG(cout<<"scelto giu"<<endl);
						fai_somme(mappa, GIU);
						DBG(cout<<"Fatte le somme"<<endl);
						if (inserisci_random(mappa))
							DBG(cout<<"Fatto inserimento"<<endl);
						redraw = true;
					}
					break;
				case ALLEGRO_KEY_LEFT:
					if (!GameOver && !Vittoria) {					
						DBG(cout<<"scelto sx"<<endl);
						fai_somme(mappa, SINISTRA);
						DBG(cout<<"Fatte le somme"<<endl);
						if (inserisci_random(mappa))
							DBG(cout<<"Fatto inserimento"<<endl);
						redraw = true;
					}
					break;
				case ALLEGRO_KEY_RIGHT:
					if (!GameOver && !Vittoria) {					
						DBG(cout<<"scelto dx"<<endl);
						fai_somme(mappa, DESTRA);
						DBG(cout<<"Fatte le somme"<<endl);
						if (inserisci_random(mappa))
							DBG(cout<<"Fatto inserimento"<<endl);
						redraw = true;
					}
					break;
				case ALLEGRO_KEY_R:
					DBG(cout<<"scelto r"<<endl);
					int button;
					button = al_show_native_message_box(display,
								"Ricomincia", "Sei sicuro?",
								"Ogni dato non salvato andrà perso.",
								NULL, ALLEGRO_MESSAGEBOX_YES_NO);
					if (button == 1) {
						libera_mappa(mappa);
						DBG(cout<<"Mappa Liberata: "<<endl; 
						ridisegna_mappa(mappa));
						if (inserisci_random(mappa))
							DBG(cout<<"Fatto inserimento"<<endl);
						redraw = true;
					}
					break;
				case ALLEGRO_KEY_S:
					if (!GameOver && !Vittoria) {
						DBG(cout<<"scelto s"<<endl);
						save_dialog(mappa);
					}
					break;
				case ALLEGRO_KEY_C:
					DBG(cout<<"scelto c"<<endl);
					if (load_dialog(mappa)) {
						redraw = true;
					}
					break;
			}//Fine switch
		}//Fine if

		if (redraw) {
			GameOver = Controlla_GameOver(mappa);
			Vittoria = controlla_vittoria(mappa);
	
			if (GameOver) {
				DBG(cout<<"GameOver"<<endl);
				#ifndef DEBUG_MODE
					system("clear");
				#endif
				cout<<"GAMEOVER"<<endl;
				cout<<"PUNTEGGIO: "<<Punteggio<<endl;
				dis_gameover(mappa);
			}
			else if (Vittoria) {
				DBG(cout<<"Vittoria"<<endl);
				#ifndef DEBUG_MODE
					system("clear");
				#endif
				cout<<"VITTORIA"<<endl;
				cout<<"PUNTEGGIO: "<<Punteggio<<endl;
				dis_vittoria(mappa);
			}
			else {
				ridisegna_mappa(mappa);
				update_graphics(mappa);
				DBG(cout<<"Mappa ridisegnata"<<endl);
			}
		}

	}//Fine While
	
	distruggi();

	return 0;
}
