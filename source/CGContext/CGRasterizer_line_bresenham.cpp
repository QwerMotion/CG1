#include "CGRasterizer.h"
#include "CGProgramInterface.h"
#include "CGFragmentOperations.h"
#include <algorithm>

void CGBresenhamLineRasterizer::rasterize(const CGVaryings& A, const CGVaryings& B)
{
    // Initialize start and end points
    CGVec2i start, end;
    start.set((int)A.position.x, (int)A.position.y);
    end.set((int)B.position.x, (int)B.position.y);

    // Fragment to work on
    CGFragmentData fragment;
    fragment.set(A);

    // Compute deltas
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);

    // Determine line direction
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;

    // Total distance for interpolation
    float total_distance = sqrtf((float)dx * dx + (float)dy * dy);

    // Error term
    int err = dx - dy;

    // Current position
    int x = start.x;
    int y = start.y;

    // Bresenham loop
    while (true) {
        // Calculate interpolation factor t
        float current_distance = sqrtf((float)(x - start.x) * (x - start.x) +
            (float)(y - start.y) * (y - start.y));
        float t = current_distance / total_distance;

        // Set fragment data and push
        fragment.coordinates.set(x, y);
        fragment.set(A, B, t); // Pass t for interpolation
        m_frag_ops.push_fragment(fragment);

        // Check if we reached the end point
        if (x == end.x && y == end.y)
            break;

        // Update error and coordinates
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }

    // Flush the fragments
    m_frag_ops.flush_fragments();
}
