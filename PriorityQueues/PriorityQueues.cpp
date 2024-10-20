#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
#define max 100
class Queue 
{
private:
	//int priority;
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
			//cout << "Queue is Empty" << endl;
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

		while (true)
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
	cout << "Make your own users and prioritize them:";
	string role;
	int priority;
	string choice;
	do
	{
		cout << "\nEnter Role:";
		getline(cin, role);
		cout << "Enter priority of the role: ";
		while (!(cin >> priority))
		{
			cout << "Error: Enter a valid priority: " << endl;
			cin.clear();
			cin.ignore(123, '\n');
		}
		cin.ignore();
		users.emplace_back(role, priority);
		cout << "Press 1 to continue creating roles,\nany button to exit\n";
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
	bool found = false;
	do
	{
		cout << "Enter the role: ";
		getline(cin, selectedRole);

		cout << "Enter name : ";
		getline(cin, name);
		for (auto& user : users)
		{
			if (user.getRole() == selectedRole)
			{
				found = true;
				pQ.enqueue(name, user.getPriority());
				break;
			}
			if (found == false)
				cout <<"Invalid Role Entered!"<<endl;
		}
		cout << "\nPress x to exit,\nany button to continue\n";
		getline(cin, option);
	} while (option != "x");

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
