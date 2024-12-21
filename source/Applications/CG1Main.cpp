// Standard includes.
#include <stdlib.h>         // for rand()
#include <time.h>           // for time() in srand()
// Our includes.
#include "Utilities/CG1Helper/CG1Helper.h"
//---------------------------------------------------------------------------
// Defines, globals, etc.


#define FRAME_WIDTH  320   // Framebuffer width.
#define FRAME_HEIGHT 200   // Framebuffer height.
#define FRAME_SCALE  2     // Integer scaling factors (zoom).


#include "Uebungen/U_JumpingLine.h"
#include "Uebungen/U_FourPoints.h"
#include "Uebungen/U_LineBenchmark.h"
#include "Uebungen/U_TestBresenham.h"
#include "Uebungen/U_TestRotatingTriangle.h"
#include "Uebungen/U_TestViewport.h"
#include "Uebungen/U_TestProjection.h"
#include "Uebungen/U_HappyHolidays.h"
#include "Uebungen/U_AwesomeTriangle.h"
#include "Uebungen/U_Lighting.h"
#include "Uebungen/U_Texturing.h"


int main(int /*argc*/,
	 char ** /*argv*/)
{
	srand((unsigned int)time(nullptr)); // initialize seed for pseudo random number generator

	//Application* app = (Application*) new App_TestViewport(FRAME_WIDTH, FRAME_HEIGHT);
	
	Application* app = (Application*) new App_TestProjection(FRAME_WIDTH,FRAME_HEIGHT);

	if (CG1Helper::initApplication(app, FRAME_SCALE)) {
		CG1Helper::runApplication();
	} else {
		fprintf(stderr,"failed to intialize CG1Helper!\n");
	}

	delete app;

	return 0;
}
//---------------------------------------------------------------------------

