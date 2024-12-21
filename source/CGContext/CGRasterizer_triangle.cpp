#include "CGRasterizer.h"
#include "CGProgramInterface.h"
#include "CGFragmentOperations.h"
#include "CGContext.h"
#include <algorithm>
//------------------------------------------------------------------------------
float triangle_area(const CGVec4& A, const CGVec4& B, const CGVec4& C) {
	// Berechnung der Determinantea
	float determinant = A.x * (B.y - C.y) +
		B.x * (C.y - A.y) +
		C.x * (A.y - B.y);
	// Die Fläche ist der halbe Betrag der Determinante
	return std::abs(determinant);
}

void CGTriangleRasterizer::rasterize(const CGVaryings& A, const CGVaryings& B, const CGVaryings& C)
{
    const CGVec4& a = A.position;
    const CGVec4& b = B.position;
    const CGVec4& c = C.position;
    CGFragmentData fragment;

    // 1. Calculate the bounding box
    int minX = std::max(0, (int)std::floor(std::min({ a.x, b.x, c.x })));
    int maxX = std::min(m_context.m_frameBuffer.getWidth() - 1, (int)std::ceil(std::max({ a.x, b.x, c.x })));
    int minY = std::max(0, (int)std::floor(std::min({ a.y, b.y, c.y })));
    int maxY = std::min(m_context.m_frameBuffer.getHeight() - 1, (int)std::ceil(std::max({ a.y, b.y, c.y })));

    // 2. Precompute the area of the triangle
    float areaABC = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

    // 3. Iterate over pixels in the bounding box
    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            CGVec2 point(x + 0.5f, y + 0.5f);

            // 4. Compute barycentric coordinates
            float w0 = ((b.x - point.x) * (c.y - point.y) - (b.y - point.y) * (c.x - point.x)) / areaABC;
            float w1 = ((c.x - point.x) * (a.y - point.y) - (c.y - point.y) * (a.x - point.x)) / areaABC;
            float w2 = 1.0f - w0 - w1;

            // 5. Check if the pixel is inside the triangle
            if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                // Interpolate attributes
                
               

                // Set fragment data
                fragment.set(A, B, C, w0, w1, w2);
                fragment.coordinates.set(x, y);
                m_frag_ops.push_fragment(fragment);
            }
        }
    }

    // 6. Flush the fragment buffer
    m_frag_ops.flush_fragments();
}

