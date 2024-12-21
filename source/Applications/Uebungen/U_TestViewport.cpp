#include "U_TestViewport.h"
#include <iostream>
//------------------------------------------------------------------------------
App_TestViewport::App_TestViewport(int w, int h)
	:Application(w,h)
{
	frame_width = w;
	frame_height = h;
	context.clearColor = CGVec4(0.0f, 0.0f, 0.0f, 1.0f);
	context.bresenhamIsEnabled = true;
}
//----------------------------program_step--------------------------------------------------
void App_TestViewport::program_step()
{
	//context.useProgram(prog);
	
	// clear the screen

	context.clear(CG_COLOR_BUFFER_BIT);
	context.useProgram(prog);

	// set the vertex attribute pointers
	context.vertexAttributePointer.position = vertexPosition_TestTriangle;
	context.vertexAttributePointer.color = vertexColor_TestTriangle;

	context.viewport = CGRectangle(200, 100, frame_width / 2, frame_height / 2);



	//context.viewport.set(0, 0, frame_width / 2, frame_height / 2);
	context.drawArrays(CG_TRIANGLES, 0, 6);
	

	//context.viewport.set(frame_width / 2, frame_height, frame_width / 2, frame_height / 2);
	//context.drawArrays(CG_TRIANGLES, 0, 6);
	

	
	//context.viewport.set(0, frame_height, frame_height, frame_width);
	//context.drawArrays(CG_TRIANGLES, 0, 6);

	
	//context.viewport.set(0, 0, frame_height/2, frame_height/2);
	//context.viewport.set(frame_height / 2, frame_height / 2, frame_height, frame_height);
	//context.viewport.set(0, 0, frame_height / 2, frame_height / 2);
	//context.viewport.set(0, 0, frame_height / 2, frame_height / 2);
	
	
	//std::cout << "test" << std::endl;
}
