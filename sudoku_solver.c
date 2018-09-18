#include <stdio.h>

#define N 9
#define UNASSIGNED 0

int col, row;

int is_exist_row(int grid[N][N], int, int);
int is_exist_col(int grid[N][N], int, int);
int is_exist_box(int grid[N][N], int, int, int);
int is_safe_num(int grid[N][N], int, int, int);
int find_unassigned(int grid[N][N], int*, int*);

int main() {
	
	printf("Here is the puzzle: \n\n");
	
	int grid[N][N] = 
			 {{0,0,0, 0,0,3, 2,9,0},
			 {0,8,6, 5,0,0, 0,0,0},
			 {0,2,0, 0,0,1, 0,0,0},
			 {0,0,3, 7,0,5, 1,0,0},
			 {9,0,0, 0,0,0, 0,0,8},
			 {0,0,2, 9,0,8, 3,0,0},
			 {0,0,0, 4,0,0, 0,8,0},
			 {0,4,7, 1,0,0, 0,0,0}};
			 
	print_grid(grid);
	printf("\n\nWhen solved: \n\n");
	
	if (solve(grid)) {
		print_grid(grid);
	} else {
		printf("no solution");
	}
	
	return 0;
}


//Is number already placed in current row
int is_exist_row(int grid[N][N], int row, int num){
	for (col = 0; col < 9; col++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}
//Is number already placed in current column
int is_exist_col(int grid[N][N], int col, int num) {
	for (row = 0; row < 9; row++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

//Is number already placed in current box (3x3)
int is_exist_box(int grid[N][N], int startRow, int startCol, int num) {
	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			if (grid[row + startRow][col + startCol] == num) {
				return 1;
			} 
		}
	}
	return 0;
}

//Is it safe to assign num to the given row,col location
int is_safe_num(int grid[N][N], int row, int col, int num) {
	return !is_exist_row(grid, row, num) 
			&& !is_exist_col(grid, col, num) 
			&& !is_exist_box(grid, row - (row % 3), col - (col %3), num);
}

//Loops through the grid to fill in each cell one-by-one; if unassigned entry found, row & col will be set that location and 1 returned, else 0 is returned
int find_unassigned(int grid[N][N], int *row, int *col) {
	for (*row = 0; *row < N; (*row)++) {
		for (*col = 0; *col < N; (*col)++) {
			if (grid[*row][*col] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int solve(int grid[N][N]) {
	
	int row = 0;
	int col = 0;
	int num;
	
	if (!find_unassigned(grid, &row, &col)){
		return 1;
	}
	
	for (num = 1; num <= N; num++ ) {
		
		if (is_safe_num(grid, row, col, num)) {
			grid[row][col] = num;
			
			if (solve(grid)) {
				return 1;
			}
			
			grid[row][col] = UNASSIGNED;
		}
	}
	
	return 0;
}

void print_grid(int grid[N][N]) {
	for (row = 0; row < N; row++) {
		for (col = 0; col < N; col++) {
			printf("%2d", grid[row][col]);
		}
		printf("\n");
	}
}
