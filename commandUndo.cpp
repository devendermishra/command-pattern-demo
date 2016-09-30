#include <cstdio>
#include <vector>
#include <stack>

//Command Interface
class Command {
public:
	virtual void execute () = 0;
	virtual void undo () = 0;
	virtual ~Command () {}
};

const size_t default_number_commands = 5;

//INVOKER
//here is MenuItem is associated with Command objects and can perform action.
class MenuItem {
public:

	//It will initialize the commands array with default number of commands
	MenuItem (): commands(default_number_commands) {
	}

	~MenuItem () {
		//Delete all the command object.
		for(std::vector<Command*>::iterator iter=commands.begin();
				iter != commands.end(); ++iter) {
			delete *iter;
		}
	}

	void add_command(Command* cmd, size_t pos) {
		if (commands.size() <= pos){
			commands.resize(pos);
		}
		commands.at(pos) = cmd;
	}

	void undo() {
		if (command_stack.size()) {
			Command * cmd = command_stack.top();
			command_stack.pop();
			cmd->undo();
			undone_stack.push(cmd);
		}
	}

	void redo() {
		if (undone_stack.size()) {
			Command * cmd = undone_stack.top();
			undone_stack.pop();
			command_stack.push(cmd);
			cmd->execute();
		}
	}

	//Action: Here, invoker calls Execute on Command objects.
	//Here, i is 1-based index.
	void perform_action(size_t i)
	{
		if (i and i <= commands.size()) {
			//Depending on what is the command, appropriate action is taken. Now, it is to upto Command object to perform the action. It can even defer the action or perform parallely or in other thread.
			commands[i-1]->execute();
			command_stack.push(commands[i-1]);
			while(not undone_stack.empty())
				undone_stack.pop();
		}
	}

private:
	//Invoker stores Command objects.
	std::vector<Command*> commands;
	std::stack<Command*> command_stack;
	std::stack<Command*> undone_stack;
};

//Receiver
//Receiver on which action is performed.
class InstanceManager {
public:
	void Run () {
		printf("Creating Instances\n");
	}
	void List () {
		printf("Show instances\n");
	}
	void Stop () {
		printf("Stopping Instances\n");
	}

	void Start () {
		printf("Starting Instances\n");
	}

	void Delete () {
		printf("Deleting Instances\n");
	}

	void UndoRun () {
		printf("Undo Creation\n");
	}
	void UndoList () {
		printf("Undo Show\n");
	}
	void UndoStop () {
		printf("Undo Stop\n");
	}

	void UndoStart () {
		printf("Undo Start\n");
	}

	void UndoDelete () {
		printf("Undo Delete\n");
	}

};

//Concrete Command classes
//Each concrete class is initialized and associated with receiver InstanceManager object.
class ShowInstances: public Command {
public:
	ShowInstances(InstanceManager * im): instance_manager(im){}

	void execute() {
		//Call appropriate action on receiver.
		instance_manager->List();
	}

	void undo() {
		instance_manager->UndoList();
	}

private:
	InstanceManager *instance_manager;
};


class CreateInstances: public Command {
public:
	CreateInstances(InstanceManager * im): instance_manager(im){}
	void execute() {
		instance_manager->Run();
	}
	
	void undo() {
		instance_manager->UndoRun();
	}

private:
	InstanceManager *instance_manager;
};

class StopInstances: public Command {
public:
	StopInstances(InstanceManager * im): instance_manager(im){}
	void execute() {
		instance_manager->Stop();
	}

	void undo() {
		instance_manager->UndoStop();
	}

private:
	InstanceManager *instance_manager;
};

class StartInstances: public Command {
public:
	StartInstances(InstanceManager * im): instance_manager(im){}
	void execute() {
		instance_manager->Start();
	}

	void undo() {
		instance_manager->UndoStart();
	}

private:
	InstanceManager *instance_manager;
};

class DeleteInstances: public Command {
public:
	DeleteInstances(InstanceManager * im): instance_manager(im){}
	void execute() {
		instance_manager->Delete();
	}

	void undo() {
		instance_manager->UndoDelete();
	}

private:
	InstanceManager *instance_manager;
};

//Create Command objects and associate them with Invoker
void setup_menu(MenuItem& menu_list, InstanceManager& im)
{
	menu_list.add_command(new ShowInstances(&im), 0);
	menu_list.add_command(new CreateInstances(&im), 1);
	menu_list.add_command(new StopInstances(&im), 2);
	menu_list.add_command(new StartInstances(&im), 3);
	menu_list.add_command(new DeleteInstances(&im), 4);
}

void show_menu()
{
	printf("1. Show Instances\n");
	printf("2. Create Instances\n");
	printf("3. Stop Instances\n");
	printf("4. Start Instances\n");
	printf("5. Delete Instances\n");
	printf("6. Undo last\n");
	printf("7. Redo last undo\n");
	printf("-1. Exit\n");
}

//Main function is doing the job of client here.
int main () {
	//It creates invoker object.
	MenuItem menu_list;
	//It setups the receiver object and
	InstanceManager im;
	//create concrete command objects.
	setup_menu(menu_list, im);

	int menu_choice;
	show_menu();
	scanf("%d", &menu_choice);
	while (menu_choice != -1) {
		//Invoker perform action as per menu's choice.
		if (menu_choice <= 5) {
			menu_list.perform_action(menu_choice);
		} else if (6 == menu_choice) {
			menu_list.undo();
		} else if (7 == menu_choice) {
			menu_list.redo();
		}

		show_menu();
		scanf("%d", &menu_choice);
	}
	return 0;

}

