#!/usr/bin/python

import random

class Dungeon:
	def __init__(self, rooms=8, rows=4, cols=4):
		random.seed()
		self.numRooms = rooms
		self.dimRows = rows
		self.dimCols = cols
		self.grid = []

		self.placeRooms()
		self.printGrid()
	
	def placeRooms(self):
		for i in range(self.dimRows):
			self.grid.append([False] * self.dimCols)

		print("x: %d" % (self.numRooms))
		print("dim: %d x %d" % (self.dimRows, self.dimCols))
		self.rooms = []
		for i in range(self.numRooms):
			(i,j) = random.randint(0, self.dimRows-1), random.randint(0, self.dimCols-1)
			while (i,j) in self.rooms:
				(i,j) = random.randint(0, self.dimRows-1), random.randint(0, self.dimCols-1)
			self.rooms.append((i,j))
			self.grid[i][j] = True
			print("(%d,%d)" % (i, j))
	
	def printGrid(self):
		barrier = '-' * (self.dimCols * 2 + 1)
		for i in range(self.dimRows):
			print(barrier)
			line = "|"
			for j in range(self.dimCols):
				if self.grid[i][j]:
					line += "x|"
				else:
					line += " |"
			print(line)
		print(barrier)


if __name__ == "__main__":
	d = Dungeon()
