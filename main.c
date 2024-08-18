#include <stdbool.h>
#include <stdio.h>

typedef struct
{
	int row;
	int column;
} Coordinate;

const static int R = 5;
const static int C = 5;
int resCounter = 0;

bool solve(char field[R][C], Coordinate cur,char seen[R][C], Coordinate res[])
{
	if (cur.column < 0 || cur.row < 0 || cur.column >= C || cur.row >= R) return false;
	if (seen[cur.row][cur.column]) return false;
	seen[cur.row][cur.column] = 1;

	const char *currentField = &field[cur.row][cur.column];
	if( *currentField == '#' || *currentField == '|' || *currentField == '-')
	{
		return false;
	}

	if (*currentField == 'F') return true;

	const Coordinate next[] = {
		{cur.row - 1, cur.column},
		{cur.row, cur.column - 1},
		{cur.row, cur.column + 1},
		{cur.row + 1, cur.column}
	};

	for (char i = 0; i < 4; i++)
	{
		if (solve(field, next[i], seen, res))
		{
			printf("current next[i]: {%i, %i}", next[i].row, next[i].column);
			res[resCounter].row = next[i].row;
			res[resCounter].column = next[i].column;
			resCounter++;

			return true;
		}
	}
	return false;
}

int main(void)
{
	char seen[][5] = {
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	};

	char field[][5] = {
	{'#','#','#','S','#'},
	{'#','#','#','?','?'},
	{'#','?','?','?','?'},
	{'#','#','#','#','?'},
	{'#','#','F','?','?'}
	};
	
	const Coordinate cur = {0, 3};
	Coordinate res[10];

	printf("field:\n");
	for (char i = 0; i < 5; i++)
	{
		for (char j = 0 ; j < 5; j++)
		{
			printf("%c", field[i][j]);
		}
		printf("\n");
	}

	printf("starting with a space: %B\n",solve(field, cur, seen, res));
	printf("res-path for resCounter %i:\n", resCounter);
	for (int i = resCounter-1; i >= 0; i--)
	{
		printf("x: %i, y: %i\n", res[i].row, res[i].column);
	}


	printf("starting with a '#': %B\n",solve(field, (Coordinate){0, 2}, seen, res));
	resCounter = 0;
	printf("res-path for resCounter %i:\n", resCounter);
	for (char i = resCounter; i > 0; i--)
	{
		printf("x: %i, y: %i\n", res[i].row, res[i].column);
	}

	return 0;
}
