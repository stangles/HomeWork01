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

	void drawRectangle(uint8_t* pixels, int x1, int y1, int width, int height);
};

void HomeWork01App::drawRectangle(uint8_t* pixels, int x1, int y1, int width, int height)
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
		x_distance = width;
	}

	if(y1 < 0) {
		y_pos = 0;
		y_distance = height-(-1*y1);
	}
	else {
		y_pos = y1;
		y_distance = height;
	}

	if(x_pos+x_distance > kAppWidth) {
		x_distance = kAppWidth-x_pos;
	}
	if(y_pos+y_distance > kAppHeight) {
		y_distance = kAppHeight-y_pos);
	}

	Color8u c = Color8u(0,255,0);



}

void HomeWork01App::setup()
{
}

void HomeWork01App::mouseDown( MouseEvent event )
{
}

void HomeWork01App::update()
{
}

void HomeWork01App::draw()
{
	// Draw the surface, using the graphics library
	gl::draw(*my_surface_);
}

CINDER_APP_BASIC( HomeWork01App, RendererGl )
