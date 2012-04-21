#include "drawable.h"

class Wall:public Drawable
{
	private:
	Wall(float x_1, float y_1, float x_2, float y_2);
	~Wall();
		
	void draw();
		
	public:
	float x1, y1, x2, y2;
};
