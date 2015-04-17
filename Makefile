##
## @file Makefile
## Betriebssysteme Makefile für mypopen.c
## 
## @authors: Claudia Baierl, Juliane Pi Winkler, René Elsner
## @date: 17.04.2015
## @version: 1.0
##
##

##
## ------------------------------------------------------------- variables --
##


OPTFLAGS        = -DDEBUG -O3 -Wall -Werror -Wextra -Wstrict-prototypes -fno-common -pedantic -g
CC              = gcc
MAKE            = make
RM              = rm -f
DOXYGEN         = doxygen
CD              = cd
MV              = mv
GREP            = grep
EXCLUDE_PATTERN = footrulewidth
OBJECTS          = mypopen.o


##
## ----------------------------------------------------------------- rules --
##

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

##
## --------------------------------------------------------------- targets --
##

all: popentest test-pipe 

popentest: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lpopentest

test-pipe: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -ltest-pipe

clean:
	$(RM) *.o *.h.gch mypopen

clean_doc:
	$(RM) -r doc/ html/ latex/

doc: clean_doc
	$(DOXYGEN)

clean_all: clean clean_doc

doc: html pfd

html: 
	$(DOXYGEN) doxygen.dcf

pdf: html 
	$(CD) doc/pdf && \ 
	$(MV) refman.tex refman_save.tex && \ 
	$(GREP) -v $(EXCLUDE_PATTERN) refman_save-tex > refman.tex && \
	$(RM) refman_save.tex && \ 
	make && \ 
	$(MV) refman.pdf refman.save && \ 
	$(RM) *.pdf *.html *.tex *.aux *.sty *.log *.eps *.out *.ind *.idx \ *.ilg *.toc *.tps makefile && \ 
	$(MV) refman.save refman.pdf
