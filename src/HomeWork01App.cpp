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

	void drawRectangle(uint8_t* pixels, int x1, int y1, int width, int height, Color8u fillColor);
};

void HomeWork01App::drawRectangle(uint8_t* pixels, int x1, int y1, int width, int height, Color8u fillColor)
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

	if(y1 < 0) {
		y_pos = 0;
		y_distance = height-(-1*y1);
	}
	else {
		y_pos = y1;
		y_distance = y1 + height;
	}

	if(x_pos+x_distance > kAppWidth)
		x_distance = kAppWidth-x_pos;
	if(y_pos+y_distance > kAppHeight)
		y_distance = kAppHeight-y_pos;

	Color8u c = fillColor;

	for(int y=y_pos; y<y_distance; y++) {
		for(int x=x_pos; x<x_distance; x++) {
			pixels[3*(x + y*kTextureSize)] = c.r;
			pixels[3*(x + y*kTextureSize)+1] = c.g;
			pixels[3*(x + y*kTextureSize)+2] = c.b;
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

	drawRectangle(dataArray, 50, 50, 50, 25, Color8u(0,255,0));
}

void HomeWork01App::draw()
{
	// Draw the surface, using the graphics library
	gl::draw(*my_surface_);
}

CINDER_APP_BASIC( HomeWork01App, RendererGl )
