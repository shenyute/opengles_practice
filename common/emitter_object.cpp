#include "emitter_object.h"
#include "platform_log.h"
#include "asset_utils.h"
#include <stdlib.h>
#include <time.h>

EmitterObject::EmitterObject()
  : m_life(0.f)
  , m_time(0.f)
{
  m_shader = new EmitterShader();
}

EmitterObject::~EmitterObject()
{
  delete m_shader;
}

void EmitterObject::RenderWithProjection(Matrix4f& projectionMatrix)
{
  // Switch Buffers
  glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer);

  // Uniforms
  glUniformMatrix4fv(m_shader->u_ProjectionMatrix, 1, 0, projectionMatrix.data());
  glUniform2f(m_shader->u_Gravity, m_gravity[0], m_gravity[1]);
  glUniform1f(m_shader->u_Time, m_time);
  glUniform1f(m_shader->u_eRadius, m_emitter.eRadius);
  glUniform1f(m_shader->u_eVelocity, m_emitter.eVelocity);
  glUniform1f(m_shader->u_eDecay, m_emitter.eDecay);
  glUniform1f(m_shader->u_eSizeStart, m_emitter.eSizeStart);
  glUniform1f(m_shader->u_eSizeEnd, m_emitter.eSizeEnd);
  glUniform3f(m_shader->u_eColorStart, m_emitter.eColorStart[0], m_emitter.eColorStart[1], m_emitter.eColorStart[2]);
  glUniform3f(m_shader->u_eColorEnd, m_emitter.eColorEnd[0], m_emitter.eColorEnd[1], m_emitter.eColorEnd[2]);
  glUniform1i(m_shader->u_Texture, 0);
  glUniform2f(m_shader->u_ePosition, m_emitter.ePosition[0], m_emitter.ePosition[1]);

  // Attributes
  glEnableVertexAttribArray(m_shader->a_pID);
  glEnableVertexAttribArray(m_shader->a_pRadiusOffset);
  glEnableVertexAttribArray(m_shader->a_pVelocityOffset);
  glEnableVertexAttribArray(m_shader->a_pDecayOffset);
  glEnableVertexAttribArray(m_shader->a_pSizeOffset);
  glEnableVertexAttribArray(m_shader->a_pColorOffset);

  glVertexAttribPointer(m_shader->a_pID, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, pID)));
  glVertexAttribPointer(m_shader->a_pRadiusOffset, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, pRadiusOffset)));
  glVertexAttribPointer(m_shader->a_pVelocityOffset, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, pVelocityOffset)));
  glVertexAttribPointer(m_shader->a_pDecayOffset, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, pDecayOffset)));
  glVertexAttribPointer(m_shader->a_pSizeOffset, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, pSizeOffset)));
  glVertexAttribPointer(m_shader->a_pColorOffset, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, pColorOffset)));

  // Draw particles
  glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
  glDisableVertexAttribArray(m_shader->a_pID);
  glDisableVertexAttribArray(m_shader->a_pRadiusOffset);
  glDisableVertexAttribArray(m_shader->a_pVelocityOffset);
  glDisableVertexAttribArray(m_shader->a_pDecayOffset);
  glDisableVertexAttribArray(m_shader->a_pSizeOffset);
  glDisableVertexAttribArray(m_shader->a_pColorOffset);
}

bool EmitterObject::UpdateLifeCycle(double timeElapsed)
{
  m_time += timeElapsed;
  if(m_time < m_life)
      return true;
  else return false;
}

void EmitterObject::Init(const char* fileName, Vector2f& position)
{
  m_particleBuffer = 0;
  LoadShader();
  LoadTexture(fileName);
  LoadParticleSystem(position);
}

void EmitterObject::LoadShader()
{
  m_shader->LoadShader("shaders/Emitter.vsh", "shaders/Emitter.fsh");
  glUseProgram(m_shader->program);
}

float randomFloatBetween(float min,float max)
{
    float range = max - min;
    return (((float) (random() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * range) + min;
}

float degreesToRadian(float degree) {
  return degree / 180.0f * M_PI;
}

void EmitterObject::LoadTexture(const char* fileName)
{
  GLuint texture = load_png_asset_into_texture(fileName);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void EmitterObject::LoadParticleSystem(Vector2f& position)
{
  Emitter newEmitter;

  // Offset bounds
  float oRadius = 0.10f;      // 0.0 = circle; 1.0 = ring
  float oVelocity = 0.50f;    // Speed
  float oDecay = 0.25f;       // Time
  float oSize = 8.00f;        // Pixels
  float oColor = 0.25f;       // 0.5 = 50% shade offset

  // Load Particles
  for(int i=0; i<NUM_PARTICLES; i++)
  {
    // Assign a unique ID to each particle, between 0 and 360 (in radians)
    newEmitter.eParticles[i].pID = degreesToRadian(((float)i/(float)NUM_PARTICLES)*360.0f);

    // Assign random offsets within bounds
    newEmitter.eParticles[i].pRadiusOffset = randomFloatBetween(oRadius, 1.00f);
    newEmitter.eParticles[i].pVelocityOffset = randomFloatBetween(-oVelocity, oVelocity);
    newEmitter.eParticles[i].pDecayOffset = randomFloatBetween(-oDecay, oDecay);
    newEmitter.eParticles[i].pSizeOffset = randomFloatBetween(-oSize, oSize);
    float r = randomFloatBetween(-oColor, oColor);
    float g = randomFloatBetween(-oColor, oColor);
    float b = randomFloatBetween(-oColor, oColor);
    newEmitter.eParticles[i].pColorOffset = Vector3f(r, g, b);
  }

  // Load Properties
  newEmitter.eRadius = 0.75f;                                     // Blast radius
  newEmitter.eVelocity = 3.00f;                                   // Explosion velocity
  newEmitter.eDecay = 2.00f;                                      // Explosion decay
  newEmitter.eSizeStart = 32.00f;                                 // Fragment start size
  newEmitter.eSizeEnd = 8.00f;                                    // Fragment end size
  float colorR = ((float) (random() % ((unsigned)RAND_MAX)) / RAND_MAX);
  float colorG = ((float) (random() % ((unsigned)RAND_MAX)) / RAND_MAX);
  float colorB = ((float) (random() % ((unsigned)RAND_MAX)) / RAND_MAX);
  //newEmitter.eColorStart = Vector3f(1.00f, 0.50f, 0.00f);   // Fragment start color
  newEmitter.eColorStart = Vector3f(colorR, colorG, colorB);
  newEmitter.eColorEnd = Vector3f(0.25f, 0.00f, 0.00f);     // Fragment end color
  newEmitter.ePosition = position;

  // Set global factors
  float growth = newEmitter.eRadius / newEmitter.eVelocity;       // Growth time
  m_life = growth + newEmitter.eDecay + oDecay;                    // Simulation lifetime

  float drag = 10.00f;                                            // Drag (air resistance)
  m_gravity = Vector2f(0.00f, -9.81f*(1.0f/drag));           // World gravity

  // Set Emitter & VBO
  m_emitter = newEmitter;
  glGenBuffers(1, &m_particleBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_emitter.eParticles), m_emitter.eParticles, GL_STATIC_DRAW);
}
