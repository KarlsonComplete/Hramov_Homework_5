#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;
const int string_len = 5;
	
struct Motor {
	string volume;
	int Horsepower;
};

struct Plane {
	string Country;
	int CapacityPeople;
	float Speed;
	Motor motor;
};

void showPlane(const Plane p) {
	cout << p.Country << "\t"
		<< p.CapacityPeople << "\t"
		<< p.Speed << "\t\t["
		<< p.motor.Horsepower << "]" << endl;
}

void showPlane(const Plane sts[], const int len) {
	cout << "Country \t"
		<< "CapacityPeople \t"
		<< "Speed \t["
		<< "Horsepower]" << endl;

	for (int i = 0; i < len; i++) {
		showPlane(sts[i]);
	}

	cout << endl;
}

void randString(string& str, const int len) {
	static const char alphabet[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// очищаем и заносим данные
	str.clear();
	str.append(len, ' ');

	for (int i = 0; i < str.length(); i++) {
		int r = rand() % (sizeof(alphabet) - 1);
		str[i] = alphabet[r];
	}
	str[str.length()] = 0;  // последний символ сообщает о том, что строка закончилась
}

void initStudents(Plane sts[], const int len) {
	for (int i = 0; i < len; i++) {
		// Student
		sts[i].CapacityPeople = rand() % 25;
		sts[i].Speed = 5.0 * (float)rand() / RAND_MAX;
		randString(sts[i].Country, string_len);

		// Address
		randString(sts[i].motor.volume, string_len);
		sts[i].motor.Horsepower = rand() % 25;
		
	}
}

void writeTextFile(const Plane sts[], const int l) {
	ofstream f;

	f.open("data.txt");
	for (int i = 0; i < l; i++)  // Все атрибуты struct  в одной строке
		f << sts[i].Country << " "
		<< sts[i].CapacityPeople << " "
		<< sts[i].Speed << " "
		<< sts[i].motor.Horsepower << endl;
	f.close();
}

void openTextFile(Plane sts[], const int l) {
	ifstream f;

	f.open("data.txt");
	for (int i = 0; i < l; i++)
		f >> sts[i].Country
		>> sts[i].CapacityPeople
		>> sts[i].Speed
		>> sts[i].motor.Horsepower;
	f.close();
}

void writeBinFile(Plane sts[], const int l) {
	fstream f;
	f.open("data.bin.txt", ios::out | ios::binary);
	f.write((char*)sts, sizeof(Plane) * l);
	f.close();
}

void openBinFile(Plane sts[], const int l) {
	fstream f;
	f.open("data.bin.txt", ios::in | ios::binary);
	f.read((char*)sts, sizeof(Plane) * l);
	f.close();
}

int main()
{
	// init
	cout.precision(3);
	srand(5);

	const int len = 10;
	Plane planes[len];

	cout << "Начальный массив:\n";
	initStudents(planes, len);
	writeTextFile(planes, len);
	showPlane(planes, 5);

	cout << "Новый массив:\n";
	initStudents(planes, len);
	showPlane(planes, 5);

	cout << "Считанный массив:\n";
	openTextFile(planes, len);
	showPlane(planes, 5);

	cout << "Бинарный файл.\n";
	writeBinFile(planes, len);

	cout << "Новый массив:\n";
	initStudents(planes, len);
	showPlane(planes, 5);

	cout << "Считанный массив:\n";
	openBinFile(planes, len);
	showPlane(planes, 5);

	return 0;
}


