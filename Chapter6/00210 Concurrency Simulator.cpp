#include <iostream>
#include <deque>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class StatementType
{
	ASSIGNMENT, OUTPUT, LOCK, UNLOCK, STOP
};

enum class ProgramState
{
	RUNNING, READY, BLOCKED
};

struct Statement
{
	StatementType type;
	char var;
	int constant;
	Statement(StatementType type, char var = '\0', int constant = 0)
		: type(type), var(var), constant(constant) {};
};

struct Program
{
	vector<Statement> statements;
	ProgramState state = ProgramState::READY;
	size_t eip = 0;
};

void simulation(vector<Program> &programs, const vector<int> &StatementUnits, int quantum)
{
	vector<int> variables(26, 0);
	deque<size_t> ready, blocked;
	bool lock = false;
	for (size_t i = 0; i < programs.size(); i++)
	{
		ready.push_back(i);
	}
	while (!ready.empty()) {
		size_t ProgramIndex = ready.front();
		Program &program = programs.at(ProgramIndex);
		ready.pop_front();
		program.state = ProgramState::RUNNING;
		int ExecutionTime = 0;
		while (program.state == ProgramState::RUNNING && ExecutionTime < quantum && program.eip < program.statements.size()) {
			const Statement &statement = program.statements[program.eip++];
			ExecutionTime += StatementUnits[static_cast<int>(statement.type)];
			switch (statement.type)
			{
			case StatementType::ASSIGNMENT:
				variables[statement.var - 'a'] = statement.constant;
				break;
			case StatementType::OUTPUT:
				cout << ProgramIndex + 1 << ": " << variables[statement.var - 'a'] << endl;
				break;
			case StatementType::LOCK:
				if (lock) {
					program.state = ProgramState::BLOCKED;
					blocked.push_back(ProgramIndex);
					program.eip--;
				}
				else {
					lock = true;
				}
				break;
			case StatementType::UNLOCK:
				lock = false;
				if (!blocked.empty()) {
					programs[blocked.front()].state = ProgramState::READY;
					ready.push_front(blocked.front());
					blocked.pop_front();
				}
				break;
			case StatementType::STOP:
				break;
			}
		}
		if (program.state == ProgramState::RUNNING && program.eip < program.statements.size()) {
			ready.push_back(ProgramIndex);
		}
	}
}

int main()
{
	int cases = 0;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		int ProgramNumber, quantum;
		cin >> ProgramNumber;
		vector<int> StatementUnits(5);
		for (size_t i = 0; i < StatementUnits.size(); i++)
		{
			cin >> StatementUnits[i];
		}
		cin >> quantum;
		cin.get();
		vector<Program> programs(ProgramNumber);
		for (int p = 0; p < ProgramNumber; p++)
		{
			string statement, word;
			char var;
			int constant;
			while (getline(cin, statement)) {
				stringstream ss(statement);
				string word;
				ss >> word;
				if (word == "end") break;
				else if (word == "print") {
					ss >> var;
					programs[p].statements.emplace_back(StatementType::OUTPUT, var);
				}
				else if (word == "lock") {
					programs[p].statements.emplace_back(StatementType::LOCK);
				}
				else if (word == "unlock") {
					programs[p].statements.emplace_back(StatementType::UNLOCK);
				}
				else {
					var = word[0];
					ss >> word >> constant;
					programs[p].statements.emplace_back(StatementType::ASSIGNMENT, var, constant);
				}
			}
		}
		simulation(programs, StatementUnits, quantum);
		if (i != cases - 1) {
			cout << endl;
		}
	}
	return 0;
}
/*
1

3 1 1 1 1 1 1
a = 4
print a
lock
b = 9
print b
unlock
print b
end
a = 3
print a
lock
b = 8
print b
unlock
print b
end
b = 5
a = 17
print a
print b
lock
b = 21
print b
unlock
print b
end
*/
