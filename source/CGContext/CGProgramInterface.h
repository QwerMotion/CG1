#pragma once
#include "CGMatrix.h"
#include "CGVector.h"
#include "CGTexture.h"
#include "CG.h"
#include "iostream"
#include "stdio.h"
//---------------------------------------------------------------------------

/// Vertex attribute container (vertex processing inputs).
struct CGVertexAttributes
{
	CGVec4 position;
	CGVec4 normal;
	CGVec4 color;
	CGVec4 texcoord;
};

/// Vertex varying container (vertex processing outputs).
struct CGVaryings
{
	CGVec4 position;
	CGVec4 normal;
	CGVec4 color;
	CGVec4 texcoord;
	CGVec4 position_es;
};

/// Fragment data container.
struct CGFragmentData
{
	CGVec2i coordinates;   /// Fragment specific framebuffer coordinate
	CGVaryings varyings;   /// Varyings as copied from vertex or interpolated.

	void set(const CGVaryings& A)
	{
		varyings = A;
	}

	void set(const CGVaryings& A,
	         const CGVaryings& B,
	         float ratio)
	{
		//U04 A1a)	
		// 
		// // Hinweis: Führen Sie die Interpolation für *alle* Member der Klasse `CGVaryings` durch:
		// - position
		// - normal
		// - color
		// - texcoord
		// - position_es
		// ...
		float otherRatio = (1 - ratio);
		

		CGVec4 startPosition = A.position;
		CGVec4 endPosition = B.position;
		CGVec4 interpolatedPosition = CGVec4(startPosition.x * otherRatio + endPosition.x * ratio, startPosition.y * otherRatio + endPosition.y * ratio, startPosition.z * otherRatio + endPosition.z * ratio, startPosition.w * otherRatio + endPosition.w * ratio);

		CGVec4 startNormal = A.normal;
		CGVec4 endNormal = B.normal;
		CGVec4 interpolatedNormal = CGVec4(startNormal.x * otherRatio + endNormal.x * ratio, startNormal.y * otherRatio + endNormal.y * ratio, startNormal.z * otherRatio + endNormal.z * ratio, startNormal.w * otherRatio + endNormal.w * ratio);

		CGVec4 startColor = A.color;
		CGVec4 endColor = B.color;
		CGVec4 interpolatedColor = CGVec4((float)startColor.x * otherRatio + endColor.x * ratio, (float)startColor.y * otherRatio + endColor.y * ratio, (float)startColor.z * otherRatio + endColor.z * ratio, (float)startColor.w * otherRatio + endColor.w * ratio);
		
		CGVec4 startTexcoord = A.texcoord;
		CGVec4 endTexcoord = B.texcoord;
		CGVec4 interpolatedTexcoord = CGVec4(startTexcoord.x * otherRatio + endTexcoord.x * ratio, startTexcoord.y * otherRatio + endTexcoord.y * ratio, startTexcoord.z * otherRatio + endTexcoord.z * ratio, startTexcoord.w * otherRatio + endTexcoord.w * ratio);

		CGVec4 startPosition_es = A.position_es;
		CGVec4 endPosition_es = B.position_es;
		CGVec4 interpolatedPosition_es = CGVec4(startPosition_es.x * otherRatio + endPosition_es.x * ratio, startPosition_es.y * otherRatio + endPosition_es.y * ratio, startPosition_es.z * otherRatio + endPosition_es.z * ratio, startPosition_es.w * otherRatio + endPosition_es.w * ratio);
		
		CGVaryings interpolated = CGVaryings();
		interpolated.position = interpolatedPosition;
		interpolated.normal = interpolatedNormal;
		interpolated.color = interpolatedColor;
		interpolated.texcoord = interpolatedTexcoord;
		interpolated.position_es = interpolatedPosition_es;

		varyings = interpolated;

		// U11 A3a)
	}

	void set(const CGVaryings& A,
	         const CGVaryings& B,
	         const CGVaryings& C,
	         float alpha, float beta, float gamma)
	{
		// U05 A2a)
		// ...
		// Interpolation für jede Komponente
		CGVec4 position = alpha * A.position + beta * B.position + gamma * C.position;
		CGVec4 normal = alpha * A.normal + beta * B.normal + gamma * C.normal;
		CGVec4 color = alpha * A.color + beta * B.color + gamma * C.color;
		CGVec4 texcoord = alpha * A.texcoord + beta * B.texcoord + gamma * C.texcoord;
		CGVec4 position_es = alpha * A.position_es + beta * B.position_es + gamma * C.position_es;

		CGVaryings interpolated = CGVaryings();
		interpolated.position = position;
		interpolated.normal = normal;
		interpolated.color = color;
		interpolated.texcoord = texcoord;
		interpolated.position_es = position_es;

		varyings = interpolated;
		// U11 A3b)
	}
};

