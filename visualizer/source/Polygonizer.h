#ifndef DG_POLYGONIZER_H
#define DG_POLYGONIZER_H

#include "DataTypes.h"
#include "CubeTables.h"
#include "Vector.h"
#include "Color.h"
#include "Set.h"

namespace dg
{

//******************************************************************************
class Polygonizer
{
	
public:
	
	enum MarchMethod
	{
		MM_CUBES,
		MM_TETRA
	};
	
	// typedefs for improved readibility
	typedef Set<Color> ColorList;
	typedef Set<Vector> VectorList;
	typedef Real (*Function)(Real fX, Real fY, Real fZ);

	// main constructor
	Polygonizer(Function pvFunction=NULL, 
				Int iCellCount=8, 
				Real fScale = 1.0, 
				Real fIsoLevel=1.0);
	
	// evaluates the given function
	inline Real sample(Real fX, Real fY, Real fZ);
	
	// function access methods
	inline void setFunction( Function pvFunction );
	
	// inverse normals methods (for density functions)
	inline void setInverseNormals(bool bInvNormals);
	inline bool getInverseNormals();
	
	// cell count access methods
	inline void setCellCount( Int iCellCount );
	inline Int getCellCount();
	
	// iso access methods
	inline void setIsoLevel( Real fIsoLevel );
	inline Real getIsoLevel();
	
	// function evaluation offset access methods
	inline void setOffset( Real fX, Real fY, Real fZ );	
	inline void getOffset(Real& fX, Real& fY, Real& fZ );
	
	// function evaluation scale access methods
	inline void setScale(Real fScale);
	inline Real getScale();
	
	// normal evaluation epsilon access methods
	inline void setEpsilon(Real fEpsilon);
	inline Real getEpsilon();
	
	inline VectorList& getVertices(){ return m_kVertexList; }
	inline VectorList& getNormals(){ return m_kNormalList; }
	inline ColorList& getColors(){ return m_kColorList; }
		
	// interpolates between two values to determine a point of intersection
	inline Real getIntersect(Real fV1, Real fV2, Real fLevel);
		
	// interprets position and normal and assigns a color
	inline void getColor(Color &rkColor, Vector &rkPos, Vector &rkNormal);
	
	// calculates a normal by sampling the given function at several locations
	void getNormal(Vector &rkNormal, Real fX, Real fY, Real fZ);
	
	// marches a single cube
	void marchCube(Real fX, Real fY, Real fZ, Real fScale);
	
	// marches a single tetrahedron
	void marchTetra(Vector *pakTetraPos, Real *pafTetraValue);
	
	// marches a single cube by using six tetrahedrons
	void marchTetraCube(Real fX, Real fY, Real fZ, Real fScale);
	
	// evaluates the given function, creating the geometry
	void evaluate(MarchMethod eType=MM_TETRA);
	
protected:

	Function m_pvFunction;
	
	bool m_bInverseNormals;
	
	Int m_iCellCount;
	
	Real m_fScale;
	Real m_fDelta;
	Real m_fEpsilon;
	Real m_fIsoLevel;
		
	Vector m_kOffset;
	
	VectorList m_kVertexList;
	VectorList m_kNormalList;
	ColorList m_kColorList;
};
//******************************************************************************

#include "Polygonizer.inc"

//******************************************************************************

} // end namespace dg

//******************************************************************************
#endif
