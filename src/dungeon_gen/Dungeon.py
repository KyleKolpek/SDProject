#!/usr/bin/python

from Room import Room

class Dungeon:
	"""
		The top-level data structure for our dungeons. These will contain a set
		of rooms (represented as a graph), each with their own state.
	"""

	def __init__(self, num_rooms=5):
		"""
			Optionally supply the number of rooms that the dungeon will contain.
		"""
		self.num_rooms = num_rooms
