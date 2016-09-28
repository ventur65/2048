/** @file
* File contenente l'interfaccia del modulo Gioco.
* @author Andrea Venturi
*/

/* Inizio interfaccia modulo Gioco */

/** Funzione che inizia una nuova partita.
*
* Invoca la funzione ::inizializza_mappa per pulire la matrice di gioco.
* Setta GameOver e Vittoria a false, Punteggio a 0.
* @param[in] mappa Matrice della mappa di gioco.
*/
void libera_mappa(int mappa[][DIM]) ;

/** Funzione che inserisce un numero (2 o 4) nella mappa di gioco in una casella
* libera casuale.
* 
* Se le caselle libere sono maggiori di 15, allora gli inserimenti saranno 2.
* Si vedano le documentazioni delle funzioni ::quante_libere, ::cerca_libera
* e ::quale_numero per maggiori informazioni.
* 
* @param[in] mappa Matrice della mappa di gioco.
* @return true in caso di inserimento/i effettuati con successo, false altrimenti.
*/
bool inserisci_random(int mappa[][DIM]) ;

/** Funzione che controlla se si è giunti a GameOver.
* 
* Da invocarsi dopo ogni mossa o caricamento.
* Controlla se, per ogni casella, le caselle adiacenti hanno valore uguale (in tal
* caso, vi sarebbero ancora mosse disponibili e non si arriverebbe al GameOver).
* Controlla inoltre che non ci siano caselle libere.
*
* @param[in] mappa Matrice della mappa di gioco.
* @return true se si è in stato di GameOver, false altrimenti.
*/
bool Controlla_GameOver(const int mappa[][DIM]) ;

/** Funzione che controlla se si è giunti alla vittoria.
*
* Scorre la mappa in cerca di una casella con valore 2048.
* Da invocarsi dopo ogni mossa o caricamento.
*
* @param[in] mappa Matrice della mappa di gioco
* @return true in caso di vittoria, false altrimenti.
*/
bool controlla_vittoria(int mappa[][DIM]) ;

/** Funzione che fa gli spostamenti e le somme nelle varie direzioni.
*
* Invocata dopo che l'utente ha premuto il tasto per lo spostamento verso una
* direzione.
* Sfrutta 3 cicli for innestati per ogni direzione di spostamento.
* I primi due servono per scorrere tutte le caselle (i è sempre il contatore di riga,
* mentre j di colonna. 
* Il terzo (quello su k) è il ciclo che itera su tutte le caselle successive 
* (le chiameremo caselle "iteratore") a quella corrente (selezionata dai cicli
* precedenti) nella direzione desiderata.
* In caso di casella "iteratore" vuota, il ciclo iteratore avanza senza fare niente
* (primo if).
* Nel caso, invece, in cui trova una casella "iteratore" con lo stesso valore della  
* corrente, si esegue la somma tra le due (eseguito moltiplicando per 2 la casella
* corrente),  si aggiorna il punteggio, sommandogli il nuovo valore della casella
* corrente, si pone la casella "iteratore" a 0 (vuota) e si interrompe il ciclo
* iteratore, causando l'avanzamento della casella corrente. (Secondo if).
* Altrimenti, se la casella corrente è 0 (vuota), mentre quella "iteratore" no, 
* si deve semplicemente effettuare lo scorrimento (terzo if). Si procede quindi
* a porre la casella corrente uguale a quella "iteratore", e si pone quest'ultima a 
* 0 (vuota). E' necessario però ripetere i controlli effettuati in precedenza perchè
* si è effettuato uno spostamento: questo è ottenuto aumentando/diminuendo il contatore di
* righe/colonne a seconda della direzione.
* Per ultimo (quarto if) se le due caselle sono diverse non si deve far altro che
* interrompere il ciclo iteratore.
* Si consiglia la visione del codice sorgente parallelamente a questa documentazione.
*
* @param[in] mappa Matrice della mappa di gioco
* @param[in] direzione Direzione verso la quale effettuare le somme/spostamenti
*/
void fai_somme (int mappa[][DIM], direzione_t direzione) ;

/* Fine interfaccia modulo Gioco */
