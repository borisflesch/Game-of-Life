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
	$(CC) $(CFLAGS) -o $(BDIR)/$@ $(ODIR)/main.o $(ODIR)/jeu.o $(ODIR)/io.o $(ODIR)/grille.o

%.o: %.c
	$(CC) $(CFLAGS) -o $(ODIR)/$@ -c $<

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/*