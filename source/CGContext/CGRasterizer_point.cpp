#include "CGRasterizer.h"
#include "CGProgramInterface.h"
#include "CGFragmentOperations.h"
#include "CGContext.h"
#include "CGMath.h"

void CGPointRasterizer::rasterize(const CGVaryings& A)
{
	CGFragmentData fragment;

	// U01 A4a) & A4c)
	// Hinweise:
	//   - fragment.set(...) setzt nur die Varyings. Fragmentkoordinaten werden in
	//     fragment.coordinates hinterlegt.
	//   - m_frag_ops.push_fragment(fragment) reiht das Fragment für die Weiterverarbeitung ein.
	//   - m_frag_ops.flush_fragments() verarbeitet _alle_ eingereihten Fragmente.
	//   - m_context.pointRadius enthält den aktuellen Punktradius.
	//   - m_context.viewport enthält die aktuellen Viewport-Parameter.
	fragment.set(A);
	fragment.coordinates =  A.position;
	m_frag_ops.push_fragment(fragment);
	m_frag_ops.flush_fragments();
}
