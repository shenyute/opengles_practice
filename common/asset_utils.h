#include "platform_gl.h"
 
#ifdef __cplusplus
extern "C" {
#endif

GLuint load_png_asset_into_texture(const char* relative_path);
GLuint build_program_from_assets(
    const char* vertex_shader_path, const char* fragment_shader_path);

#ifdef __cplusplus
}
#endif
