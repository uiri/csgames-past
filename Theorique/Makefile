FILENAME = info-theorique
PDFLATEX = pdflatex --shell-escape 

$(FILENAME).pdf : $(FILENAME).tex
	$(PDFLATEX) $(FILENAME).tex

.PHONY: all clean solution template
all :
	$(PDFLATEX) $(FILENAME).tex
	$(PDFLATEX) $(FILENAME).tex

solution:
	sed -e 's/%\\printanswers/\\printanswers/' $(FILENAME).tex > solution-$(FILENAME).tex
	$(PDFLATEX) solution-$(FILENAME).tex
	$(PDFLATEX) solution-$(FILENAME).tex
	rm -f solution-$(FILENAME).tex

template:
	homework-template $(FILENAME).tex > template-$(FILENAME).tex

clean:
	rm -f *.log *.aux $(FILENAME).pdf
	rm -f *.gnuplot *.table

site: all template
	cp $(FILENAME).pdf ~/Documents/Site/content/files/inf7440/aut2015/
	cp template-$(FILENAME).tex ~/Documents/Site/content/files/inf7440/aut2015/
