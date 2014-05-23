TEXFILES=$(wildcard *.tex)
TARGETS=$(patsubst %.tex,%,$(TEXFILES))

all: $(TARGETS)


$(TARGETS) : % : %.tex
	pdflatex $< 
