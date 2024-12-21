#pragma once
#include "CGContext/CGProgram.h"
#include "CGContext/CGProgramInterface.h"
class Program_projectVertex : public CGProgram
{
public:
	struct
	{
		// U07 A1b)
		// ...
	}
	uniform;
	Program_projectVertex()
	{

	}
	~Program_projectVertex(){}


	void vertex_shader(const CGVertexAttributes& in,
	                   CGVaryings& out) const
	{
		// U06 A5b)
		out.position = in.position / ( - 1.0f * in.position.z);
		out.color = in.color;
	}

	void fragment_shader(const CGVaryings& in,
	                     CGVec4& out) const
	{
		out = in.color;
	}
};

