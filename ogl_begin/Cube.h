#pragma once
#include<iostream>
#include<fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include<vector>

enum Facet
{
	Top = 0,
	Bottom = 1,
	Front = 2,
	Back = 3,
	Left = 4,
	Right = 5
};

enum Color
{
	R = 0,
	B,
	Y,
	O,
	G,
	W
};

class Cube
{
	char cube[6][3][3];
	void turnMatrix(int facet, bool cw);
	char colors[6] = { 'R', 'B', 'Y', 'O', 'G', 'W' };
	std::map<std::set<char>, int> centerCubes = { {{'R','O'}, 0}, {{'B','G'}, 0}, {{'Y','W'}, 0} };

	std::map<std::set<char>, int> middleCubes = { {{'R','B'}, 0}, {{'B','Y'}, 0}, {{'Y','O'}, 0},
												  {{'O','G'}, 0}, {{'G','W'}, 0}, {{'W','R'}, 0},
												  {{'R','Y'}, 0}, {{'B','O'}, 0}, {{'Y','G'}, 0},
												  {{'O','W'}, 0}, {{'G','R'}, 0}, {{'B','W'}, 0}
	};

	std::map<std::set<char>, int> cornerCubes = { {{'W','G','O'}, 0}, {{'G','O','Y'}, 0},
												  {{'O','Y','B'}, 0}, {{'Y','B','R'}, 0},
												  {{'B','R','W'}, 0}, {{'R','W','G'}, 0},
												  {{'W','O','B'}, 0}, {{'G','Y','R'}, 0}
	};
public:
	Cube();
	bool checkState();
	friend std::ostream& operator<<(std::ostream& out, Cube& cube);
	void LoadFromFile(std::string filename);
	void F(bool cw = true);
	void B(bool cw = true);
	void L(bool cw = true);
	void R(bool cw = true);
	void U(bool cw = true);
	void D(bool cw = true);
	void Mixing();
	long long getHash();
	std::vector<std::string> cubeSolve();
	void getCross();
	bool checkCross();
	bool checkSecondLayer();
	bool checkCornerCubes();
	bool checkCentreCubes();
	bool checkBottomCross();
	bool checkSideCubesBottomLayer();
	bool checkCornerCubesBottomLayer();
	bool checkThirdLayer();
	bool checkLastLayer();
	void getSecondLayer();
	void getCentreCubes();
	void getCornerCubes();
	void getBottonCross();
	void getSideCubesBottomLayer();
	void getCornerCubesBottomLayer();
	void getThirdLayer();
	std::vector<std::string> answer;
	std::vector<std::string> mix;
};

/*
��������:

1) F > front - ����������� ��� ����� �� ������� �������.

2) B > back - ������ ��� ������� ������� �� ������� �������.
�������������� ���, ��� ����� ������� ��������� � ���!

3) L > left - ����� ������� �� ������� �������.

4) R > right - ������ ������� �� ������� �������.

5) U > up - ������� ������� �� ������� �������.

6) D > down - ������ ������� �� ������� �������.

//////////////////////////////////////////////////
7) M > middle - ������� ����, ����������� ����� ������ (R) � ����� (L) �������, ������������ ����(������� �� ������� �������).

8) M` > middle - ������� ����, ����������� ����� ������ (R) � ����� (L) �������, ������������ �����(������� ������ ������� �������).

9) S > standing - ������� ����, ����������� ����� ����������� (F) � ������ (B) ���������, �� ������� �������.

10) S`> standing - ������� ����, ����������� ����� ����������� � ������ ���������, ������ ������� �������.

11) E > equatorial - ������� ����, ����������� ����� ������� (U) � ������ (D) ���������, ������������ �����(������� �� ������� �������, ���� �������� ������ �� ���).

12) E`> equatorial - ������� ����, ����������� ����� ������� � ������ ���������,  ������������ ������(������� ������ ������� �������, ���� �������� ������ �� ���).



*/