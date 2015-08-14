IDIR = headers
SDIR = src
ODIR = obj
BDIR = bin

CC     = gcc
CFLAGS = -Wall -g -std=c99 -I$(IDIR)/

_OBJS = buffer_ring.o
OBJS  = $(patsubst %,$(ODIR)/%,$(_OBJS))

LIBS = 


all: bring_test

bring_test: $(ODIR)/buffer_ring.o
	$(CC) -o $(BDIR)/buffer_ring $(LIBS) $(ODIR)/buffer_ring.o

$(ODIR)/%.o:  $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean: clean_obj clean_exe

clean_obj:
	rm -f $(ODIR)/*.o

clean_exe:
	rm -f $(BDIR)/*

