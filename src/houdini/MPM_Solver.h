#ifndef __MPM_Solver_h__
#define __MPM_Solver_h__

#include <UT/UT_IStream.h>
#include <GA/GA_Types.h>
#include <GU/GU_DetailHandle.h>
#include <SIM/SIM_OptionsUser.h>
#include <SIM/SIM_SingleSolver.h>
#include <SIM/SIM_Geometry.h>

#include "../engine.h"
#include "../particle.h"

// Grid
#define MPM_GRIDX "gridx"
#define MPM_GRIDY "gridy"
#define MPM_GRIDZ "gridz"
#define MPM_SPACING "spacing"

//
//// Particle
//#define MPM_P_MASS "mass"
//#define MPM_P_VOLUME "volume"
//#define MPM_P_VEL "velocity"
//#define MPM_P_BP "Bp"
//#define MPM_P_F "F"
//#define MPM_P_FE "Fe"
//#define MPM_P_FP "Fp"
//#define MPM_P_ALPHA "alpha"
//#define MPM_P_Q "q"

// Young's modulus
#define MPM_E "e"
// Poisson's ratio
#define MPM_NU "nu"
// Particle Density
#define MPM_DENSITY "density"

// BoundingBox
#define MPM_BBOXMIN "bboxMin"
#define MPM_BBOXMAX "bboxMax"

// Simulation
#define MPM_TIMESTEP "timestep"

// Collision
#define MPM_COLLISION_OBJECT "CollisionObject"
// Collision Type
#define MPM_COLLISION_TYPE "CollisionType"
#define MPM_MUB "muB"

// Snow
#define MPM_THETAC "thetaC"
#define MPM_THETAS "thetaS"


#define MPM_MATERIAL "material"



class SIM_MPMSolver : public SIM_SingleSolver,
	public SIM_OptionsUser
{
public:	
	// I: int64
	// F: fpreal64
	// V3: UT_Vector3
	GETSET_DATA_FUNCS_I(MPM_GRIDX, GridX);
	GETSET_DATA_FUNCS_I(MPM_GRIDY, GridY);
	GETSET_DATA_FUNCS_I(MPM_GRIDZ, GridZ);
	GETSET_DATA_FUNCS_F(MPM_SPACING, Spacing);

	//// Get Attribute Name
	//GETSET_DATA_FUNCS_S(MPM_P_MASS, PMass);
	//GETSET_DATA_FUNCS_S(MPM_P_VOLUME, PVolume);
	//GETSET_DATA_FUNCS_S(MPM_P_VEL, PVelocity);
	//GETSET_DATA_FUNCS_S(MPM_P_BP, PBp);
	//GETSET_DATA_FUNCS_S(MPM_P_F, PF);
	//GETSET_DATA_FUNCS_S(MPM_P_FE, PFe);
	//GETSET_DATA_FUNCS_S(MPM_P_FP, PFp);
	//GETSET_DATA_FUNCS_S(MPM_P_ALPHA, PAlpha);
	//GETSET_DATA_FUNCS_S(MPM_P_Q, PQ);

	GETSET_DATA_FUNCS_F(MPM_E, E);
	GETSET_DATA_FUNCS_F(MPM_NU, Nu);
	GETSET_DATA_FUNCS_F(MPM_DENSITY, Density);

	GETSET_DATA_FUNCS_V3(MPM_BBOXMIN, BBoxMin);
	GETSET_DATA_FUNCS_V3(MPM_BBOXMAX, BBoxMax);

	GETSET_DATA_FUNCS_F(MPM_TIMESTEP, Timestep);

	GETSET_DATA_FUNCS_I(MPM_MATERIAL, Material);

	GETSET_DATA_FUNCS_I(MPM_COLLISION_TYPE, CollisionType);
	GETSET_DATA_FUNCS_F(MPM_MUB, MuB);

	GETSET_DATA_FUNCS_F(MPM_THETAC, ThetaC);
	GETSET_DATA_FUNCS_F(MPM_THETAS, ThetaS);

	

protected:
	explicit SIM_MPMSolver(const SIM_DataFactory *factory);
	virtual ~SIM_MPMSolver();

	// This implements your own solver step
	SIM_Result solveSingleObjectSubclass(
		SIM_Engine& engine, SIM_Object& object,
		SIM_ObjectArray& feedbackToObjects,
		const SIM_Time& timeStep,
		bool objectIsNew
	);
private:
	static const SIM_DopDescription* getMyOwnSolverDescription();
	DECLARE_STANDARD_GETCASTTOTYPE();
	DECLARE_DATAFACTORY(SIM_MPMSolver, SIM_SingleSolver, "MPM Solver", getMyOwnSolverDescription());

	Vec3f worldMin;
	Vec3f localMax;

	// World: coordinte system in Houdini
	// Local: coordinate system in MPMEngine

	// Convert Houdini coordinates to MPMEngine coordinates
	inline Vec3f worldToLocal(Vec3f p0);
	// Convert MPMEngine coordinates to Houdini coordinates
	inline Vec3f localToWorld(Vec3f p1);

	bool checkValidLocalPosition(Vec3f pos, float threshold);

};

#endif

