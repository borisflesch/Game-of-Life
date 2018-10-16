CC = gcc

# Dossiers principaux
IDIR = include
ODIR = obj
BDIR = bin
SDIR = src

# Flags compilateur
CFLAGS = -I$(IDIR) -Wall
# OBJECTS = $(SOURCES:src/%.c=%.o)

vpath %.h $(IDIR)
vpath %.c $(SDIR)
vpath %.o $(ODIR)

main: main.o jeu.o io.o grille.o
	@mkdir -p $(BDIR)
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $(ODIR)/main.o $(ODIR)/jeu.o $(ODIR)/io.o $(ODIR)/grille.o

%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -o $(ODIR)/$@ -c $<

dist:
	@mkdir -p dist
	tar -J -cvf dist/projet.tar.xz grilles include src makefile

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/*