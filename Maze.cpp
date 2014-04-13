#include "Maze.h"

Maze::Maze(int rows, int cols):
		m_size(rows, cols)
{
	m_f = new char *[m_size.row * 2 + 1];
	for (int i = 0; i < m_size.row * 2 + 1; i++) {
		m_f[i] = new char[m_size.col * 2 + 1];
	}

	for (int i = 0; i < m_size.row; i++) {
		for (int j = 0; j < m_size.col; j++) {
			m_f[2 * i][2 * j] = FILLED;
			m_f[2 * i][2 * j + 1] = FILLED;
			m_f[2 * i + 1][2 * j] = FILLED;
			m_f[2 * i + 1][2 * j + 1] = EMPTY;
		}
	}

	for (int i = 0; i < 2 * m_size.row + 1; i++) {
		m_f[i][2 * m_size.col] = FILLED;
	}

	for (int j = 0; j < 2 * m_size.col + 1; j++) {
		m_f[2 * m_size.row][j] = FILLED;
	}

	if (debug) {
		printf("Maze(%d, %d)\n", m_size.row, m_size.col);
	}
}

const Cell& Maze::getSize() {
	return m_size;
}

void Maze::print() {
	for (int i = 0; i < 2 * m_size.row + 1; i++) {
		for (int j = 0; j < 2 * m_size.row + 1; j++) {
			if (m_f[i][j] == EMPTY) {
				printf(" ");
			} else if (m_f[i][j] == FILLED) {
				printf("%c", 'X');
			}
		}
		printf("\n");
	}
}

void Maze::generate() {
	///TODO: Implemet. Started.
}
