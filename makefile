default: bin/demo bin/demo2

bin/demo: commandDemo.cpp
	mkdir -p bin
	g++ -g -O0 $< -o $@

bin/demo2: commandUndo.cpp
	mkdir -p bin
	g++ -g -O0 $< -o $@

clean:
	rm -f bin/demo
	rm -f bin/demo2
