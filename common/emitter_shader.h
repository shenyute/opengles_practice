#include "platform_gl.h"

class EmitterShader
{
public:
  EmitterShader();
  ~EmitterShader();
  void LoadShader(const char* vsh, const char* fsh);

public:
  // Program Handle
  GLuint    program;

  // Attribute Handles
  GLint     a_pID;
  GLint     a_pRadiusOffset;
  GLint     a_pVelocityOffset;
  GLint     a_pDecayOffset;
  GLint     a_pSizeOffset;
  GLint     a_pColorOffset;

  // Uniform Handles
  GLuint    u_ProjectionMatrix;
  GLint     u_Gravity;
  GLint     u_Time;
  GLint     u_eRadius;
  GLint     u_eVelocity;
  GLint     u_eDecay;
  GLint     u_eSize;
  GLint     u_eColor;
};
