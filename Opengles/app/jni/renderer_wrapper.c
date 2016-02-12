#include <jni.h>
#include "gl_api.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_example_ytshen_opengles_RendererWrapper_on_1surface_1created
    (JNIEnv *env, jclass clazz)
{
  UNUSED(env);
  UNUSED(clazz);
  on_surface_created();
}

JNIEXPORT void JNICALL Java_com_example_ytshen_opengles_RendererWrapper_on_1surface_1changed
    (JNIEnv *env, jclass clazz)
{
  UNUSED(env);
  UNUSED(clazz);
  on_surface_changed();
}

JNIEXPORT void JNICALL Java_com_example_ytshen_opengles_RendererWrapper_on_1draw_1frame
    (JNIEnv *env, jclass clazz)
{
  UNUSED(env);
  UNUSED(clazz);
  on_draw_frame();
}

JNIEXPORT void JNICALL Java_com_example_ytshen_opengles_RendererWrapper_on_1touch_1press(
    JNIEnv* env, jclass cls, jfloat normalized_x, jfloat normalized_y) {
    UNUSED(env);
    UNUSED(cls);
    on_touch_press(normalized_x, normalized_y);
}

JNIEXPORT void JNICALL Java_com_example_ytshen_opengles_RendererWrapper_on_1long_1press(
    JNIEnv* env, jclass cls, jfloat normalized_x, jfloat normalized_y) {
    UNUSED(env);
    UNUSED(cls);
    on_long_press(normalized_x, normalized_y);
}

#ifdef __cplusplus
}
#endif
