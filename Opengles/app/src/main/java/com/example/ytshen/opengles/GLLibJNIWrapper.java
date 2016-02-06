package com.example.ytshen.opengles;

public class GLLibJNIWrapper{
    static {
        System.loadLibrary("glapi");
    }

    public static native void on_surface_created();

    public static native void on_surface_changed(int width, int height);

    public static native void on_draw_frame();
}
