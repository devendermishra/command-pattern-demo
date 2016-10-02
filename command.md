#Command Design Pattern
##Introduction

Command pattern is an object behavioral pattern.

_Intent_

"Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requeusts".

Verbatim of the intent is quoted from GoF book of Design Patterns.

Many times, we need the following:

1. Logging the operations performed so far. They can be logged as a script which can be replayed as required.
2. Replaying the operations performed so far
3. Underlying operations can be changed, swapped with each other
4. Undo/redo operation

The above problems can be solved by using Command Pattern in the design by identifying operations as commands and separating them from the code or module which invokes. They are separated using encapsulation.

In this text, we will see what is Command Pattern and how does it rescue us in the above mentioned problem. We will also see the usage of command pattern in an executable program. This program is a menu-based application for managing cloud resources (instances).

##Pattern

###Motivation
Sometimes, it is required to issue requests to objects without knowing what is the in the operation or who(receiver) is acting on the request. 

One example is of remote controller with 4-buttons. A button can be assigned one function at a time. And functions of button can be arranged or rearranged in any order the user wants. This is can be done in hard ways (like redesigning circuit or program every times we need to change functionality of a button or to rearrange them) or easy ways (separating functionalities as a pluggable module which can be attached to the button when required).

Functionality can be made pluggable when the button does not details of what is being performed. It will know only then that it sends the signal to the pluggable module attached to it. In this case, we can easily change functionality by unplugging existing one and plugging new one. They can be rearragned easily by unplugging from existing button and replugging to a new button. By this, button does not implement functionality or knows how to do the operation.

Another example on the similar line we can think of menu which can be changed or rearranged. There, it is also important that menu button action does not implement functionality on its own but know an object which can perform the desired functionality and just send message to that object.

Command pattern in the case lead us to separate the request from the object which invokes it by encapsulating it as an object. Those request objects can be stored and passed around like other objects.

As request objects needs to be used in the same way (by calling method with same signature) for that they need an abstraction. For this purpose, there is an abstract Command class (or interface in languages like Java). Command class declares an interface for executing operations. In the simplest form, they define an abstract method called `execute`.

Concrete command subclasses command and specify receiver-action pair (receiver is that who will perform the action or help in action). Receiver can be stored with invidual command objects or can be shared between them. The receiver has knowledge required to carry out the request.

In our given example of remote controller and menu, command objects can provide easy implementation. In case of remote, functionalities of buttons are Command object subclasses which are assigned to a button. When the button is pressed, it calls execute method of the command object stored with it. For menu, functionality is stored as command with menu items. When a menu item is clicked, it calls execute method of the command object stored with it.

###Structure

Structure of command pattern is shown in Fig. 1.


	Fig. 1: Command pattern

Let us see what are these entities/classes with their responsiblities:

- Command: an interface for executing an operation.
- ConcreteCommand:

	- It defines binding between a Receiver object and an action.
	- It implements Execute by invoking the corresponding operations of receiver.

- Client (Application): It creates `ConcreteCommand` objects and set their receiver.
- Invoker (Menu item or remote controller button): It asks the command to carry out the request.
- Receiver (Document, Application, Resource Manager etc.): It knows how to perform the requested operation. Any class can act as a receiver.

###Collaboration

Sequence diagrm of command pattern is shown in Fig. 2. It shows how Command decouples the invoker from the operation performed by the request (and hence from the receiver).

	Fig. 2: Sequence diagram of command pattern

Collaboration is explained below:

- Client creates ConcreteCommand(aCommand) and associate it with reciever.
- Invoker object stores the ConcreteCommand object.
- Invoker issues a request by calling Execute on the command.
- ConcreteCommand object invokes operations on its receiver to carry out the request.

When commands are undoable, ConcreteCommand stores state for undoing the command before executing Execute.

###Applicability

Use Command pattern when you need:

- parameterize objects by an action to perform
- specify queue and execute requests at different times. Command object can lifetime different from original request.
- Undo: Command's Execute can store the state for reversing the effect of Execute. Executed commands are stored in a history list.
- logging changes so that they can be reapplied or rollbacked in case of a system crash.
- structure a system around high-level operations built on primitives operations. In Command pattern, you can make a higher-level command object by storing other command objects and can call those command objects on execute.

###Consequences

It has following consequences:

1. Decouples the object that invokes the operation from the one that knows how to perform it.
2. Commands are first-class objects. They can be manipulated (by passing different parameters, changing attributes etc.) and extended like other object.
3. Commands can be assembled into composite command. e.g Macros
4. Easy to add new Commands. There is no need to change existing classes.

###Implementation
Following issues need to be considered when implementing Command pattern:

1. How intelligent should a command be?
	A command can perform all the operation on its own without using any receiver or it can just delegate the operation to the receiver.

2. Supporting undo/redo
	Undo can be supported by providing a way to reverse the execution of command object (by storing state on command object and Unexecute/Undo method). Redo needs only executing the last executed command object. For single undo/redo, only last executed command is to be stored. For multi-level undo/redo, application needs to store the list commands that are executed so far. Memento pattern can be used to store the state information.

	In undo/redo process, errors can accumulate as commands are executed, undone and redone repeatedly. Application's state eventually diverges from original values. Hence, it may require to store more information with command to restore the application state to the original state.


##Example
Example given here is inspired from menu-based application for managing resources (which is refered as instance here) on a cloud. This application presents a menu to perform different operations on instances. This is a demo application and it misses the real-world details. Those details can be handled by extending `Command` class with real-world implementation and off-course modifying `InstanceManager` class.

It is accessible at [[https://github.com/devendermishra/command-pattern-demo]]. Please read `ReadMe.md` on how to use. Please see and give your feedback on it.

In this application, command pattern tries to solve the following problem:

1. New menus might be added in the future.
2. Menu list might be reduced in the future.
3. User should be able to change the order of menu in the future.
4. A new and better implementation might come in future and can replace existing menu.
5. Undo/redo.
6. Sequence of input can be logged to a file and using that file, input sequence can be repeated.
7. Actions can be executed in a different thread.

Solving the problem here means that it solves the problem ease without drastic modifications on the code.


Let us see the design and how command pattern solves the above concerns.

###Structure

Structure of the application is shown in the figure below.


	Fig. 3. Structure of the application 

1. `Command`: `Command` is an abstract class (interface in Java) which defines `execute`, `undo` and `redo` methods. Subclasses of `Command` (`ShowInstances`, `CreateInstances`, `StopInstances`, `StartInstances` and `DeleteInstances`)
2. `MenuItems`: `MenuItems` holds `Command` objects. It is responsible for choosing appropriate `Command` objects based on some logic and calling `execute` method.
3. `InstanceManager`: It corresponds to the `Receiver`. `Command` object calls method of `InstanceManager` to perform the necessary action.
4. Client: Our client is `main` function or entry point of the application.


###Behavioral Dynamics


	Fig. 4. Sequence diagram of the application

Let us see how our application works:

1. When application starts, then the client (`main` function) does the following

	a. Creates an `InstanceManager` object. (`Receiver`)
	b. Creates a `MenuItem` object. (`Invoker`)
	c. Creates command objects and associate them with the `InstanceManager` object.
	d. Associate command objects to the `MenuItem` object by assigning them at the appropriate place.
	e. Run input loop where it asks for the user input. If user indicates exit (pressing -1) exit the application. Other inputs are redirected to the `MenuItem` object.

Now, application is ready to receive user input. Let us see what happens when the user enters the input:

1. On input:

	a. `MenuItem` object finds the appropriate `Command` object. Here, it is in the array with index same as user input.
	b. call `Command` object's `execute` method.

###How it solves our concerns:

####New menus might be added in the future.
This problem will be solved as follows:

1. Extend `Command` class or an existing sub-class and implement it. This is required only if new kind of action is to be added.
2. Associate the object of `Command` sub-classes with `MenuItem`. It can be adding it into the array at the appropriate index.
3. Modify print-menu or menu list to add the new menu.

e.g. If we need to add the menu "Destroy all", we can do the following:

`class DestroyAll: public Command { ... };`
`menu_item.add(new DestroyAll, 8)`
`#In the code`
`  printf("8. Destroy all\n");`

Now, on entering 8, it will perform "Destroy all"

####Menu list might be reduced in the future.
This is fairly easy. Remove the command object and remove it from `MenuItem`. The advantage offered by command pattern is that as we changed menu items, we are ensured that existing commands will not break due to this change.

####User should be able to change the order of menu in the future.
As implementation is here array-based, order of the array items can be changed.

####A new and better implementation might come in future and can replace existing menu.
It can be done by:

1. Extend the `Command` class or an existing sub-class. Override `execute` method with the better implementation.
2. In the `MenuItem`, change the association by removing existing object and add new object.

e.g.

	class NewImpl: public Command { /*a better implementation*/ };
	menu_item.add(new NewImpl(), 8); //Assuming that old implementation was 8th position.

####Undo/redo.
File `commandUndo.cpp` demonstrates undo/redo. Here, undo/redo is stack based which means that if we are performing undos, then we are doing redos. Moment we change anything, redo will be disabled. redo will undo the last undo. It will not undo the last undo over a new change.

For undo/redo, we need:

1. State of the system is to be maintained. It can be maintained at `Command` objects or `Receiver` object (but managed by command objects). Memento design pattern can be used store the last states.
2. Sequence of the commands executed is to be maintained. Invoker stores the sequence.
3. Each command will provide an `undo` method which will either restore the previous state or ask the receiver the restore the state.

Structure is show in the following figure:


	Fig. 5. Structure for undo/redo

To support undo/redo, we will do the following:

1. Add abstract method `undo` to `Command` class.
2. Each subclass will implement `undo` method.
3. MenuItem maintains two stacks: command sequence and undo stack (for redo)
3. Modify MenuItem so that:

	a. In each menu action, it will store the command sequence in the stack.
	b. Clear the undo stack

4. When undo is requested (from MenuItem), then

	a. MenuItem pop the command from the command sequence stack (got the last executed command) and calls undo method.
	b. Stores the popped command into the undo stack.

5. When redo is requested (from MenuItem), then

	a. MenuItem pop the command from the undo stack (got the last undone command) and calls execute method.
	b. Stores the popped command into the command sequence stack.

On every action, other than undo/redo, it clears undo stack. Hence, it performs the redo of the last undone command.

Following sequence diagram shows the above action:

	Fig. 6: Sequence diagram from undo/redo


####Sequence of input can be logged to a file and using that file, input sequence can be repeated.
It can be achieved in the following way:

1. Invoker can log the action. Limitation: Invoker needs to know which action is what.
2. Command object can log the action.

####Actions can be executed in a different thread.
It can
As invoker has command objects, it can execute them in different thread. 
