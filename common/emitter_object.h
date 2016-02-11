#include "platform_gl.h"
#include "Eigen/Dense"
#include <Eigen/Geometry>
#include "emitter_shader.h"

#define NUM_PARTICLES 180

using namespace Eigen;

struct Particle;
typedef struct Particle
{
    float       pID;
    float       pRadiusOffset;
    float       pVelocityOffset;
    float       pDecayOffset;
    float       pSizeOffset;
    Vector3f    pColorOffset;
  Particle()
    : pID(0.f)
    , pRadiusOffset(0.f)
    , pVelocityOffset(0.f)
    , pDecayOffset(0.f)
    , pSizeOffset(0.f) {}

} Particle;

struct Emitter;
typedef struct Emitter
{
    Particle    eParticles[NUM_PARTICLES];
    float       eRadius;
    float       eVelocity;
    float       eDecay;
    float       eSizeStart;
    float       eSizeEnd;
    Vector3f    eColorStart;
    Vector3f    eColorEnd;
  Emitter()
    : eRadius(0.f)
    , eVelocity(0.f)
    , eDecay(0.f)
    , eSizeStart(0.f)
    , eSizeEnd(0.f) { }
} Emitter;

class EmitterObject
{
public:
  EmitterObject();
  ~EmitterObject();
  void RenderWithProjection(Matrix4f& matrix);
  void UpdateLifeCycle(double timeEscape);
  void Init(const char* fileName);

private:
  void LoadShader();
  void LoadTexture(const char* fileName);
  void LoadParticleSystem();

private:
  Vector2f m_gravity;
  double m_life;
  double m_time;
  EmitterShader* m_shader;
  Emitter m_emitter;
};
