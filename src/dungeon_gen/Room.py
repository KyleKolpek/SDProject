
class Room:
	"""
		Rooms are individual components of dungeons.

	"""
	def __init__(self, width=500, length=1000):
		"""
			Optionally supply the length and width of the room (in pixels)
		"""
		self.width = width
		self.length = length
