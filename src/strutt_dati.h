/** @file 
* File contenente dichiarazioni e definizioni di alcune costanti, variabili e strutture dati utili negli altri file.
* 
* @author Andrea Venturi
*/
/* Inizio header modulo Struttura Dati */

/** Tipo direzione per il movimento delle caselle di gioco.
*
* Lo spostamento può avvenire lungo le 4 direzioni.
* Si è optato per gli enumeratori in quanto aumenta la leggibilità al momento del
* passaggio alla funzione ::fai_mosse. Vedere la documentazione di quest'ultima per
* ulteriori dettagli.
*/
enum direzione_t {SU, GIU, DESTRA, SINISTRA};

const int MAXLUN = 100; /**< Lunghezza massima stringhe */
const int DIM = 4; /**< Dimensione mappa di gioco */
extern bool GameOver; /**< Booleano: true se si raggiunge il gameover */
extern bool Vittoria; /**< Booleano: true se si raggiunge la vittoria */
extern int Punteggio; /**< Intero che rappresenta il punteggio raggiunto */

extern ALLEGRO_DISPLAY *display; /**< Display del gioco */
extern ALLEGRO_EVENT_QUEUE *event_queue; /**< Coda di eventi */

#ifdef DEBUG_MODE
#define DBG(A) {A; }
#else
#define DBG(A)
#endif

/* Fine header modulo Struttura Dati */
