CC = gcc

# Dossiers principaux
IDIR = include
ODIR = obj
BDIR = bin
SDIR = src
LDIR = lib
CPPFLAGS = -I/usr/include/cairo -Iinclude
LDFLAGS = -lcairo -lm -lX11 -ljeu -L lib/
MODE=CAIROGUI

# Flags compilateur
CFLAGS = $(CPPFLAGS) -Wall -g
# OBJECTS = $(SOURCES:src/%.c=%.o)

vpath %.h $(IDIR)
vpath %.c $(SDIR)
vpath %.o $(ODIR)

main: main.o jeu.o io.o grille.o
	@mkdir -p $(BDIR)
	@mkdir -p $(LDIR)

	ar -crv $(LDIR)/libjeu.a $(ODIR)/jeu.o $(ODIR)/grille.o
	ranlib $(LDIR)/libjeu.a

	$(CC) -DMODE$(MODE) $(CFLAGS) -o $(BDIR)/$@ $(ODIR)/main.o $(ODIR)/io.o $(LDFLAGS)
	@echo "\n=== Compilation terminée avec succès ==="
	@echo "Lancez le programme avec ./bin/main <numéro de grille>"

%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) -DMODE$(MODE) $(CFLAGS) -o $(ODIR)/$@ -c $<

dist:
	@mkdir -p dist
	tar -J -cvf dist/FleschBoris-GoL-v0.5.tar.xz grilles include src makefile Doxyfile README.md
	@echo "\n=== Archive créée avec succès ==="
	@echo "Chemin relatif de l'archive : dist/FleschBoris-GoL-v0.5.tar.xz"

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/*
	rm -f $(LDIR)/*.a
	rm -rf dist/
	rm -rf doc/
	@echo "\n=== Artefacts de compilation éliminés avec succès ==="
