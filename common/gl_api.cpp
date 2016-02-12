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
#include <vector>
 
static std::vector<EmitterObject*> s_emitters;
 
// position X, Y, texture S, T
static const float rect[] = {-1.0f, -1.0f, 0.0f, 0.0f,
                             -1.0f,  1.0f, 0.0f, 1.0f,
                              1.0f, -1.0f, 1.0f, 0.0f,
                              1.0f,  1.0f, 1.0f, 1.0f};

void on_surface_created() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

double now_ms(void) {
  struct timespec res;
  clock_gettime(CLOCK_REALTIME, &res);
  double ms = 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;
  return ms;
}

void update_life_cycle() {
  static double s_lastTime = 0;
  double now = now_ms();
  double timeElapsed = 0;

  if (s_emitters.size() > 0) {
    if (s_lastTime != 0)
      timeElapsed = ((now - s_lastTime) / 1000.0f);
    //DEBUG_LOG_PRINT_D("gl_api", "update_life_cycle timeElapsed=%f", timeElapsed);
    std::vector<EmitterObject*>::iterator it = s_emitters.begin();
    for (; it != s_emitters.end();) {
      bool alive = (*it)->UpdateLifeCycle(timeElapsed);
      if (!alive) {
        delete *it;
        it = s_emitters.erase(it);
      } else
        ++it;
    }
  }
  s_lastTime = now;
}

void on_draw_frame() {
    //glClearColor(0.30f, 0.74f, 0.20f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Set the blending function (normal w/ premultiplied alpha)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    update_life_cycle();
    // Create Projection Matrix
    float aspectRatio = 768.0f / 1022;
    Affine3f m;
    m = Scaling(1.0f, aspectRatio, 1.0f);
    Matrix4f projectionMatrix = Matrix4f::Identity();
    projectionMatrix = m.matrix();
    // Render Emitter
    if (s_emitters.size() > 0) {
      std::vector<EmitterObject*>::iterator it = s_emitters.begin();
      for (; it != s_emitters.end(); ++it) {
        (*it)->RenderWithProjection(projectionMatrix);
      }
    }
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
  DEBUG_LOG_PRINT_D("gl_api", "on_touch_press %f,%f count=%d", x, y, s_emitters.size());
  EmitterObject* emitter = new EmitterObject();
  Vector2f position(x, y);
  emitter->Init("textures/texture_64.png", position);
  s_emitters.push_back(emitter);
}

void on_long_press(float x, float y) {
  DEBUG_LOG_PRINT_D("gl_api", "on_long_press %f,%f count=%d", x, y, s_emitters.size());
}
