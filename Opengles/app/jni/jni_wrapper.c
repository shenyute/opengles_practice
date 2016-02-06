#include <jni.h>
#include "../../../common/gl_api.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_example_ytshen_opengles_GLLibJNIWrapper_on_1surface_1created
    (JNIEnv *env, jclass clazz)
{
  on_surface_created();
}

JNIEXPORT void JNICALL Java_com_example_ytshen_opengles_GLLibJNIWrapper_on_1surface_1changed
    (JNIEnv *env, jclass clazz)
{
  on_surface_changed();
}

JNIEXPORT void JNICALL Java_com_example_ytshen_opengles_GLLibJNIWrapper_on_1draw_1frame
    (JNIEnv *env, jclass clazz)
{
  on_draw_frame();
}

#ifdef __cplusplus
}
#endif
