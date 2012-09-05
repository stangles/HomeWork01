#include "cinder\app\AppBasic.h"
#include "cinder\gl\gl.h"
#include "Resources.h"
#include "cinder\gl\Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HomeWork01App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	Surface* my_surface_;

	//Width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024; //Must be the next power of 2 bigger or equal to app dimensions

	void drawRectangle(uint8_t* pixels, int x1, int y1, int width, int height, Color8u fill_color);

	void drawCircle(uint8_t* pixels, int x1, int y1, int radius, Color8u fill_color);

	void HomeWork01App::copyRect(uint8_t* pixels, int from_corner_x, int from_corner_y, int from_width, int from_height);
};


void HomeWork01App::copyRect(uint8_t* pixels, int from_corner_x, int from_corner_y, int from_width, int from_height)
{
	for(int y=from_corner_y; y<from_corner_y+from_height; y++) {
		for(int x=from_corner_x; x<from_corner_x+from_width; x++) {
			pixels[3*((x+from_height) + (y+from_width*kTextureSize))] = pixels[3*(x + y*kTextureSize)];
			pixels[3*((x+from_height) + (y+from_width*kTextureSize)+1)] = pixels[3*(x + y*kTextureSize)+1];
			pixels[3*((x+from_height) + (y+from_width*kTextureSize)+2)] = pixels[3*(x + y*kTextureSize)+2];
		}
	}
}

void HomeWork01App::drawCircle(uint8_t* pixels, int x1, int y1, int radius, Color8u fill_color)
{
	int x_pos = x1 - radius;
	int y_pos = y1 - radius;
	int x_distance = x1 + (2*radius);
	int y_distance = y1 + (2*radius);
	Color8u c = fill_color;

	float point_distance;
	for(int y=y_pos; y<y_distance; y++) {
		for(int x=x_pos; x<x_distance; x++) {
			point_distance = (((float) y - (float) y1)*((float) y - (float) y1)) + (((float) x - (float) x1)*((float) x - (float) x1));
			if(point_distance <= radius*radius) {
				pixels[3*(x + y*kTextureSize)] = c.r;	//
				pixels[3*(x + y*kTextureSize)+1] = c.g;	//Borrowed this from Brinkman's HW01
				pixels[3*(x + y*kTextureSize)+2] = c.b;	//
			}
		}
	}
}

void HomeWork01App::drawRectangle(uint8_t* pixels, int x1, int y1, int width, int height, Color8u fill_color)
{
	int x_pos;
	int y_pos;
	int x_distance;
	int y_distance;

	if(x1 < 0) {
		x_pos = 0;
		x_distance = width-(-1*x1);
	}
	else {
		x_pos = x1;
		x_distance = x1 + width;
	}

	if(y1 < 0) {						//
		y_pos = 0;						// All these conditionals are for checking if the rectangle is within the window and fixing it if it's not
		y_distance = height-(-1*y1);	//
	}
	else {
		y_pos = y1;
		y_distance = y1 + height;
	}

	if(x_pos+x_distance > kAppWidth)
		x_distance = kAppWidth-x_pos;
	if(y_pos+y_distance > kAppHeight)
		y_distance = kAppHeight-y_pos;

	Color8u c = fill_color;

	for(int y=y_pos; y<y_distance; y++) {
		for(int x=x_pos; x<x_distance; x++) {
			pixels[3*(x + y*kTextureSize)] = c.r;	//
			pixels[3*(x + y*kTextureSize)+1] = c.g;	//Borrowed from Brinkman's HW01
			pixels[3*(x + y*kTextureSize)+2] = c.b;	//
		}
	}
}

void HomeWork01App::setup()
{
	my_surface_ = new Surface(kTextureSize, kTextureSize,false);
}

void HomeWork01App::mouseDown( MouseEvent event )
{
}

void HomeWork01App::update()
{

	uint8_t* dataArray = (*my_surface_).getData();

	//White Background
	for(int i = 0; i < kTextureSize*kTextureSize; i++){
			dataArray[3*(i)] = 255;
			dataArray[3*(i)+1] = 255;
			dataArray[3*(i)+2] = 255;
	}

	drawRectangle(dataArray, 250, 200, 75, 50, Color8u(0,255,0)); //Draw rectangle

	drawCircle(dataArray, 150, 100, 50, Color8u(0,255,0)); //Draw Circles
	drawCircle(dataArray, 150, 350, 50, Color8u(0,255,0));

	//copyRect(dataArray, 0, 0, 400, 600); //This was intended to copy one half of the window onto the other
}

void HomeWork01App::draw()
{
	// Draw the surface, using the graphics library
	gl::draw(*my_surface_);
}

CINDER_APP_BASIC( HomeWork01App, RendererGl )
