#include <cstdio>
#include <vector>

//Command Interface
class Command {
public:
	virtual void execute () = 0;
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

	//Action: Here, invoker calls Execute on Command objects.
	//Here, i is 1-based index.
	void perform_action(size_t i)
	{
		if (i and i <= commands.size())
			//Depending on what is the command, appropriate action is taken. Now, it is to upto Command object to perform the action. It can even defer the action or perform parallely or in other thread.
			commands[i-1]->execute();
	}

private:
	//Invoker stores Command objects.
	std::vector<Command*> commands;	
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
		printf("Stopping Instances\n");
	}

	void Delete () {
		printf("Deleting Instances\n");
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

private:
	InstanceManager *instance_manager;
};


class CreateInstances: public Command {
public:
	CreateInstances(InstanceManager * im): instance_manager(im){}
	void execute() {
		instance_manager->Run();
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

private:
	InstanceManager *instance_manager;
};

class StartInstances: public Command {
public:
	StartInstances(InstanceManager * im): instance_manager(im){}
	void execute() {
		instance_manager->Start();
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
		menu_list.perform_action(menu_choice);

		show_menu();
		scanf("%d", &menu_choice);
	}
	return 0;

}

