default: bin/demo

bin/demo: commandDemo.cpp
	mkdir -p bin
	g++ -g -O0 $< -o $@

clean:
	rm -f bin/demo
