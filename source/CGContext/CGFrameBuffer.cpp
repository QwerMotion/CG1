#include "CGFrameBuffer.h"
#include <stdlib.h> // for malloc
#include <string.h> // for memcpy
#include "CG.h"
#include "CGVector.h"
//------------------------------------------------------------------------------
// CGFRAMEBUFFER
//------------------------------------------------------------------------------
bool CGFrameBuffer::allocate(int width, int height)
{
	bool retval = colorBuffer.reserve(width,height);
	// also reserve a depth buffer
	retval = retval && depthBuffer.reserve(width, height);
	return retval;
}
//------------------------------------------------------------------------------
int CGFrameBuffer::getWidth() const
{
	return colorBuffer.getWidth();
}
//------------------------------------------------------------------------------
int CGFrameBuffer::getHeight() const
{
	return colorBuffer.getHeight();
}


//------------------------------------------------------------------------------
// CGFRAMEBUFFER::CGBUFFER4UB
//------------------------------------------------------------------------------
CGFrameBuffer::CGColorBuffer::CGColorBuffer()
{
	m_buffer_data = nullptr;
}
//------------------------------------------------------------------------------
CGFrameBuffer::CGColorBuffer::~CGColorBuffer()
{
	free(m_buffer_data);
	m_buffer_data = nullptr;
}
//------------------------------------------------------------------------------
bool CGFrameBuffer::CGColorBuffer::reserve(const int width, const int height)
{
	m_width = width;
	m_height = height;

	// allocate the memory for the buffer
	this->m_buffer_data = (unsigned char*)malloc(width * height * sizeof(int) * 4);
	

	// U01 A1a)
	// Hinweise:
	//   - m_buffer_data ist eine Membervariable; auf sie kann auch in anderen Methoden der Klasse
	//     CGColorBuffer zugegriffen werden.
	//   - malloc nimmt einen Parameter entgegen: die Anzahl der zu reservierenden Bytes
	//   - malloc gibt einen Zeiger auf den allozierten Speicher zurück (als void*, m_buffer_data
	//     ist aber vom Typ unsigned char*)
	// m_buffer_data = ...

	return m_buffer_data != nullptr;
}
//------------------------------------------------------------------------------
void CGFrameBuffer::CGColorBuffer::set_white(const CGVec2i& p)
{
	assert(m_buffer_data != nullptr);
	assert(p.x < m_width && p.y < m_height && p.x >= 0 && p.y >= 0);

	unsigned char* writeAdress = this->m_buffer_data + (m_width * p.y + p.x) * sizeof(unsigned char) * 4;
	*writeAdress = 255;
	*(writeAdress + 1 * sizeof(unsigned char)) = 255;
	*(writeAdress + 2 * sizeof(unsigned char)) = 255;
	*(writeAdress + 3 * sizeof(unsigned char)) = 255;



	// U01 A1b)
	// Hinweise:
	//   - Gebrauchen Sie Zeigerarithmetik, um die Adresse des Pixels bei (p.x, p.y) zu berechnen.
	//   - m_buffer_data zeigt auf den Anfang des Speicherbereichs, der in CGColorBuffer::reserve
	//     reserviert wurde.
	// ...
}
//------------------------------------------------------------------------------
void CGFrameBuffer::CGColorBuffer::set(const CGVec2i &p, const CGVec4 &rgba)
{
	assert(m_buffer_data != nullptr);
	//assert(p.x < m_width && p.y < m_height && p.x >= 0 && p.y >= 0);

	int r = (int)(rgba.x * 255);
	int g = (int)(rgba.y * 255);
	int b = (int)(rgba.z * 255);
	int a = (int)(rgba.w * 255);

	unsigned char* writeAdress = this->m_buffer_data + (m_width * p.y + p.x) * sizeof(unsigned char) * 4;
	*writeAdress = r;
	*(writeAdress + 1 * sizeof(unsigned char)) = g;
	*(writeAdress + 2 * sizeof(unsigned char)) = b;
	*(writeAdress + 3 * sizeof(unsigned char)) = a;

	// U01 A1c)
	// Hinweise:
	//   - Die Werte der einzelnen Kanäle des Parameters rgba sind vom Typ float und liegen im
	//     Intervall [0.0, 1.0]
	//   - Welcher Wertebereich ist für eine vorzeichenfreie 8-Bit-Ganzzahl (unsigned char) zulässig?
	//     Auf diesen Bereich muss das Intervall [0.0, 1.0] der Eingabewerte abgebildet werden.
	// ...
}
//------------------------------------------------------------------------------
CGVec4 CGFrameBuffer::CGColorBuffer::get(const CGVec2i &p) const
{
	assert(m_buffer_data != nullptr);
	assert(p.x < m_width && p.y < m_height && p.x >= 0 && p.y >= 0);

	CGVec4 rgba;

	unsigned char* readAdress = this->m_buffer_data + (m_width * p.y + p.x) * sizeof(unsigned char) * 4;

	float r = (float)*readAdress / 255.0f;
	float g = (float)*(readAdress + 1 * sizeof(unsigned char)) / 255.0f;
	float b = (float)*(readAdress + 2 * sizeof(unsigned char)) / 255.0f;
	float a = (float)*(readAdress + 3 * sizeof(unsigned char)) / 255.0f;

	rgba.x = r;
	rgba.y = g;
	rgba.z = b;
	rgba.w = a;


	// U01 A1d)
	// Hinweise:
	//   - Für diese Operation muss die in CGColorBuffer::set vorgenommene Umrechnung invertiert
	//     werden.
	// ...

	return rgba;
}
//------------------------------------------------------------------------------
void CGFrameBuffer::CGColorBuffer::clear(const CGVec4& rgba)
{
	assert(m_buffer_data != nullptr);

	//int r = (int)(rgba.x * 255);
	//int g = (int)(rgba.y * 255);
	//int b = (int)(rgba.z * 255);
	//int a = (int)(rgba.w * 255);

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {

			this->set(CGVec2i(x, y), rgba);
		}
	}

	// U01 A1e)
	// Hinweise:
	//   - Rechnen Sie zunächst die Eingabefarbe analog zu CGColorBuffer::set um und kopieren Sie
	//     die resultierenden Werte dann pro Pixel einmal in den Color Buffer.
	// ...
}
//------------------------------------------------------------------------------
unsigned char* CGFrameBuffer::CGColorBuffer::getDataPointer() const
{
	return m_buffer_data;
}
//------------------------------------------------------------------------------
int CGFrameBuffer::CGColorBuffer::getWidth() const
{
	return m_width;
}
//------------------------------------------------------------------------------
int CGFrameBuffer::CGColorBuffer::getHeight() const
{
	return m_height;
}


//------------------------------------------------------------------------------
// CGFRAMEBUFFER::CGBUFFER1F
//------------------------------------------------------------------------------
CGFrameBuffer::CGDepthBuffer::CGDepthBuffer()
{
	m_buffer_data = nullptr;
}
//------------------------------------------------------------------------------
CGFrameBuffer::CGDepthBuffer::~CGDepthBuffer()
{
	free(m_buffer_data);
	m_buffer_data = nullptr;
}
//------------------------------------------------------------------------------
bool CGFrameBuffer::CGDepthBuffer::reserve(const int width,const int height)
{
	m_width = width;
	m_height = height;
	// U09 A1 a)
	// ...
	return true;
}
//------------------------------------------------------------------------------
float CGFrameBuffer::CGDepthBuffer::get(const CGVec2i &p) const
{
	assert(m_buffer_data != nullptr);
	assert(p.x < m_width && p.y < m_height && p.x >= 0 && p.y >= 0);
	// U09 A1 a)
	// ...

	return 0.0f;
}
//------------------------------------------------------------------------------
void CGFrameBuffer::CGDepthBuffer::set(const CGVec2i &p, const float z)
{
	assert(m_buffer_data != nullptr);
	assert(p.x < m_width && p.y < m_height && p.x >= 0 && p.y >= 0);
	// U09 A1 a)
	// ...

}
//------------------------------------------------------------------------------
void CGFrameBuffer::CGDepthBuffer::clear()
{
	assert(m_buffer_data != nullptr);
	// U09 A1 a)
	// ...
}
//------------------------------------------------------------------------------
float* CGFrameBuffer::CGDepthBuffer::getDataPointer() const
{
	return m_buffer_data;
}
//------------------------------------------------------------------------------
int CGFrameBuffer::CGDepthBuffer::getWidth() const
{
	return m_width;
}
//------------------------------------------------------------------------------
int CGFrameBuffer::CGDepthBuffer::getHeight() const
{
	return m_height;
}
//------------------------------------------------------------------------------
