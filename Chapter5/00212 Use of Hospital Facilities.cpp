#include <iostream>
#include <iomanip>
#include <set>
#include <string>
#include <vector>

using namespace std;

enum class EventType
{
	ROOM_READY,
	ROOM_FINISHED,
};

struct Event
{
	EventType et;
	int minute;
	Event(EventType type, int minute) : et(type), minute(minute) {};
	bool operator<(const Event &e) const
	{
		if (minute < e.minute) return true;
		else if (minute == e.minute) {
			if (et != e.et && et == EventType::ROOM_READY) return true;
			else return false;
		}
		else return false;
	}
};

struct Room
{
	int no;
	int StartingTime, UsedTime;
	size_t PatientIndex;
	int AvailableTime, EndTime;
	Room(int no, int StartingTime) : no(no), StartingTime(StartingTime),
		UsedTime(0), AvailableTime(0), EndTime(0) {};
};

struct Patient
{
	string name;
	int SurgeyTime, RecoveryTime;
	size_t RoomNo, BedNo;
	int SurgeryStartingTime, SurgeryEndTime;
	int RecoveryStartingTime, RecoveryEndTime;
	Patient()
	{
		RoomNo = 0, BedNo = 0;
		SurgeryStartingTime = 0, SurgeryEndTime = 0;
		RecoveryStartingTime = 0, RecoveryEndTime = 0;
	}
};

istream& operator >> (istream &is, Patient &patient)
{
	is >> patient.name >> patient.SurgeyTime >> patient.RecoveryTime;
	return is;
}

void ProcessRoomReady(set<Event> &events, vector<Room> &rooms, vector<Room> &beds, vector<Patient> &patients, size_t &PatientIndex, int current)
{
	for (Room &room : rooms)
	{
		if (room.AvailableTime == current) {
			if (room.StartingTime == -1) {
				room.StartingTime = current;
			}
			room.UsedTime += patients[PatientIndex].SurgeyTime;
			room.PatientIndex = PatientIndex;
			room.EndTime = current + patients[PatientIndex].SurgeyTime;
			patients[PatientIndex].RoomNo = room.no;
			patients[PatientIndex].SurgeryStartingTime = current;
			patients[PatientIndex].SurgeryEndTime = patients[PatientIndex].SurgeryStartingTime + patients[PatientIndex].SurgeyTime;
			events.insert(Event(EventType::ROOM_FINISHED, room.EndTime));
			PatientIndex++;
			if (PatientIndex == patients.size()) {
				break;
			}
		}
	}
}

void ProcessRoomFinished(set<Event> &events, vector<Room> &rooms, vector<Room> &beds, vector<Patient> &patients,
	int current, int O2RTime, int PrepareRoom, int PrepareBed)
{
	for (Room &room : rooms)
	{
		if (room.EndTime == current) {
			room.AvailableTime = current + PrepareRoom;
			events.insert(Event(EventType::ROOM_READY, room.AvailableTime));
			for (Room &bed : beds)
			{
				if (bed.AvailableTime <= current) {
					if (bed.StartingTime == 0) {
						bed.StartingTime = current + O2RTime;
					}
					bed.UsedTime += patients[room.PatientIndex].RecoveryTime;
					bed.PatientIndex = room.PatientIndex;
					bed.EndTime = current + O2RTime + patients[room.PatientIndex].RecoveryTime;
					bed.AvailableTime = bed.EndTime + PrepareBed;
					patients[room.PatientIndex].BedNo = bed.no;
					patients[room.PatientIndex].RecoveryStartingTime = current + O2RTime;
					patients[room.PatientIndex].RecoveryEndTime = patients[room.PatientIndex].RecoveryStartingTime + patients[room.PatientIndex].RecoveryTime;
					break;
				}
			}
		}
	}
}

void PrintPatient(const vector<Patient> &patients, int StartingHour)
{
	cout << " Patient          Operating Room          Recovery Room" << endl;
	cout << " #  Name     Room#  Begin   End      Bed#  Begin    End" << endl;
	cout << " ------------------------------------------------------" << endl;
	for (size_t i = 0; i < patients.size(); i++)
	{
		cout << setw(2) << setfill(' ') << i + 1 << "  ";
		cout << patients[i].name << string(9 - patients[i].name.length(), ' ') << ' ';
		cout << setw(2) << patients[i].RoomNo << "   ";
		cout << setw(2) << setfill(' ') << StartingHour + patients[i].SurgeryStartingTime / 60 << ':' << setw(2) << setfill('0') << patients[i].SurgeryStartingTime % 60 << "   ";
		cout << setw(2) << setfill(' ') << StartingHour + patients[i].SurgeryEndTime / 60 << ':' << setw(2) << setfill('0') << patients[i].SurgeryEndTime % 60 << "     ";
		cout << setw(2) << setfill(' ') << patients[i].BedNo << "   ";
		cout << setw(2) << setfill(' ') << StartingHour + patients[i].RecoveryStartingTime / 60 << ':' << setw(2) << setfill('0') << patients[i].RecoveryStartingTime % 60 << "   ";
		cout << setw(2) << setfill(' ') << StartingHour + patients[i].RecoveryEndTime / 60 << ':' << setw(2) << setfill('0') << patients[i].RecoveryEndTime % 60;
		cout << endl;
	}
	cout << endl;
}

void PrintRoomAndBed(const vector<Patient> &patients, const vector<Room> &rooms, const vector<Room> &beds)
{
	int LastLeaveBed = 0;
	for (const Patient &patient : patients)
	{
		if (patient.RecoveryEndTime > LastLeaveBed) {
			LastLeaveBed = patient.RecoveryEndTime;
		}
	}
	cout << "Facility Utilization" << endl;
	cout << "Type  # Minutes  % Used" << endl;
	cout << "-------------------------" << endl;
	for (size_t i = 0; i < rooms.size(); i++)
	{
		cout << "Room " << setw(2) << setfill(' ') << i + 1 << "    " << setw(4) << rooms[i].UsedTime << "  ";
		cout << fixed << setw(6) << setfill(' ') << setprecision(2);
		if (LastLeaveBed == 0) cout << 0.0 << endl;
		else cout << 100.0 * rooms[i].UsedTime / LastLeaveBed << endl;
	}
	for (size_t i = 0; i < beds.size(); i++)
	{
		cout << "Bed  " << setw(2) << setfill(' ') << i + 1 << "    " << setw(4) << beds[i].UsedTime << "  ";
		cout << fixed << setw(6) << setfill(' ') << setprecision(2);
		if (LastLeaveBed == 0) cout << 0.0 << endl;
		else cout << 100.0 * beds[i].UsedTime / LastLeaveBed << endl;
	}
	cout << endl;
}

void simiulation(vector<Room> &rooms, vector<Room> &beds, vector<Patient> &patients,
	int StartingHour, int O2RTime, int PrepareRoom, int PrepareBed)
{
	set<Event> events;
	events.insert(Event(EventType::ROOM_READY, 0));
	size_t PatientIndex = 0;
	while (!events.empty()) {
		const Event &event = *events.begin();
		switch (event.et)
		{
		case EventType::ROOM_READY:
			if (PatientIndex == patients.size()) {
				break;
			}
			ProcessRoomReady(events, rooms, beds, patients, PatientIndex, event.minute);
			break;
		case EventType::ROOM_FINISHED:
			ProcessRoomFinished(events, rooms, beds, patients, event.minute, O2RTime, PrepareRoom, PrepareBed);
			break;
		default:
			break;
		}
		events.erase(events.begin());
	}
	PrintPatient(patients, StartingHour);
	PrintRoomAndBed(patients, rooms, beds);
}

int main()
{
	int RoomNum, BedNum, StartingHour, O2RTime, PrepareRoom, PrepareBed, PatientNum;
	while (cin >> RoomNum) {
		cin >> BedNum >> StartingHour >> O2RTime >> PrepareRoom >> PrepareBed >> PatientNum;
		vector<Patient> patients;
		for (int i = 0; i < PatientNum; i++)
		{
			Patient patient;
			cin >> patient;
			patients.push_back(patient);
		}
		vector<Room> rooms, beds;
		for (int i = 0; i < RoomNum; i++)
		{
			rooms.push_back(Room(i + 1, -1));
		}
		for (int i = 0; i < BedNum; i++)
		{
			beds.push_back(Room(i + 1, 0));
		}
		simiulation(rooms, beds, patients, StartingHour, O2RTime, PrepareRoom, PrepareBed);
	}
	return 0;
}
/*
5 12 07 5 15 10 16
Jones
28 140
Smith
120 200
Thompson
23 75
Albright
19 82
Poucher
133 209
Comer
74 101
Perry
93 188
Page
111 223
Roggio
69 122
Brigham
42 79
Nute
22 71
Young
38 140
Bush
26 121
Cates
120 248
Johnson
86 181
White
92 140
*/
