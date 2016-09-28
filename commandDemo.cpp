#include <cstdio>
#include <vector>

//Command class
class Command {
public:
	virtual void execute () = 0;
	virtual ~Command () {}
};

const size_t default_number_commands = 5;
//Invoker here is MenuItem which stores reference to Command objects and can perform ith action.
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

	//Here, i is 1-based index.
	void perform_action(size_t i)
	{
		if (i and i <= commands.size())
			commands[i-1]->execute();
	}

private:
	std::vector<Command*> commands;	
};

//Concrete command classes
class ShowInstances: public Command {
public:
	void execute() {
		printf("Show instances\n");
	}
};

class CreateInstances: public Command {
public:
	void execute() {
		printf("Creating Instances\n");
	}
};

class StopInstances: public Command {
public:
	void execute() {
		printf("Stopping Instances\n");
	}
};

class StartInstances: public Command {
public:
	void execute() {
		printf("Stopping Instances\n");
	}
};

class DeleteInstances: public Command {
public:
	void execute() {
		printf("Deleting Instances\n");
	}
};

void setup_menu(MenuItem& menu_list)
{
	menu_list.add_command(new ShowInstances(), 0);
	menu_list.add_command(new CreateInstances(), 1);
	menu_list.add_command(new StopInstances(), 2);
	menu_list.add_command(new StartInstances(), 3);
	menu_list.add_command(new DeleteInstances(), 4);
}

void show_menu()
{
	printf("1. Show Instances\n");
	printf("2. Create Instances\n");
	printf("3. Stop Instances\n");
	printf("4. Start Instances\n");
	printf("5. Delete Instances\n");
	printf("-1. Exit\n");
}

int main () {
	MenuItem menu_list;
	setup_menu(menu_list);

	int menu_choice;
	show_menu();
	scanf("%d", &menu_choice);
	while (menu_choice != -1) {
		menu_list.perform_action(menu_choice);
		show_menu();
		scanf("%d", &menu_choice);

	}
	return 0;

}
