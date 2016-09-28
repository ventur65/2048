OBJ = 2048.o gioco.o salva_carica.o disegno.o
CXXFLAGS=-Wall
PKG = `pkg-config --cflags --libs allegro-5.0 allegro_ttf-5.0 allegro_font-5.0 allegro_image-5.0 allegro_dialog-5.0`

2049: $(OBJ)
	g++ -o 2048 $(OBJ) $(PKG)

-include dependencies

.PHONY: depend clean cleanall debug

depend: 
	g++ -MM *.cc > dependencies

clean:
	rm -f *.o

cleanall:
	rm -f 2048 *.o *~
	
debug:
	g++ -o 2048 -g -D DEBUG_MODE *.cc $(PKG)
	
	
