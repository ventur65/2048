/** @file 
* File contenente il modulo Disegno.
* Questo modulo non contiene alcuna logica di gioco. Esso raccoglie le funzioni necessarie
* per la visualizzazione in interfaccia grafica del gioco.
* @author Andrea Venturi
*
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include "strutt_dati.h"
#include "disegno.h"

using namespace std;

//Inizio Definizioni modulo Disegno

/** Funzione che sceglie l'immagine da caricare a seconda del valore
* nella mappa.
*
* Funzione ausiliaria, viene invocata per ogni casella della mappa di gioco. 
* Vedi ::update_graphics per maggiori dettagli sull'utilità.
*
* @param[in] value Valore della casella.
* @param[out] stringa Percorso dell'immagine corrispondente al valore.
*/
void scegli_img(char *stringa, int value) 
{
	switch (value) {
		case 0:
			strcpy(stringa, "../img/vuoto.png"); break;
		case 2:
			strcpy(stringa, "../img/2.jpeg"); break;
		case 4:
			strcpy(stringa, "../img/4.jpeg"); break;
		case 8:
			strcpy(stringa, "../img/8.jpeg"); break;
		case 16:
			strcpy(stringa, "../img/16.jpeg"); break;
		case 32:
			strcpy(stringa, "../img/32.jpeg"); break;
		case 64:
			strcpy(stringa, "../img/64.jpeg"); break;
		case 128:
			strcpy(stringa, "../img/128.jpeg"); break;
		case 256:
			strcpy(stringa, "../img/256.jpeg"); break;
		case 512:
			strcpy(stringa, "../img/512.jpeg"); break;
		case 1024:
			strcpy(stringa, "../img/1024.jpeg"); break;
		case 2048:
			strcpy(stringa, "../img/2048.jpeg"); break;
	}
}

/** Funzione che disegna le scritte sul display.
*/
void disegna(void)
{  	
   ALLEGRO_FONT *font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf",100,0 );
   
   assert(font);
   if (!font){
      cerr<<"Could not load 'pocket_calcuatlor_tt.ttf'.\n";
   }
 
   al_clear_to_color(al_map_rgb(251,248,239)); //Sfondo display
   
   al_draw_text(font, al_map_rgb(237,197,63), 50 , 10, 0, "2048");
   al_destroy_font(font);
   
   int x = 400;
   font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 15, 0);
   ALLEGRO_COLOR colscritte = al_map_rgb(118,111,101);
   assert(font);
   al_draw_text(font, colscritte, 550, 10, 0, "Andrea Venturi");
   al_destroy_font(font);
   
   font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 30, 0);
   assert(font);
   al_draw_text(font, colscritte, x, 100, 0, "PUNTEGGIO:");
   al_destroy_font(font);
   
   font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 40, 0);
   assert(font);
   al_draw_textf(font, colscritte, x, 135, 0, "%d", Punteggio);
   al_destroy_font(font);
   
   font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 25, 0);
   assert(font);
   al_draw_text(font, colscritte, x, 200, 0, "Istruzioni:");
   al_draw_text(font, colscritte, x, 230, 0, "Raggiungi 2048 sommando");
   al_draw_text(font, colscritte, x, 260, 0, "i numeri uguali vicini.");
   
   al_draw_text(font, colscritte, x, 300, 0, "Comandi");
   al_draw_text(font, colscritte, x, 330, 0, "Muovi: Frecce Direzionali");
   al_draw_text(font, colscritte, x, 360, 0, "Salvataggio: Tasto S");
   al_draw_text(font, colscritte, x, 390, 0, "Carica: Tasto C");
   al_draw_text(font, colscritte, x, 420, 0, "Ricomincia: Tasto R");
   al_destroy_font(font);
   
   ALLEGRO_BITMAP *sotto = al_load_bitmap("../img/sotto.png");
   assert(sotto);
   al_draw_bitmap(sotto, 10, 110, 0);
   
   al_destroy_bitmap(sotto);
}

/** Funzione che ridisegna la tabella di gioco.
*
* Sfrutta ::scegli_img per caricare l'immagine giusta per ogni casella.
*
* @param[in] mappa Matrice della mappa di gioco.	 
*/
void dis_tabella(const int mappa[][DIM]) 
{
	char file[50];

	ALLEGRO_BITMAP *bitmap;
   	for (int i = 0; i < DIM; i++) {
	   	for (int j = 0; j < DIM; j++) {
   			scegli_img(file, mappa[i][j]);
   			bitmap = al_load_bitmap(file);
   			assert(bitmap);
   			al_draw_bitmap(bitmap, 25+j*85, 125+i*85, 0);
   			al_destroy_bitmap(bitmap);
   		}
   	}
}

void ridisegna_mappa(const int mappa[][DIM])
{
	#ifndef DEBUG_MODE
	system("clear"); //Per versione da terminale
	#endif
	cout<<"frecce->movimenti, r->ricomincia, s->salva, c->carica"<<endl;
		cout<<"Punteggio: "<<Punteggio<<endl<<endl;
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++)
			if (mappa[i][j] == 0)
				cout<<"X\t";
			else
				cout<<mappa[i][j]<<"\t";
		cout<<endl;
	}
}

void update_graphics(const int mappa[][DIM])
{
	disegna();
	
	dis_tabella(mappa);
   	
   	al_flip_display();
}

void dis_gameover(const int mappa[][DIM])
{
	ALLEGRO_FONT *font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 100, 0);
	assert(font);
	if (!font){
      cerr<<"Could not load 'pocket_calcuatlor_tt.ttf'.\n";
   	}

	al_clear_to_color(al_map_rgb(251,248,239));
	
	al_draw_text(font, al_map_rgb(237,197,63), 320, 10, ALLEGRO_ALIGN_CENTER, "GAME OVER");
	
	al_destroy_font(font);

	int x = 390;

	ALLEGRO_COLOR colscritte = al_map_rgb(118,111,101);
	font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 30, 0);
	assert(font);
   	al_draw_text(font, colscritte, x, 100, 0, "PUNTEGGIO:");
   	al_destroy_font(font);

	font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 40, 0);
	assert(font);
   	al_draw_textf(font, colscritte, x, 135, 0, "%d", Punteggio);
   	al_destroy_font(font);
   
   	font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 25, 0);
   	assert(font);
  	al_draw_text(font, colscritte, x, 200, 0, "Premi R per ricominciare,");
	al_draw_text(font, colscritte, x, 230, 0, "C per caricare un salvataggio");
	al_draw_text(font, colscritte, x, 260, 0, "oppure chiudi la finestra");
	al_draw_text(font, colscritte, x, 290, 0, "per uscire.");
	al_destroy_font(font);

	ALLEGRO_BITMAP *sotto = al_load_bitmap("../img/sotto.png");
	assert(sotto);
	al_draw_bitmap(sotto, 10, 110, 0);
	al_destroy_bitmap(sotto);

	dis_tabella(mappa);

	al_flip_display();
}

void dis_vittoria(const int mappa[][DIM])
{

	ALLEGRO_FONT *font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 100, 0);
	assert(font);
	ALLEGRO_COLOR colscritte = al_map_rgb(118,111,101);

	al_clear_to_color(al_map_rgb(251,248,239));
	
	al_draw_text(font, al_map_rgb(237,197,63), 320, 10, ALLEGRO_ALIGN_CENTER, "VITTORIA!");
	
	al_destroy_font(font);

	int x = 390;

	font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 30, 0);
	assert(font);
   	al_draw_text(font, colscritte, x, 100, 0, "PUNTEGGIO:");
   	al_destroy_font(font);

	font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 40, 0);
	assert(font);
   	al_draw_textf(font, colscritte, x, 135, 0, "%d", Punteggio);
   	al_destroy_font(font);
   
   	font = al_load_ttf_font("../fonts/pocket_calcuatlor_tt.ttf", 25, 0);
   	assert(font);
	al_draw_text(font, colscritte, x, 200, 0, "Congratulazioni!");
  	al_draw_text(font, colscritte, x, 230, 0, "Hai raggiunto 2048!");
	al_draw_text(font, colscritte, x, 260, 0, "Premi R per ricominciare,");
	al_draw_text(font, colscritte, x, 290, 0, "C per caricare un salvataggio");
	al_draw_text(font, colscritte, x, 320, 0, "oppure chiudi la finestra.");
	al_destroy_font(font);

	ALLEGRO_BITMAP *sotto = al_load_bitmap("../img/sotto.png");
	assert(sotto);
	al_draw_bitmap(sotto, 10, 110, 0);
	al_destroy_bitmap(sotto);

	dis_tabella(mappa);

	al_flip_display();
}

//Fine Definzioni modulo Disegno
