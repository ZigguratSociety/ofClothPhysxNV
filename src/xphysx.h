#include <ctype.h>
#include "PxPhysicsAPI.h"
#include "RenderBuffer.h"

#pragma comment(lib, "PhysX3DEBUG_x64.lib") 
#pragma comment(lib, "PhysX3CommonDEBUG_x64.lib") 
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")


using namespace physx;

int oldTimeSinceStart = 0;
float mAccumulator = 0.0f;

PxPhysics*               gPhysicsSDK = NULL;
PxFoundation*            gFoundation = NULL;
PxDefaultErrorCallback   gDefaultErrorCallback;
PxDefaultAllocator       gDefaultAllocatorCallback;
PxScene*                 gScene = NULL;                             
PxReal                   gTimeStep = 1.0f/60;
PxCloth* gCloth = NULL;

void stepPhysX() {
        gScene->simulate(gTimeStep);
        gScene->fetchResults(true);
}

void shutdown() {
	gPhysicsSDK->release();
        gFoundation->release();
}

void CreateCloth() {
        PxTransform gPose = PxTransform(PxVec3(0,1,0));
        PxU32 resolution = 20;
        PxU32 numParticles = resolution*resolution;
        PxU32 numTriangles = 2*(resolution-1)*(resolution-1);
        PxClothParticle* particles = new PxClothParticle[numParticles];
        PxVec3 center(0.5f, 0.3f, 0.0f);
        PxVec3 delta = 1.0f/(resolution-1) * PxVec3(15.0f, 15.0f, 15.0f);
        PxClothParticle* pIt = particles;
        for(PxU32 i=0; i<resolution; ++i)
        {
                for(PxU32 j=0; j<resolution; ++j, ++pIt)
                {
                        pIt->invWeight = j+1<resolution ? 1.0f : 0.0f;
                        pIt->pos = delta.multiply(PxVec3(PxReal(i),
                                PxReal(j), -PxReal(j))) - center;
                }
        }
        PxU32* triangles = new PxU32[3*numTriangles];
        PxU32* iIt = triangles;
        for(PxU32 i=0; i<resolution-1; ++i)
        {
                for(PxU32 j=0; j<resolution-1; ++j)
                {
                        PxU32 odd = j&1u, even = 1-odd;
                        *iIt++ = i*resolution + (j+odd);
                        *iIt++ = (i+odd)*resolution + (j+1);
                        *iIt++ = (i+1)*resolution + (j+even);
                        *iIt++ = (i+1)*resolution + (j+even);
                        *iIt++ = (i+even)*resolution + j;
                        *iIt++ = i*resolution + (j+odd);
                }
        }
        PxClothMeshDesc meshDesc;
        meshDesc.points.count = numParticles;
        meshDesc.points.stride = sizeof(PxClothParticle);
        meshDesc.points.data = particles;
        meshDesc.invMasses.count = numParticles;
        meshDesc.invMasses.stride = sizeof(PxClothParticle);
        meshDesc.invMasses.data = &particles->invWeight;
        meshDesc.triangles.count = numTriangles;
        meshDesc.triangles.stride = 3*sizeof(PxU32);
        meshDesc.triangles.data = triangles;
        PxClothFabric* fabric = PxClothFabricCreate(*gPhysicsSDK, meshDesc, PxVec3(0, 1, 0));
        delete[] triangles;
        gCloth = gPhysicsSDK->createCloth(gPose, *fabric, particles, PxClothFlags(0));
        fabric->release();
        delete[] particles;
        gCloth->setSolverFrequency(240.0f);
        gScene->addActor(*gCloth);
}

void InitPhysX()
{
        gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
        gPhysicsSDK = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale() );
        if(gPhysicsSDK == NULL) {
                cerr<<"Error creating PhysX3 device, Exiting..."<<endl;
                exit(1);
        }
        PxSceneDesc sceneDesc(gPhysicsSDK->getTolerancesScale());
        sceneDesc.gravity               = PxVec3(0.0f, -9.8f, 0.0f);
        sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
        sceneDesc.filterShader  = PxDefaultSimulationFilterShader;
        gScene = gPhysicsSDK->createScene(sceneDesc);
        gScene->setVisualizationParameter(PxVisualizationParameter::eSCALE,             1.0);
        gScene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES,  1.0f);
        gScene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES,        1.0f);
        gScene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_HORIZONTAL,  1.0f);
        gScene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_VERTICAL,1.0f);
        gScene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_BENDING,1.0f);
        PxMaterial* material = gPhysicsSDK->createMaterial(0.5f,0.5f,0.5f);
        PxTransform planePos =  PxTransform(PxVec3(0, 0, 0),PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
        PxRigidStatic* plane =  gPhysicsSDK->createRigidStatic(planePos);
        plane->createShape(PxPlaneGeometry(), *material);
        gScene->addActor(*plane);
        CreateCloth();
        gCloth->addCollisionPlane(PxClothCollisionPlane(PxVec3(0, 1, 0), 0.0f));
        gCloth->addCollisionConvex(1 << 0); // Convex references the first plane
}
