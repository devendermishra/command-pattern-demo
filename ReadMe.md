#Command Pattern Demo
##Introduction
This application is a basic demo of Command pattern. It is inspired from menu-based application for managing resources (referred as instances in the application) on a cloud. It misses many low level and higher level features. As it is demo, it does not actually create or delete resource but has stubbed function which can be replaced by real-life functions if required. Or `Command` class can be executed to implement real-life application.

##How to use?

###For linux-based systems

1. Download the code
2. Run `make`.

You will have `bin/demo` and `bin/demo2`. `bin/demo` is basic demo without undo/redo. `bin/demo2` also has undo/redo options.

###For non-linux based systems

There are two full C++ programs which can be compiled and executed as stand-alone program on any OS. `commandDemo.cpp` is basic demo without undo/redo. `commandUndo.cpp` contains undo/redo feature as well. Both files are separate and independent from each other.

##Important files:

1. `commandDemo.cpp`: It demonstrates basic usage of command pattern as a CLI menu-based application.
2. `commandUndo.cpp`: It demonstrates basic usage of command pattern with undo/redo options as CLI menu-based application.

##Notes for the other languages

Code is written in C++. It does not include any platform dependencies and can be easily ported into other high-level OOPs-based languages like Java/C#. Implement `Command` class as an interface in those languages.
