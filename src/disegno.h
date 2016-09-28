/**@file
* File contenente l'interfaccia del modulo Disegno.
* @author Andrea Venturi
*/

/* Inizio interfaccia modulo Disegno */

/** Funzione che ridisegna su stdout la mappa.
*
* Invocata dopo ogni mossa.
*
* @param[in] mappa Matrice della mappa di gioco.
*/
void ridisegna_mappa(const int mappa[][DIM]) ;

/** Funzione che ridisegna tutto il display dopo ogni mossa.
*
* Sfrutta ::disegna e ::dis_tabella per ridisegnare rispettivamente il display
* e la tabella di gioco.
*
* @param[in] mappa Matrice della mappa di gioco.
*/
void update_graphics(const int mappa[][DIM]) ;

/** Funzione che ridisegna il display in caso di GameOver.
*
* Sfrutta ::dis_tabella per ridisegnare la tabella di gioco.
*
* @param[in] mappa Matrice della mappa di gioco.
*/
void dis_gameover(const int mappa[][DIM]) ;

/** Funzione che ridisegna il display in caso di Vittoria.
*
* Sfrutta ::dis_tabella per ridisegnare la tabella di gioco.
*
* @param[in] mappa Matrice della mappa di gioco.
*/
void dis_vittoria(const int mappa[][DIM]) ;

/* Fine interfaccia modulo Disegno. */
