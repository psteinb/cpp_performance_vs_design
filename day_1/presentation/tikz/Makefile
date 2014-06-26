TEXFILES=$(wildcard *.tex)
TARGETS=$(patsubst %.tex,%,$(TEXFILES))

all: $(TARGETS)

$(TARGETS) : % : %.tex
	pdflatex $< 

clean :
	rm -vf *.aux *.pdf *.log

help :
	@echo "building all tikz files as pdfs"	
	@echo -e "usage		 : make"	
	@echo -e "available targets: \n\t\tall " $(TARGETS)
