/** @file
* File contenente l'interfaccia del modulo Salva/Carica.
* @author Andrea Venturi
*/

/* Inizio interfaccia modulo Salva/Carica */

/** Funzione che mostra il filechooser ed effettua il salvataggio su file.
*
* Sfrutta ::salva per il salvataggio su file di testo. 
* Se il file esiste già si chiede se si vuole sovrascrivere.
* In caso di errori, si visualizza un dialogo di errore.
*
* @param[in] mappa Matrice della mappa di gioco.
*/
void save_dialog(int mappa[][DIM]) ;

/** Funzione che mostra il filechooser ed effettua il caricamento da file di testo.
*
* Questa funzione sfrutta ::carica per caricare da file di testo esterno.
* Nel caso di errore di caricamento, si mostra un dialogo di errore e non si modifica
* la mappa corrente.
* 
* @param[in] mappa Matrice della mappa di gioco.
* @param[out] successo True se l'operazione di caricamento ha avuto successo, False altrimenti.
*/
bool load_dialog(int mappa[][DIM]) ;
