#include "platform_gl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_OFFSET(i) ((void*)(i))

GLuint create_vbo(const GLsizeiptr size, const GLvoid* data, const GLenum usage);

#ifdef __cplusplus
}
#endif
