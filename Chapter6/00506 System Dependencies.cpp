#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Component
{
	string name;
	size_t idx;
	bool explicitly, installed;
	vector<size_t> dependent;
	list<size_t> InstalledSupport;
	Component(const string &name, size_t idx) 
		: name(name), idx(idx), explicitly(false), installed(false) {}
	void AddDependency(const Component &dependency)
	{
		if (find(dependent.begin(), dependent.end(), dependency.idx) == dependent.end()) {
			dependent.push_back(dependency.idx);
		}
	}
	void AddSupport(const Component &support)
	{
		if (find(InstalledSupport.begin(), InstalledSupport.end(), support.idx) == InstalledSupport.end()) {
			InstalledSupport.push_back(support.idx);
		}
	}
	void DelSupport(const Component &support)
	{
		InstalledSupport.remove(support.idx);
	}
};

class Program
{
public:
	Program(ostream &os) : os(os) {}
	void depend(const string &items)
	{
		istringstream iss(items);
		string ItemName, DependencyName;
		iss >> ItemName;
		size_t ItemIdx = AddComponent(ItemName);
		while (iss >> DependencyName) {
			size_t DependencyIdx = AddComponent(DependencyName);
			components[ItemIdx].AddDependency(components[DependencyIdx]);
		}
	}
	void install(const string &item)
	{
		size_t ItemIdx = AddComponent(item);
		Component &component = components[ItemIdx];
		if (component.installed) {
			PrintWithIndent(component.name + " is already installed.");
		}
		else {
			InstallComponent(component, true);
		}
	}
	void remove(const string &item)
	{
		size_t ItemIdx = AddComponent(item);
		Component &component = components[ItemIdx];
		if (!component.installed) {
			PrintWithIndent(component.name + " is not installed.");
		}
		else if (!component.InstalledSupport.empty()) {
			PrintWithIndent(component.name + " is still needed.");
		}
		else {
			RemoveComponent(component);
		}
	}
	void ListInstalled()
	{
		for (size_t ComponentIdx : installed)
		{
			PrintWithIndent(components[ComponentIdx].name);
		}
	}
private:
	vector<Component> components;
	map<string, size_t> Name2Idx;
	list<size_t> installed;
	ostream &os;
	size_t AddComponent(const string &item)
	{
		auto iter = Name2Idx.find(item);
		if (iter == Name2Idx.end()) {
			Name2Idx[item] = components.size();
			components.emplace_back(item, components.size());
			return components.back().idx;
		}
		else return iter->second;
	}
	void InstallComponent(Component &component, bool explicitly)
	{
		for (size_t DependencyIdx : component.dependent)
		{
			Component &dependency = components[DependencyIdx];
			if (!dependency.installed) {
				InstallComponent(dependency, false);
			}
			dependency.AddSupport(component);
		}
		PrintWithIndent("Installing " + component.name);
		component.explicitly = explicitly;
		component.installed = true;
		installed.push_back(component.idx);
	}
	void RemoveComponent(Component &component)
	{
		PrintWithIndent("Removing " + component.name);
		component.explicitly = false;
		component.installed = false;
		installed.remove(component.idx);
		for (auto riter = component.dependent.rbegin(); riter != component.dependent.rend(); riter++)
		{
			Component &dependency = components[*riter];
			if (dependency.installed) {
				if (dependency.InstalledSupport.size() == 1 && !dependency.explicitly) {
					RemoveComponent(dependency);
				}
				dependency.DelSupport(component);
			}
		}
	}
	void PrintWithIndent(const string &message)
	{
		os << "   " << message << endl;
	}
};

int main()
{
	string line;
	string command, parameter;
	while (getline(cin, line)) {
		Program program(cout);
		do {
			cout << line << endl;
			istringstream iss(line);
			iss >> command;
			if (command == "END") break;
			else if (command == "DEPEND") {
				getline(iss, parameter);
				program.depend(parameter);
			}
			else if (command == "INSTALL") {
				iss >> parameter;
				program.install(parameter);
			}
			else if (command == "REMOVE") {
				iss >> parameter;
				program.remove(parameter);
			}
			else if (command == "LIST") {
				program.ListInstalled();
			}
			else;
		} while (getline(cin, line));
	}
	return 0;
}
/*
DEPEND   TELNET TCPIP NETCARD
DEPEND TCPIP NETCARD
DEPEND DNS TCPIP NETCARD
DEPEND  BROWSER   TCPIP  HTML
INSTALL NETCARD
INSTALL TELNET
INSTALL foo
REMOVE NETCARD
INSTALL BROWSER
INSTALL DNS
LIST
REMOVE TELNET
REMOVE NETCARD
REMOVE DNS
REMOVE NETCARD
INSTALL NETCARD
REMOVE TCPIP
REMOVE BROWSER
REMOVE TCPIP
END
*/
