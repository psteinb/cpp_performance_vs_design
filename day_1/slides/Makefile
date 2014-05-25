
all : slides

slides:
	pdflatex  -shell-escape slides
	bibtex slides
	pdflatex  -shell-escape slides
	pdflatex  -shell-escape slides	

clean:
	rm -rf *snm *toc *nav *blg *bbl *vrb *.pyg.* *out *aux *log
