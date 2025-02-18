LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "This makefile builds HACTL (Haifa's Algorithm Competition Template Library)"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast		- to build HACTL, quickly (only runs LaTeX once)"
	@echo "	make hactl		- to build HACTL"
	@echo "	make clean		- to clean up the build process"
	@echo "	make veryclean		- to clean up and remove hactl.pdf"
	@echo "	make test		- to run all the stress tests in stress-tests/"
	@echo "	make test-compiles	- to test compiling all headers"
	@echo "	make help		- to show this information"
	@echo "	make showexcluded	- to show files that are not included in the doc"
	@echo ""
	@echo "For more information see the file 'doc/README'"

fast: | build
	$(LATEXCMD) content/hactl.tex </dev/null
	cp build/hactl.pdf hactl.pdf

hactl: test-session.pdf | build
	$(LATEXCMD) content/hactl.tex && $(LATEXCMD) content/hactl.tex
	cp build/hactl.pdf hactl.pdf

clean:
	cd build && rm -f hactl.aux hactl.log hactl.tmp hactl.toc hactl.pdf hactl.ptc

veryclean: clean
	rm -f hactl.pdf test-session.pdf

build:
	mkdir -p build/

test:
	./doc/scripts/run-all.sh .

test-compiles:
	./doc/scripts/compile-all.sh .

test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build
	$(LATEXCMD) content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf

showexcluded: build
	grep -RoPh '^\s*\\hactlimport{\K.*' content/ | sed 's/.$$//' > build/headers_included
	find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included

.PHONY: help fast hactl clean veryclean build test test-compiles showexcluded