#include "U_TestRotatingTriangle.h"
#include "Utilities/CG1Helper/CG1Helper.h"
//------------------------------------------------------------------------------
App_TestRotatingTriangle::App_TestRotatingTriangle(int w, int h)
        :Application(w,h)
{
	context.clearColor = CGVec4(0.0f, 0.0f, 0.0f, 1.0f);

	context.bresenhamIsEnabled = true;

	//U05 A1b)
	context.polygonMode = CG_FILL;
}
//------------------------------------------------------------------------------
void App_TestRotatingTriangle::program_step()
{

	if(CG1Helper::isKeyReleased(GLFW_KEY_F1))
		context.polygonMode= context.polygonMode==CG_FILL?CG_LINE:CG_FILL;

	// clear the screen
	context.clear(CG_COLOR_BUFFER_BIT);

	// Construct vertex data
	const float step = 0.3f * CG1Helper::getTime();
	const float ca = cosf(step);
	const float sa = sinf(step);


	float vertexPosition_TestRotTriangle[21*4]={20,20,0,
	                                            ca*20+20,sa*20+20,0,
	                                            -sa*15+20,ca*15+20,0,

	                                            1,1,0,
	                                            4,1,0,
	                                            1,4,0,

	                                            6.6f, 1.6f, 0,
	                                            7.4f, 1.6f, 0,
	                                            6.6f, 2.4f, 0,


	                                            40-1,4,0,
	                                            40-4,1,0,
	                                            40-1,1,0,


	                                            40-6.6f, 2.4f, 0,
	                                            40-7.4f, 1.6f, 0,

	                                            40-6.6f, 1.6f, 0,




	                                            19+0.5,1+0.5,0,
	                                            22+0.5,1+0.5,0,
	                                            22+0.5,4+0.5,0,

	                                            22+0.5,4+0.5,0,
	                                            19+0.5,4+0.5,0,
	                                            19+0.5,1+0.5,0,

	                                           };



	// set the vertex attribute pointers
	context.vertexAttributePointer.position = vertexPosition_TestRotTriangle;
	context.vertexAttributePointer.color = vertexColor_TestRotTriangle;

	// select the program used
	context.useProgram(prog);


	context.drawArrays(CG_TRIANGLES, 0, 21);
}
