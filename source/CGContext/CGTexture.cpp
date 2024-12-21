#include "CGTexture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CGMath.h"

//------------------------------------------------------------------------------
// CGTEXTURE2D
//------------------------------------------------------------------------------
CGTexture2D::CGTexture2D()
{
	reset();
}
//------------------------------------------------------------------------------
CGTexture2D::~CGTexture2D()
{
	free(m_data);
	m_data = nullptr;
}
//------------------------------------------------------------------------------
void CGTexture2D::reset()
{
	m_width=m_height=0;
	filterMode=CG_NEAREST;
	wrapMode=CG_CLAMP;
	m_data=nullptr;
}
//------------------------------------------------------------------------------
void CGTexture2D::allocate(int width, int height, const unsigned char* data4ub)
{
	this->m_width = width;
	this->m_height = height;
	m_data = (unsigned char*) realloc(m_data,(size_t)(width*height)*4);
	memcpy(m_data,data4ub,(size_t)(width*height)*4);
}

//------------------------------------------------------------------------------
CGVec4 CGTexture2D::fetchTexel(int x, int y) const
{
	assert(m_data != nullptr);
	// U11 A2a)
	// ...

	return CGVec4(0.0f);
}
//------------------------------------------------------------------------------
CGVec4 CGTexture2D::sample(const CGVec4 &texcoord) const
{
	// U11 A2b)
	// ...
	return CGVec4(0.0f);
}
//------------------------------------------------------------------------------
