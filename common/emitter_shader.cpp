#include "emitter_shader.h"
#include "asset_utils.h"

EmitterShader::EmitterShader()
{
}

EmitterShader::~EmitterShader()
{
}

void EmitterShader::LoadShader(const char* vsh, const char* fsh)
{
  program = build_program_from_assets(vsh, fsh);
  // Attributes
  this->a_pID = glGetAttribLocation(this->program, "a_pID");
  this->a_pRadiusOffset = glGetAttribLocation(this->program, "a_pRadiusOffset");
  this->a_pVelocityOffset = glGetAttribLocation(this->program, "a_pVelocityOffset");
  this->a_pDecayOffset = glGetAttribLocation(this->program, "a_pDecayOffset");
  this->a_pSizeOffset = glGetAttribLocation(this->program, "a_pSizeOffset");
  this->a_pColorOffset = glGetAttribLocation(this->program, "a_pColorOffset");

  // Uniforms
  this->u_ProjectionMatrix = glGetUniformLocation(this->program, "u_ProjectionMatrix");
  this->u_Gravity = glGetUniformLocation(this->program, "u_Gravity");
  this->u_Time = glGetUniformLocation(this->program, "u_Time");
  this->u_eRadius = glGetUniformLocation(this->program, "u_eRadius");
  this->u_eVelocity = glGetUniformLocation(this->program, "u_eVelocity");
  this->u_eDecay = glGetUniformLocation(this->program, "u_eDecay");
  this->u_eSizeStart = glGetUniformLocation(this->program, "u_eSizeStart");
  this->u_eSizeEnd = glGetUniformLocation(this->program, "u_eSizeEnd");
  this->u_eColorStart = glGetUniformLocation(this->program, "u_eColorStart");
  this->u_eColorEnd = glGetUniformLocation(this->program, "u_eColorEnd");
  this->u_Texture = glGetUniformLocation(this->program, "u_Texture");
}
