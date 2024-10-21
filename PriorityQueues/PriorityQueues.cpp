#include<iostream>
#include<string>
//#include<algorithm>
#include<vector>
using namespace std;
#define max 100
class Queue 
{
private:
	int front;
	int rear;
	string* names;
	int *priorityQ;
public:
	Queue()
	{
		front = rear = -1;
		priorityQ = new int[max];
		names = new string[max];
	}
	bool enqueue(string element, int priority)
	{
		if (isFull())
		{
			cout << "Queue is Full" << endl;
			return false;
		}

		if (front == -1)
		{
			front = rear = 0;
			names[rear] = element;
			priorityQ[rear] = priority;
		}
		else
		{
			rear = (rear + 1) % max;
			 names[rear] = element;
			priorityQ[rear] = priority;

			int i = rear;
			while (i != front  && priorityQ[i] > priorityQ[ (i - 1 + max) % max])
			{
				swap(priorityQ[i], priorityQ[(i - 1 + max) % max]);
				swap(names[i], names[(i - 1 + max) % max]);
				i = (i - 1 + max) % max;
			}
		}
		return true;
	}


	pair<string,int> dequeue()
	{
		
		if (isEmpty())
		{
			cout << "Queue was Empty"<<endl;
			return pair<string,int>("", -1);
		}
		pair<string, int> dequeuedElement = make_pair(names[front], priorityQ[front]);

		if (front == rear)
		{
			front = rear = -1;
		}
		else if (front == max - 1 )
		{
			front = 0;
		}
		else
		{
			front++;
		}
		return dequeuedElement;
	}
	bool isEmpty()
	{
		if (front == -1)
		{
			return true;
		}
		else
			return false;
	}
	bool isFull()
	{
		if ((front == 0 && rear == max - 1) || (front == rear + 1))
		{
			cout << "Queue is full" << endl;
			return true;
		}
		else
			return false;
	}
	void displayQueue()
	{
		if (isEmpty())
		{
			cout << "Queue is empty!" << endl;
			return;
		}

		cout << "Current Queue:" << endl;
		int i = front;

		while (i!=rear)
		{
			cout << "Name: " << names[i] << ", Priority: " << priorityQ[i] << endl;

			if (i == rear) 
				break;

			i = (i + 1) % max; 
		}
	}
};
class user
{
private:
	string role;
	int priority;
    
public:
	user(string role, int priority)
	{
		this->priority = priority;
		this->role = role;
	}
	string getRole()
	{
		return this->role;
	}
	int getPriority()
	{
		return this->priority;
	}
	void displayuser()
	{
		cout << "Role: " << this->getRole() << "  Priority: " << this->getPriority() << endl;
	}
};

int main()
{
	Queue pQ;
	vector<user> users;
	cout << "*** Make your own Roles and prioritize them ***:";
	string role;
	int priority;
	string choice;
	bool flag = true;
	do
	{
		cout << "\nEnter Role:";
		getline(cin, role);
		if (role == "") { cout << "invalid role" << endl; flag = false; }
		if (flag == true)
		{
			cout << "Enter priority of the role: ";
			while (!(cin >> priority))
			{
				cout << "Error: Enter a valid priority: " << endl;
				cin.clear();
				cin.ignore(123, '\n');
			}
			cin.ignore();
			users.emplace_back(role, priority);
		}
		
		cout << "\nPress 1 to continue creating roles, Any button to exit\n";
		getline(cin, choice);
	
	} while (choice == "1");

	cout << "Available Roles: " << endl;
	for (auto& user : users)
	{
		user.displayuser();
	}
	string selectedRole;
	string name;
	string option;
	flag = true;
	bool enque = false;
	bool found = false;
	do
	{
		cout << "Enter the Role: ";
		getline(cin, selectedRole);
		if (selectedRole == "") { cout << "invalid role" << endl; flag = false; }
		else
			flag = true;
		if (flag == true)
		{
			cout << "Enter Name : ";
			getline(cin, name);
			for (auto& user : users)
			{
				found = false;
				if (user.getRole() == selectedRole)
				{
					found = true;
					enque=pQ.enqueue(name, user.getPriority());
					if (!enque) {
						cout << "Failed! Queue is full" << endl;
					}
					break;
				}
			}
			if (found == false)
				cout << "Invalid Role Entered!" << endl;
		}
		
		cout << "\nPress 'x' to exit, Any key to continue: ";
		getline(cin, option);
	} while (option != "x");

	//Deque using pair 
	pair<string, int> dequeuedElement = pQ.dequeue();
	if (dequeuedElement.first == "" && dequeuedElement.second == -1)
	{
		cout << "Queue is empty!" << endl;
	}
	else
	{
		cout << "Dequeued Name: " << dequeuedElement.first << endl;
		cout << "Dequeued Priority: " << dequeuedElement.second << endl;
	}

	pQ.displayQueue();

	return 0;
 }
