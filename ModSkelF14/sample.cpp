// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();

	// draw the floor
	setAmbientColor(0.1f,0.1f,0.1f);
	setDiffuseColor(COLOR_RED);

	glPushMatrix();
	//glRotated(VAL(BODY_ROTATION), 0.0, -1.0, 1.0);
	drawEllipsoid(VAL(BODY_X), VAL(BODY_Y), VAL(BODY_Z));

		glPushMatrix();
		glTranslated(VAL(BODY_X) / VAL(UPPER_WING_PX), VAL(BODY_Y) / VAL(UPPER_WING_PY), -VAL(BODY_Z) / VAL(UPPER_WING_PZ));
		drawBox(2.5, 0.01f, 2); 
		glPopMatrix();

		glPushMatrix();
		glTranslated(VAL(BODY_X) / VAL(UPPER_WING_PX), VAL(BODY_Y) / VAL(UPPER_WING_PY), -VAL(BODY_Z) / VAL(UPPER_WING_PZ));
		drawBox(2.5, 0.01f, 2);
		glPopMatrix();


	glPopMatrix();

	//glPushMatrix();
	//glTranslated(-5,0,-5);
	//drawBox(10,0.01f,10);
	//glPopMatrix();

	//// draw the sample model
	//setAmbientColor(.1f,.1f,.1f);
	//setDiffuseColor(COLOR_GREEN);
	//glPushMatrix();
	//glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

	//	glPushMatrix();
	//	glTranslated(-1.5, 0, -2);
	//	glScaled(3, 1, 4);
	//	drawBox(1,1,1);
	//	glPopMatrix();

	//	// draw cannon
	//	glPushMatrix();
	//	glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
	//	glRotated(-90, 1.0, 0.0, 0.0);
	//	drawCylinder(VAL(HEIGHT), 0.1, 0.1);

	//	glTranslated(0.0, 0.0, VAL(HEIGHT));
	//	drawCylinder(1, 1.0, 0.9);

	//	glTranslated(0.0, 0.0, 0.5);
	//	glRotated(90, 1.0, 0.0, 0.0);
	//	drawCylinder(4, 0.1, 0.2);
	//	glPopMatrix();

	//glPopMatrix(); 
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);

	//body
	controls[BODY_X] = ModelerControl("BODY X",0,5,0.1f,1.5);
	controls[BODY_Y] = ModelerControl("BODY Y",0,5,0.1f,2);
	controls[BODY_Z] = ModelerControl("BODY Z",0,5,0.1f,3 );
	controls[BODY_ROTATION] = ModelerControl("BODY ROTATION",0,360,1,65);

	controls[UPPER_WING_PX] = ModelerControl("UPPER WING PX", 0.1, 3, 0.1f, 1.2);
	controls[UPPER_WING_PY] = ModelerControl("UPPER WING PY", 0.1, 3, 0.1f, 3);
	controls[UPPER_WING_PZ] = ModelerControl("UPPER WING PZ", 0.1, 3, 0.1f, 2);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
