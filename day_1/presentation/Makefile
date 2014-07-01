

all : slides

slides: figures
	pdflatex  -shell-escape slides
	bibtex slides
	pdflatex  -shell-escape slides
	pdflatex  -shell-escape slides	

figures :
	make -C tikz/

clean:
	rm -rf *snm *toc *nav *blg *bbl *vrb *.pyg.* *out *aux *log
	make -C tikz/ clean
