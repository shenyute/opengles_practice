#include "gl_api.h"
#include "asset_utils.h"
#include "buffer.h"
#include "image.h"
#include "platform_asset_utils.h"
#include "platform_gl.h"
#include "platform_log.h"
#include "macros.h"
#include "shader.h"
#include "texture.h"
#include "emitter_object.h"

#include <math.h>
 
static GLuint texture;
static GLuint buffer;
static GLuint program;
 
static GLint a_position_location;
static GLint a_texture_coordinates_location;
static GLint u_texture_unit_location;
static EmitterObject s_object;
 
// position X, Y, texture S, T
static const float rect[] = {-1.0f, -1.0f, 0.0f, 0.0f,
                             -1.0f,  1.0f, 0.0f, 1.0f,
                              1.0f, -1.0f, 1.0f, 0.0f,
                              1.0f,  1.0f, 1.0f, 1.0f};

void on_surface_created() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    s_object.Init();
}
 
void on_surface_changed() {
/*
    texture = load_png_asset_into_texture("textures/air_hockey_surface.png");
    buffer = create_vbo(sizeof(rect), rect, GL_STATIC_DRAW);
    program = build_program_from_assets("shaders/shader.vsh", "shaders/shader.fsh");
 
    a_position_location = glGetAttribLocation(program, "a_Position");
    a_texture_coordinates_location = 
        glGetAttribLocation(program, "a_TextureCoordinates");
    u_texture_unit_location = glGetUniformLocation(program, "u_TextureUnit");
*/
}

void on_draw_frame() {
    glClearColor(0.30f, 0.74f, 0.20f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render Emitter
    // Create Projection Matrix
    float aspectRatio = 768.0f / 1022;
    Affine3f m;
    m = Scaling(1.0f, aspectRatio, 1.0f);
    Matrix4f projectionMatrix = Matrix4f::Identity();
    projectionMatrix = m.matrix();
    s_object.RenderWithProjection(projectionMatrix);
/*
 
    glUseProgram(program);
 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(u_texture_unit_location, 0);
 
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(a_position_location, 2, GL_FLOAT, GL_FALSE, 
        4 * sizeof(GL_FLOAT), BUFFER_OFFSET(0));
    glVertexAttribPointer(a_texture_coordinates_location, 2, GL_FLOAT, GL_FALSE, 
        4 * sizeof(GL_FLOAT), BUFFER_OFFSET(2 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(a_position_location);
    glEnableVertexAttribArray(a_texture_coordinates_location);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
*/
}

void on_touch_press(float x, float y) {
  DEBUG_LOG_PRINT_D("gl_api", "%f,%f", x, y);
}
