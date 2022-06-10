#include"Cube.h"
#include"MainCube.h"
#include <windows.h>
#include <gl/gl.h>
#define _USE_MATH_DEFINES
#include<cmath>
#include<array>
#include<vector>
#include<string>
#include<algorithm>

#pragma comment(lib, "opengl32.lib")

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

POINTFLOAT vertices[] = { {-0.5, 0.5}, {0.5, 0.5}, {-0.5, -0.5}, {0.5, -0.5} };

float colors[] = { 1,0,1,   0,1,1,   0,0,1};
GLuint index[] = { 0, 1, 2, 3 };

float peaks[] = { 2,2,0,   -2,0,3,   2, -2, 0 };
float peaks_2[] = { -1,1,0,   2,0,3,   -1, -1, 0 };

float BottomFacet[] = { 1,1,-1,    -1,1,-1,    1,-1,-1,   -1,-1,-1 };
float LeftFacet[]  = { -1,-1,-1, -1,-1,1, -1,1,-1,  -1,1,1 };
float RightFacet[] = { 1,-1,-1,  1,-1,1,  1,1,-1,   1,1,1  };
float BackFacet[]  = { -1,1,-1,  -1,1,1,  1,1,-1,   1,1,1  };
float UpFacet[]    = { -1,-1,1, -1,1,1,  1,-1,1,   1,1,1 };
float FrontFacet[] = { -1,-1,-1, -1,-1,1, 1,-1,-1,  1,-1,1 };

float cube_1[24] = { 1,1,-1,  1,1 - offset,-1,  1 - offset,1 - offset,-1,  1 - offset,1,-1,  
					 1,1,1 - 2 * offset,  1,1 - offset,1 - 2 * offset,  1 - offset,1 - offset,1 - 2 * offset,  1 - offset,1,1 - 2 * offset};

float cube_2[24]; 
float cube_3[24]; 
float cube_4[24];
float cube_5[24];
float cube_6[24];
float cube_7[24];
float cube_8[24];
float cube_9[24];
float cube_10[24];
float cube_11[24];
float cube_12[24];
float cube_13[24];
float cube_14[24];
float cube_15[24];
float cube_16[24];
float cube_17[24];
float cube_18[24];
float cube_19[24];
float cube_20[24];
float cube_21[24];
float cube_22[24];
float cube_23[24];
float cube_24[24];
float cube_25[24];
float cube_26[24];
float cube_27[24];

std::vector<std::vector<std::vector<float>>> ColorMass;
std::vector<std::vector<std::vector<float>>> saved_cubes(2);
std::vector<std::string> sample = { "D'", "B", "U"};

bool stop = false;

float* matr[27] = { cube_1, cube_2, cube_3, cube_4, cube_5, cube_6, cube_7, cube_8, cube_9, cube_10, cube_11,
					cube_12, cube_13, cube_14, cube_15, cube_16, cube_17, cube_18, cube_19, cube_20, cube_21,
					cube_22, cube_23, cube_24, cube_25, cube_26, cube_27 };

void ChangeVecSize()
{
	ColorMass.resize(27);

	for (int i = 0; i < 27; i++)
		ColorMass[i].resize(6);
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			ColorMass[i][j].resize(3);
		}
	}

	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				ColorMass[i][j][k] = 0;
			}
		}
	}

	for (int i = 0; i < 2; i++)
		saved_cubes[i].resize(6);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 6; j++)
			saved_cubes[i][j].resize(3);

}

void FillVector()
{
	for (int i = 0; i < 9; i++)
	{
		ColorMass[i][0][0] = 1;
		ColorMass[i][0][1] = 1;
		ColorMass[i][0][2] = 1;
	}

	for (int i = 0; i <= 18; i += 9)
	{
		ColorMass[i][2][0] = 1;
		ColorMass[i][2][1] = 0;
		ColorMass[i][2][2] = 0;

		ColorMass[i+1][2][0] = 1;
		ColorMass[i+1][2][1] = 0;
		ColorMass[i+1][2][2] = 0;

		ColorMass[i+2][2][0] = 1;
		ColorMass[i+2][2][1] = 0;
		ColorMass[i+2][2][2] = 0;
	}

	for (int i = 2; i <= 20; i += 9)
	{
		ColorMass[i][3][0] = 0;
		ColorMass[i][3][1] = 0;
		ColorMass[i][3][2] = 1;

		ColorMass[i + 3][3][0] = 0;
		ColorMass[i + 3][3][1] = 0;
		ColorMass[i + 3][3][2] = 1;

		ColorMass[i + 6][3][0] = 0;
		ColorMass[i + 6][3][1] = 0;
		ColorMass[i + 6][3][2] = 1;
	}

	for (int i = 6; i <= 24; i+=9)
	{
		ColorMass[i][4][0] = 1;
		ColorMass[i][4][1] = 0.5;
		ColorMass[i][4][2] = 0;

		ColorMass[i + 1][4][0] = 1;
		ColorMass[i + 1][4][1] = 0.5;
		ColorMass[i + 1][4][2] = 0;

		ColorMass[i + 2][4][0] = 1;
		ColorMass[i + 2][4][1] = 0.5;
		ColorMass[i + 2][4][2] = 0;
	}

	for (int i = 18; i <= 26; i++)
	{
		ColorMass[i][5][0] = 1;
		ColorMass[i][5][1] = 1;
		ColorMass[i][5][2] = 0;
	}

	for (int i = 0; i <= 18; i += 9)
	{
		ColorMass[i][1][0] = 0;
		ColorMass[i][1][1] = 1;
		ColorMass[i][1][2] = 0;

		ColorMass[i + 3][1][0] = 0;
		ColorMass[i + 3][1][1] = 1;
		ColorMass[i + 3][1][2] = 0;

		ColorMass[i + 6][1][0] = 0;
		ColorMass[i + 6][1][1] = 1;
		ColorMass[i + 6][1][2] = 0;
	}
}

void CubeInit()
{
	for (int i = 2; i < 24; i += 3)
	{
		cube_10[i] = cube_1[i] + offset;
		cube_19[i] = cube_1[i] + 2 * offset;

		cube_10[i - 1] = cube_1[i-1];
		cube_10[i - 2] = cube_1[i-2];
		cube_19[i - 1] = cube_1[i-1];
		cube_19[i - 2] = cube_1[i-2];
	}

	for (int i = 0; i < 24; i += 3)
	{
		cube_4[i] = cube_1[i] - offset;
		cube_7[i] = cube_1[i] - 2 * offset;

		cube_4[i+1] = cube_1[i+1];
		cube_4[i+2] = cube_1[i+2];
		cube_7[i+1] = cube_1[i+1];
		cube_7[i+2] = cube_1[i+2];


		cube_13[i] = cube_10[i] - offset;
		cube_16[i] = cube_10[i] - 2 * offset;

		cube_13[i+1] = cube_10[i+1];
		cube_13[i+2] = cube_10[i+2];
		cube_16[i+1] = cube_10[i+1];
		cube_16[i+2] = cube_10[i+2];

		cube_22[i] = cube_19[i] - offset;
		cube_25[i] = cube_19[i] - 2 * offset;

		cube_22[i+1] = cube_19[i+1];
		cube_22[i+2] = cube_19[i+2];
		cube_25[i+1] = cube_19[i+1];
		cube_25[i+2] = cube_19[i+2];
	}

	for (int i = 1; i < 24; i += 3)
	{
		cube_2[i] = cube_1[i] - offset;
		cube_3[i] = cube_1[i] - 2 * offset;

		cube_2[i+1] = cube_1[i+1];
		cube_2[i-1] = cube_1[i-1];
		cube_3[i+1] = cube_1[i+1];
		cube_3[i-1] = cube_1[i-1];

		cube_5[i] = cube_4[i] - offset;
		cube_6[i] = cube_4[i] - 2 * offset;

		cube_5[i+1] = cube_4[i+1];
		cube_5[i-1] = cube_4[i-1];
		cube_6[i+1] = cube_4[i+1];
		cube_6[i-1] = cube_4[i-1];

		cube_8[i] = cube_7[i] - offset;
		cube_9[i] = cube_7[i] - 2 * offset;

		cube_8[i+1] = cube_7[i+1];
		cube_8[i-1] = cube_7[i-1];
		cube_9[i+1] = cube_7[i+1];
		cube_9[i-1] = cube_7[i-1];

		cube_11[i] = cube_10[i] - offset;
		cube_12[i] = cube_10[i] - 2 * offset;

		cube_11[i+1] = cube_10[i+1];
		cube_11[i-1] = cube_10[i-1];
		cube_12[i+1] = cube_10[i+1];
		cube_12[i-1] = cube_10[i-1];

		cube_14[i] = cube_13[i] - offset;
		cube_15[i] = cube_13[i] - 2 * offset;

		cube_14[i+1] = cube_13[i+1];
		cube_14[i-1] = cube_13[i-1];
		cube_15[i+1] = cube_13[i+1];
		cube_15[i-1] = cube_13[i-1];

		cube_17[i] = cube_16[i] - offset;
		cube_18[i] = cube_16[i] - 2 * offset;

		cube_17[i+1] = cube_16[i+1];
		cube_17[i-1] = cube_16[i-1];
		cube_18[i+1] = cube_16[i+1];
		cube_18[i-1] = cube_16[i-1];

		cube_20[i] = cube_19[i] - offset;
		cube_21[i] = cube_19[i] - 2 * offset;

		cube_20[i+1] = cube_19[i+1];
		cube_20[i-1] = cube_19[i-1];
		cube_21[i+1] = cube_19[i+1];
		cube_21[i-1] = cube_19[i-1];

		cube_23[i] = cube_22[i] - offset;
		cube_24[i] = cube_22[i] - 2 * offset;

		cube_23[i+1] = cube_22[i+1];
		cube_23[i-1] = cube_22[i-1];
		cube_24[i+1] = cube_22[i+1];
		cube_24[i-1] = cube_22[i-1];

		cube_26[i] = cube_25[i] - offset;
		cube_27[i] = cube_25[i] - 2 * offset;

		cube_26[i+1] = cube_25[i+1];
		cube_26[i-1] = cube_25[i-1];
		cube_27[i+1] = cube_25[i+1];
		cube_27[i-1] = cube_25[i-1];
	}
}

void ChangeColors_R(int f, int s, bool cw = true)
{
	if (cw)
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[f][0][i] = ColorMass[s][1][i];
			ColorMass[f][1][i] = ColorMass[s][5][i];
			ColorMass[f][2][i] = ColorMass[s][2][i];
			ColorMass[f][3][i] = ColorMass[s][0][i];
			ColorMass[f][4][i] = ColorMass[s][4][i];
			ColorMass[f][5][i] = ColorMass[s][3][i];
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[f][1][i] = ColorMass[s][0][i];
			ColorMass[f][5][i] = ColorMass[s][1][i];
			ColorMass[f][2][i] = ColorMass[s][2][i];
			ColorMass[f][0][i] = ColorMass[s][3][i];
			ColorMass[f][4][i] = ColorMass[s][4][i];
			ColorMass[f][3][i] = ColorMass[s][5][i];
		}
	}
}

void ChangeColors_saved_cubes_R(int n, int n2, bool cw = true)
{
	if (cw)
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[n][0][i] = saved_cubes[0][1][i];
			ColorMass[n][1][i] = saved_cubes[0][5][i];
			ColorMass[n][2][i] = saved_cubes[0][2][i];
			ColorMass[n][3][i] = saved_cubes[0][0][i];
			ColorMass[n][4][i] = saved_cubes[0][4][i];
			ColorMass[n][5][i] = saved_cubes[0][3][i];

			ColorMass[n2][0][i] = saved_cubes[1][1][i];
			ColorMass[n2][1][i] = saved_cubes[1][5][i];
			ColorMass[n2][2][i] = saved_cubes[1][2][i];
			ColorMass[n2][3][i] = saved_cubes[1][0][i];
			ColorMass[n2][4][i] = saved_cubes[1][4][i];
			ColorMass[n2][5][i] = saved_cubes[1][3][i];
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[n][1][i] = saved_cubes[0][0][i];
			ColorMass[n][5][i] = saved_cubes[0][1][i];
			ColorMass[n][2][i] = saved_cubes[0][2][i];
			ColorMass[n][0][i] = saved_cubes[0][3][i];
			ColorMass[n][4][i] = saved_cubes[0][4][i];
			ColorMass[n][3][i] = saved_cubes[0][5][i];

			ColorMass[n2][1][i] = saved_cubes[1][0][i];
			ColorMass[n2][5][i] = saved_cubes[1][1][i];
			ColorMass[n2][2][i] = saved_cubes[1][2][i];
			ColorMass[n2][0][i] = saved_cubes[1][3][i];
			ColorMass[n2][4][i] = saved_cubes[1][4][i];
			ColorMass[n2][3][i] = saved_cubes[1][5][i];
		}
	}
}

void ChangeColors_F(int f, int s, bool cw = true)
{
	if (cw)
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[f][0][i] = ColorMass[s][2][i];
			ColorMass[f][1][i] = ColorMass[s][1][i];
			ColorMass[f][2][i] = ColorMass[s][5][i];
			ColorMass[f][3][i] = ColorMass[s][3][i];
			ColorMass[f][4][i] = ColorMass[s][0][i];
			ColorMass[f][5][i] = ColorMass[s][4][i];
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[f][2][i] = ColorMass[s][0][i];
			ColorMass[f][1][i] = ColorMass[s][1][i];
			ColorMass[f][5][i] = ColorMass[s][2][i];
			ColorMass[f][3][i] = ColorMass[s][3][i];
			ColorMass[f][0][i] = ColorMass[s][4][i];
			ColorMass[f][4][i] = ColorMass[s][5][i];
		}
	}
}

void ChangeColors_saved_cubes_F(int n, int n2, bool cw = true)
{
	if (cw)
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[n][0][i] = saved_cubes[0][2][i];
			ColorMass[n][1][i] = saved_cubes[0][1][i];
			ColorMass[n][2][i] = saved_cubes[0][5][i];
			ColorMass[n][3][i] = saved_cubes[0][3][i];
			ColorMass[n][4][i] = saved_cubes[0][0][i];
			ColorMass[n][5][i] = saved_cubes[0][4][i];

			ColorMass[n2][0][i] = saved_cubes[1][2][i];
			ColorMass[n2][1][i] = saved_cubes[1][1][i];
			ColorMass[n2][2][i] = saved_cubes[1][5][i];
			ColorMass[n2][3][i] = saved_cubes[1][3][i];
			ColorMass[n2][4][i] = saved_cubes[1][0][i];
			ColorMass[n2][5][i] = saved_cubes[1][4][i];
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[n][2][i] = saved_cubes[0][0][i];
			ColorMass[n][1][i] = saved_cubes[0][1][i];
			ColorMass[n][5][i] = saved_cubes[0][2][i];
			ColorMass[n][3][i] = saved_cubes[0][3][i];
			ColorMass[n][0][i] = saved_cubes[0][4][i];
			ColorMass[n][4][i] = saved_cubes[0][5][i];

			ColorMass[n2][2][i] = saved_cubes[1][0][i];
			ColorMass[n2][1][i] = saved_cubes[1][1][i];
			ColorMass[n2][5][i] = saved_cubes[1][2][i];
			ColorMass[n2][3][i] = saved_cubes[1][3][i];
			ColorMass[n2][0][i] = saved_cubes[1][4][i];
			ColorMass[n2][4][i] = saved_cubes[1][5][i];
		}
	}
}

void ChangeColors_U(int f, int s, bool cw = true)
{
	if (cw)
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[f][0][i] = ColorMass[s][0][i];
			ColorMass[f][1][i] = ColorMass[s][4][i];
			ColorMass[f][2][i] = ColorMass[s][1][i];
			ColorMass[f][3][i] = ColorMass[s][2][i];
			ColorMass[f][4][i] = ColorMass[s][3][i];
			ColorMass[f][5][i] = ColorMass[s][5][i];
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[f][0][i] = ColorMass[s][0][i];
			ColorMass[f][4][i] = ColorMass[s][1][i];
			ColorMass[f][1][i] = ColorMass[s][2][i];
			ColorMass[f][2][i] = ColorMass[s][3][i];
			ColorMass[f][3][i] = ColorMass[s][4][i];
			ColorMass[f][5][i] = ColorMass[s][5][i];
		}
	}
}

void ChangeColors_saved_cubes_U(int n, int n2, bool cw = true)
{
	if (cw)
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[n][0][i] = saved_cubes[0][0][i];
			ColorMass[n][1][i] = saved_cubes[0][4][i];
			ColorMass[n][2][i] = saved_cubes[0][1][i];
			ColorMass[n][3][i] = saved_cubes[0][2][i];
			ColorMass[n][4][i] = saved_cubes[0][3][i];
			ColorMass[n][5][i] = saved_cubes[0][5][i];

			ColorMass[n2][0][i] = saved_cubes[1][0][i];
			ColorMass[n2][1][i] = saved_cubes[1][4][i];
			ColorMass[n2][2][i] = saved_cubes[1][1][i];
			ColorMass[n2][3][i] = saved_cubes[1][2][i];
			ColorMass[n2][4][i] = saved_cubes[1][3][i];
			ColorMass[n2][5][i] = saved_cubes[1][5][i];
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			ColorMass[n][0][i] = saved_cubes[0][0][i];
			ColorMass[n][4][i] = saved_cubes[0][1][i];
			ColorMass[n][1][i] = saved_cubes[0][2][i];
			ColorMass[n][2][i] = saved_cubes[0][3][i];
			ColorMass[n][3][i] = saved_cubes[0][4][i];
			ColorMass[n][5][i] = saved_cubes[0][5][i];

			ColorMass[n2][0][i] = saved_cubes[1][0][i];
			ColorMass[n2][4][i] = saved_cubes[1][1][i];
			ColorMass[n2][1][i] = saved_cubes[1][2][i];
			ColorMass[n2][2][i] = saved_cubes[1][3][i];
			ColorMass[n2][3][i] = saved_cubes[1][4][i];
			ColorMass[n2][5][i] = saved_cubes[1][5][i];
		}
	}
}

void R2(bool cw = true)
{
	if (cw)
	{
		ChangeColors_R(0, 18);
		ChangeColors_R(18, 20);
		ChangeColors_R(20, 2);

		ChangeColors_R(1, 9);
		ChangeColors_R(9, 19);
		ChangeColors_R(19, 11);

		ChangeColors_saved_cubes_R(2, 11);
	}
	else
	{
		ChangeColors_R(0, 2, false);
		ChangeColors_R(2, 20, false);
		ChangeColors_R(20, 18, false);

		ChangeColors_R(1, 11, false);
		ChangeColors_R(11, 19, false);
		ChangeColors_R(19, 9, false);

		ChangeColors_saved_cubes_R(18, 9, false);
	}

}
void F2(bool cw = true)
{
	if (cw)
	{
		ChangeColors_F(2, 20);
		ChangeColors_F(20, 26);
		ChangeColors_F(26, 8);

		ChangeColors_F(5, 11);
		ChangeColors_F(11, 23);
		ChangeColors_F(23, 17);

		ChangeColors_saved_cubes_F(8, 17);
	}
	else
	{
		ChangeColors_F(2, 8, false);
		ChangeColors_F(8, 26, false);
		ChangeColors_F(26, 20, false);

		ChangeColors_F(5, 17, false);
		ChangeColors_F(17, 23, false);
		ChangeColors_F(23, 11, false);

		ChangeColors_saved_cubes_F(20, 11, false);
	}
}
void L2(bool cw = true)
{
	if (cw)
	{
		ChangeColors_R(6, 8, false);
		ChangeColors_R(8, 26, false);
		ChangeColors_R(26, 24, false);

		ChangeColors_R(7, 17, false);
		ChangeColors_R(17, 25, false);
		ChangeColors_R(25, 15, false);

		ChangeColors_saved_cubes_R(24, 15, false);
	}
	else
	{

		ChangeColors_R(6, 24);
		ChangeColors_R(24, 26);
		ChangeColors_R(26, 8);

		ChangeColors_R(7, 15);
		ChangeColors_R(15, 25);
		ChangeColors_R(25, 17);

		ChangeColors_saved_cubes_R(8, 17);
	}
}
void B2(bool cw = true)
{
	if (cw)
	{
		ChangeColors_F(0, 6, false);
		ChangeColors_F(6, 24, false);
		ChangeColors_F(24, 18, false);

		ChangeColors_F(3, 15, false);
		ChangeColors_F(15, 21, false);
		ChangeColors_F(21, 9, false);

		ChangeColors_saved_cubes_F(18, 9, false);

	}
	else
	{
		ChangeColors_F(0, 18);
		ChangeColors_F(18, 24);
		ChangeColors_F(24, 6);

		ChangeColors_F(3, 9);
		ChangeColors_F(9, 21);
		ChangeColors_F(21, 15);

		ChangeColors_saved_cubes_F(6, 15);
	}
}
void U2(bool cw = true)
{
	if (cw)
	{
		ChangeColors_U(18, 24);
		ChangeColors_U(24, 26);
		ChangeColors_U(26, 20);

		ChangeColors_U(19, 21);
		ChangeColors_U(21, 25);
		ChangeColors_U(25, 23);

		ChangeColors_saved_cubes_U(20, 23);

	}
	else
	{
		ChangeColors_U(18, 20, false);
		ChangeColors_U(20, 26, false);
		ChangeColors_U(26, 24, false);


		ChangeColors_U(19, 23, false);
		ChangeColors_U(23, 25, false);
		ChangeColors_U(25, 21, false);

		ChangeColors_saved_cubes_U(24, 21, false);
	}
}
void D2(bool cw = true)
{
	if (cw)
	{
		ChangeColors_U(0, 2, false);
		ChangeColors_U(2, 8, false);
		ChangeColors_U(8, 6, false);


		ChangeColors_U(1, 5, false);
		ChangeColors_U(5, 7, false);
		ChangeColors_U(7, 3, false);

		ChangeColors_saved_cubes_U(6, 3, false);


	}
	else
	{
		ChangeColors_U(0, 6);
		ChangeColors_U(6, 8);
		ChangeColors_U(8, 2);

		ChangeColors_U(1, 3);
		ChangeColors_U(3, 7);
		ChangeColors_U(7, 5);

		ChangeColors_saved_cubes_U(2, 5);
	}
}

float xAlpha = 20;
float zAlpha = 0;
POINTFLOAT pos = { 0, 0 };
void Mix(const std::vector<std::string>& commands)
{
	for (auto i : commands)
	{
		if (i == "R")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[0][j][k];
					saved_cubes[1][j][k] = ColorMass[1][j][k];
				}
			R2();
			Sleep(100);
		}
		else if (i == "R'")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[0][j][k];
					saved_cubes[1][j][k] = ColorMass[1][j][k];
				}
			R2(false);
			Sleep(100);
		}
		else if (i == "L")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[6][j][k];
					saved_cubes[1][j][k] = ColorMass[7][j][k];
				}
			L2();
			Sleep(100);
		}
		else if (i == "L'")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[6][j][k];
					saved_cubes[1][j][k] = ColorMass[7][j][k];
				}
			L2(false);
			Sleep(100);
		}
		else if (i == "F")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[2][j][k];
					saved_cubes[1][j][k] = ColorMass[5][j][k];
				}
			F2();
			Sleep(100);
		}
		else if (i == "F'")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[2][j][k];
					saved_cubes[1][j][k] = ColorMass[5][j][k];
				}
			F2(false);
			Sleep(100);
		}
		else if (i == "B")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[0][j][k];
					saved_cubes[1][j][k] = ColorMass[3][j][k];
				}
			B2();
			Sleep(100);
		}
		else if (i == "B'")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[0][j][k];
					saved_cubes[1][j][k] = ColorMass[3][j][k];
				}
			B2(false);
			Sleep(100);
		}

		else if (i == "U")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[18][j][k];
					saved_cubes[1][j][k] = ColorMass[19][j][k];
				}
			U2();
			Sleep(100);
		}
		else if (i == "U'")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[18][j][k];
					saved_cubes[1][j][k] = ColorMass[19][j][k];
				}
			U2(false);
			Sleep(100);
		}
		else if (i == "D")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[0][j][k];
					saved_cubes[1][j][k] = ColorMass[1][j][k];
				}
			D2();
			Sleep(100);
		}
		else if (i == "D'")
		{
			for (int j = 0; j < 6; j++)
				for (int k = 0; k < 3; k++)
				{
					saved_cubes[0][j][k] = ColorMass[0][j][k];
					saved_cubes[1][j][k] = ColorMass[1][j][k];
				}
			D2(false);
			Sleep(100);
		}
	}
}

void ShowCube_2()
{
	for (int i = 0; i < 27; i++)
	{
		float* mass;
		mass = matr[i];
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(ColorMass[i][0][0], ColorMass[i][0][1], ColorMass[i][0][2]);
		glVertex3f(mass[0], mass[1], mass[2]);
		glVertex3f(mass[3], mass[4], mass[5]);
		glVertex3f(mass[6], mass[7], mass[8]);
		glVertex3f(mass[9], mass[10], mass[11]);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(ColorMass[i][1][0], ColorMass[i][1][1], ColorMass[i][1][2]);
		glVertex3f(mass[0], mass[1], mass[2]);
		glVertex3f(mass[9], mass[10], mass[11]);
		glVertex3f(mass[21], mass[22], mass[23]);
		glVertex3f(mass[12], mass[13], mass[14]);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(ColorMass[i][2][0], ColorMass[i][2][1], ColorMass[i][2][2]);
		glVertex3f(mass[0], mass[1], mass[2]);
		glVertex3f(mass[3], mass[4], mass[5]);
		glVertex3f(mass[15], mass[16], mass[17]);
		glVertex3f(mass[12], mass[13], mass[14]);
		glEnd();


		glBegin(GL_TRIANGLE_FAN);
		glColor3f(ColorMass[i][3][0], ColorMass[i][3][1], ColorMass[i][3][2]);
		glVertex3f(mass[3], mass[4], mass[5]);
		glVertex3f(mass[6], mass[7], mass[8]);
		glVertex3f(mass[18], mass[19], mass[20]);
		glVertex3f(mass[15], mass[16], mass[17]);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(ColorMass[i][4][0], ColorMass[i][4][1], ColorMass[i][4][2]);
		glVertex3f(mass[6], mass[7], mass[8]);
		glVertex3f(mass[9], mass[10], mass[11]);
		glVertex3f(mass[21], mass[22], mass[23]);
		glVertex3f(mass[18], mass[19], mass[20]);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(ColorMass[i][5][0], ColorMass[i][5][1], ColorMass[i][5][2]);
		glVertex3f(mass[12], mass[13], mass[14]);
		glVertex3f(mass[15], mass[16], mass[17]);
		glVertex3f(mass[18], mass[19], mass[20]);
		glVertex3f(mass[21], mass[22], mass[23]);
		glEnd();
	}
	glLineWidth(5);

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex3f(1 - offset, 1, -1);
	glVertex3f(1 - offset, -1, -1);
	glVertex3f(1 - offset, -1, 1);
	glVertex3f(1 - offset, 1, 1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex3f(-1 + offset, 1, -1);
	glVertex3f(-1 + offset, -1, -1);
	glVertex3f(-1 + offset, -1, 1);
	glVertex3f(-1 + offset, 1, 1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex3f(1, 1 - offset, -1);
	glVertex3f(-1, 1 - offset, -1);
	glVertex3f(-1, 1 - offset, 1);
	glVertex3f(1, 1 - offset, 1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex3f(1, -1 + offset, -1);
	glVertex3f(-1, -1 + offset, -1);
	glVertex3f(-1, -1 + offset, 1);
	glVertex3f(1, -1 + offset, 1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex3f(1, 1, 1 - offset);
	glVertex3f(1, -1, 1 - offset);
	glVertex3f(-1, -1, 1 - offset);
	glVertex3f(-1, 1, 1 - offset);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex3f(1, 1, -1 + offset);
	glVertex3f(1, -1, -1 + offset);
	glVertex3f(-1, -1, -1 + offset);
	glVertex3f(-1, 1, -1 + offset);
	glEnd();
}

void MoveCamera()
{
	if (GetKeyState(VK_UP) < 0) xAlpha = ++xAlpha > 180 ? 180 : xAlpha;
	if (GetKeyState(VK_DOWN) < 0) xAlpha = --xAlpha < 0 ? 0 : xAlpha;
	if (GetKeyState(VK_LEFT) < 0) zAlpha = ++zAlpha;
	if (GetKeyState(VK_RIGHT) < 0) zAlpha = --zAlpha;

	glRotatef(-xAlpha, 1, 0, 0);
	glRotatef(-zAlpha, 0, 0, 1);
}


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;
	float theta = 0.0f;

	/* register window class */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;

	/* create main window */
	hwnd = CreateWindowEx(0,
		"GLSample",
		"OpenGL Sample",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500,
		500,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);

	/* enable OpenGL for the window */
	EnableOpenGL(hwnd, &hDC, &hRC);

	//glOrtho(-5,5, -5, 5, -5, 5);

	glEnable(GL_DEPTH_TEST);

	glFrustum(-2,2, -2,2, 2, 20);
	ChangeVecSize();
	FillVector();
	glTranslatef(0, 0, -4);
	CubeInit();

	srand(time(0));
	Cube cube;
	cube.Mixing();

	/* program main loop */
	while (!bQuit)
	{
		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			/* OpenGL animation code goes here */
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			/*glRotatef(1, 0, 1, 0);

			glVertexPointer(3, GL_FLOAT, 0, &peaks);
			glEnableClientState(GL_VERTEX_ARRAY);

			glColor3f(1, 1, 1);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableClientState(GL_VERTEX_ARRAY);

			glVertexPointer(3, GL_FLOAT, 0, &peaks_2);
			glEnableClientState(GL_VERTEX_ARRAY);

			glColor3f(1, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableClientState(GL_VERTEX_ARRAY);*/

			glPushMatrix();

			MoveCamera();
			ShowCube_2();
			if (GetKeyState('M') < 0)
				Mix(cube.mix);
			if (GetKeyState('S') < 0)
			{
				std::vector<std::string> ans = cube.mix;
				std::reverse(ans.begin(), ans.end());
				for (int i = 0; i < ans.size(); i++)
				{
					if (ans[i] == "R")
						ans[i] = "R'";
					else if (ans[i] == "R'")
						ans[i] = "R";
					else if (ans[i] == "L")
						ans[i] = "L'";
					else if (ans[i] == "L'")
						ans[i] = "L";
					else if (ans[i] == "B")
						ans[i] = "B'";
					else if (ans[i] == "B'")
						ans[i] = "B";
					else if (ans[i] == "U")
						ans[i] = "U'";
					else if (ans[i] == "U'")
						ans[i] = "U";
					else if (ans[i] == "D")
						ans[i] = "D'";
					else if (ans[i] == "D'")
						ans[i] = "D";
					else if (ans[i] == "F")
						ans[i] = "F'";
					else if (ans[i] == "F'")
						ans[i] = "F";
				}
				Mix(ans);
			}

			Sleep(10);

			glPopMatrix();


			SwapBuffers(hDC);
			Sleep(1);
		}
	}

	/* shutdown OpenGL */
	DisableOpenGL(hwnd, hDC, hRC);

	/* destroy the window explicitly */
	DestroyWindow(hwnd);

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	/* get the device context (DC) */
	*hDC = GetDC(hwnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}