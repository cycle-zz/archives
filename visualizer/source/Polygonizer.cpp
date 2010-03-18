#include "DataTypes.h"
#include "Polygonizer.h"
#include "Shading.h"

using namespace dg;

//******************************************************************************
Polygonizer::Polygonizer(
	Function pvFunction, Int iCellCount, Real fScale, Real fIsoLevel)
	: m_kVertexList(1, 1000), m_kNormalList(1, 1000), m_kColorList(1, 1000)  
{
	m_pvFunction = pvFunction;
	m_iCellCount = iCellCount;
	m_fScale = fScale;
	m_fDelta = 1.0 / m_iCellCount;
	m_fEpsilon = 0.01;
	m_fIsoLevel = fIsoLevel;	
}
//******************************************************************************
void Polygonizer::getNormal(Vector &rkNormal, Real fX, Real fY, Real fZ)
{
	rkNormal.x() = sample(fX - m_fEpsilon, fY, fZ) - 
  				   sample(fX + m_fEpsilon, fY, fZ);
	
	rkNormal.y() = sample(fX, fY - m_fEpsilon, fZ) - 
				   sample(fX, fY + m_fEpsilon, fZ);

	rkNormal.z() = sample(fX, fY, fZ - m_fEpsilon) - 
				   sample(fX, fY, fZ + m_fEpsilon);

	rkNormal.normalize();
}
//******************************************************************************
void Polygonizer::marchCube(Real fX, Real fY, Real fZ, Real fScale)
{
	if(!m_pvFunction)
		return;
	
	Real afCubeValue[8];		// sampled values for each cube corner
	Vector akEdgeVector[12];	// edge vertices
	Vector akEdgeNorm[12];		// edge normals

	// get values for each cube corner
	for(int iV = 0; iV < 8; iV++)
	{
		afCubeValue[iV] = sample(fX + ms_aafCubeOffsets[iV][0] * fScale,
		                         fY + ms_aafCubeOffsets[iV][1] * fScale,
		                         fZ + ms_aafCubeOffsets[iV][2] * fScale);
	}

	// determine inside and outside points
	int iFlagIndex = 0;
	for(int iTest = 0; iTest < 8; iTest++)
	{
		if (afCubeValue[iTest] <= m_fIsoLevel)
			iFlagIndex |= 1 << iTest;
	}

	// get edge bits to determine surface intersection
	int iEdgeBits = ms_aiCubeEdgeBits[iFlagIndex];

	// return if cube does not intersect with surface
	if (iEdgeBits == 0)
		return ;

	// determine intersection point for each edge
	for(int iE = 0; iE < 12; iE++)
	{
		// get the intersection point if there is one
		if (iEdgeBits & (1 << iE))
		{
			// get the intersection offset
			Real fOffset = getIntersect(afCubeValue[ ms_aaiCubeConnects[iE][0] ],
			     	                    afCubeValue[ ms_aaiCubeConnects[iE][1] ],
										m_fIsoLevel);
			// create the edge
			akEdgeVector[iE].x() = fX + (ms_aafCubeOffsets[ ms_aaiCubeConnects[iE][0] ][0] + 
								 fOffset * ms_aafCubeDirs[iE][0]) * fScale;
								 
			akEdgeVector[iE].y() = fY + (ms_aafCubeOffsets[ ms_aaiCubeConnects[iE][0] ][1] + 
								 fOffset * ms_aafCubeDirs[iE][1]) * fScale;
								 
			akEdgeVector[iE].z() = fZ + (ms_aafCubeOffsets[ ms_aaiCubeConnects[iE][0] ][2] + 
								 fOffset * ms_aafCubeDirs[iE][2]) * fScale;

			// get the normal for this edge
			getNormal(akEdgeNorm[iE], 
					  akEdgeVector[iE].x(), 
					  akEdgeVector[iE].y(), 
					  akEdgeVector[iE].z());
		}
	}

	// create the triangles (max 5) for the intersections
	for(int iTri = 0; iTri < 5; iTri++)
	{
		if (ms_aaiTriConnects[iFlagIndex][3*iTri] < 0)
			break;

		// for each triangle corner
		for(int iC = 0; iC < 3; iC++)
		{
			// get the vertex index
			int iV = ms_aaiTriConnects[iFlagIndex][3 * iTri + iC];

			// get a color value for this triangle
			Color kColor;	
			getColor(kColor, akEdgeVector[iV], akEdgeNorm[iV]);
			
			// add the colors, normals and vertices
			m_kColorList.insert( kColor );
			m_kNormalList.insert( akEdgeNorm[iV] );
			m_kVertexList.insert( akEdgeVector[iV] );
		}
	}
}
//******************************************************************************
void Polygonizer::marchTetra(Vector *pakTetraPos, Real *pafTetraValue)
{
	if(!m_pvFunction)
		return;
	
	Vector akEdgeVector[6];		// edge vertices
	Vector akEdgeNorm[6];		// edge normals

	// determine inside and outside points
	int iFlagIndex = 0;
	for(int iV = 0; iV < 4; iV++)
	{
		if (pafTetraValue[iV] <= m_fIsoLevel)
			iFlagIndex |= 1 << iV;
	}

	// get edge bits to determine surface intersection
	int iEdgeBits = ms_aiTetraEdgeBits[iFlagIndex];

	// return if tetra does not intersect with surface
	if (iEdgeBits == 0)
		return ;

	// determine intersection point for each edge
	for(int iE = 0; iE < 6; iE++)
	{
		// get the intersection point if there is one
		if(iEdgeBits & (1 << iE))
		{
			// get the tetra vertex indices
			int iV0 = ms_aaiTetraConnects[iE][0];
			int iV1 = ms_aaiTetraConnects[iE][1];

			// get the intersection point
			Real fOffset = getIntersect(pafTetraValue[iV0], 
										pafTetraValue[iV1], 
										m_fIsoLevel);
										
			// precompute the inverse of the intersection offset
			Real fInvOffset = 1.0 - fOffset;

			// create the edge
			akEdgeVector[iE].x() = fInvOffset * pakTetraPos[iV0].x() + 
								 fOffset * pakTetraPos[iV1].x();
								 
			akEdgeVector[iE].y() = fInvOffset * pakTetraPos[iV0].y() + 
								 fOffset * pakTetraPos[iV1].y();
								 
			akEdgeVector[iE].z() = fInvOffset * pakTetraPos[iV0].z() + 
								 fOffset * pakTetraPos[iV1].z();

			// get a normal for this edge
			getNormal(akEdgeNorm[iE], 
					  akEdgeVector[iE].x(), 
					  akEdgeVector[iE].y(), 
					  akEdgeVector[iE].z());
		}
	}
	
	// create the triangles (max 2) for the intersections
	for(int iTri = 0; iTri < 2; iTri++)
	{
		// return if not a valid triangle
		if (ms_aaiTetraTris[iFlagIndex][3*iTri] < 0)
			break;

		// for each triangle corner
		for(int iC = 0; iC < 3; iC++)
		{
			// get the vertex index
			int iV = ms_aaiTetraTris[iFlagIndex][3 * iTri + iC];

			// get a color value for this triangle
			Color kColor;				
			getColor(kColor, akEdgeVector[iV], akEdgeNorm[iV]);
			
			// add the colors, normals, and vertices
			m_kColorList.insert( kColor );
			m_kNormalList.insert( akEdgeNorm[iV] );
			m_kVertexList.insert( akEdgeVector[iV] );
		}
	}
}
//******************************************************************************
void Polygonizer::marchTetraCube(Real fX, Real fY, Real fZ, Real fScale)
{
	if(!m_pvFunction)
		return;
	
	Vector akCubePos[8];	// positions in cube
	Real afCubeValue[8];	// values in cube

	Vector akTetraPos[4];	// positions in tetra
	Real afTetraValue[4];	// values in tetra

	// get values for each cube corner
	int iV = 0;
	for(iV = 0; iV < 8; iV++)
	{
		akCubePos[iV].x() = fX + ms_aafCubeOffsets[iV][0] * fScale;
		akCubePos[iV].y() = fY + ms_aafCubeOffsets[iV][1] * fScale;
		akCubePos[iV].z() = fZ + ms_aafCubeOffsets[iV][2] * fScale;
	}

	// sample the values for each cube corner
	for(iV = 0; iV < 8; iV++)
		afCubeValue[iV] = sample(akCubePos[iV].x(),
		                         akCubePos[iV].y(),
		                         akCubePos[iV].z());

	// for each tetrahedron in the cube
	for(int iT = 0; iT < 6; iT++)
	{
		// for each vertex in the tetrahedron
		for (iV = 0; iV < 4; iV++)
		{
			// get the tetra index
			int iTC = ms_aaiCubeTetras[iT][iV];

			// get the vertex positions
			akTetraPos[iV].x() = akCubePos[iTC].x();
			akTetraPos[iV].y() = akCubePos[iTC].y();
			akTetraPos[iV].z() = akCubePos[iTC].z();

			// copy the cube value
			afTetraValue[iV] = afCubeValue[iTC];
		}
		
		// perform the tetra march
		marchTetra(akTetraPos, afTetraValue);
	}
}
//******************************************************************************
void Polygonizer::evaluate(MarchMethod eType)
{
	if(!m_pvFunction)
		return;
	
	Int iX = 0, iY = 0, iZ = 0;
	
	// clear out the geometry list
	m_kVertexList.clear();
	m_kNormalList.clear();
	m_kColorList.clear();
		
	// perform appropriate march type
	// switch done outside the loop to avoid checking at every cell
	if (eType == Polygonizer::MM_CUBES)
	{
		for (iX = 0; iX < m_iCellCount; iX++)
		{
			for (iY = 0; iY < m_iCellCount; iY++)
			{
				for (iZ = 0; iZ < m_iCellCount; iZ++)
				{
					marchCube( iX * m_fDelta, 
							   iY * m_fDelta, 
							   iZ * m_fDelta, 
							   m_fDelta);
				}
			}
		}
	}
	else if(eType == Polygonizer::MM_TETRA)
	{
		for (iX = 0; iX < m_iCellCount; iX++)
		{
			for (iY = 0; iY < m_iCellCount; iY++)
			{
				for (iZ = 0; iZ < m_iCellCount; iZ++)
				{
					marchTetraCube( iX * m_fDelta, 
									iY * m_fDelta, 
									iZ * m_fDelta, 
									m_fDelta);
				}
			}
		}
	}
}
//******************************************************************************
