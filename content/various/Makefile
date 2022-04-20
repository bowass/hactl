# Usage: make [run/test/...] [q=file]
q := a # change this for default question file
run: exe
	@./exe
exe: $q.cpp # with DEBUG define
	@myg++ -Wno-unknown-pragmas -D DEBUG -o exe $q.cpp
servexe: $q.cpp # without DEBUG define
	@myg++ -Wno-unknown-pragmas -o servexe $q.cpp
clean:
	@rm exe servexe
test: exe in # tests locally with DEBUG
	@cat in | ./exe
servtest: servexe in # tests like server
	@cat in | ./exe
