package com.example.ytshen.opengles;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private GLSurfaceView mSurfaceView;
    private boolean mRendererSet;
    private RendererWrapper mRenderer;

    private boolean isProbablyEmulator() {
        return Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
                && (Build.FINGERPRINT.startsWith("generic")
                || Build.FINGERPRINT.startsWith("unknown")
                || Build.MODEL.contains("google_sdk")
                || Build.MODEL.contains("Emulator")
                || Build.MODEL.contains("Android SDK built for x86"));
    }

    @Override
    protected void onPause() {
        super.onPause();

        if (mSurfaceView != null) {
            mSurfaceView.onPause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        if (mSurfaceView != null) {
            mSurfaceView.onResume();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActivityManager activityManager
                = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

        final boolean supportsEs2 =
                configurationInfo.reqGlEsVersion >= 0x20000 || isProbablyEmulator();

        if (supportsEs2) {
            mSurfaceView = new GLSurfaceView(this);

            if (isProbablyEmulator()) {
                // Avoids crashes on startup with some emulator images.
                mSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
            }

            mSurfaceView.setEGLContextClientVersion(2);
            mRenderer = new RendererWrapper(this);
            mSurfaceView.setRenderer(mRenderer);
            mRendererSet = true;
            mSurfaceView.setOnTouchListener(new View.OnTouchListener() {
                @Override
                public boolean onTouch(View v, MotionEvent event) {
                    if (event != null) {
                        // Convert touch coordinates into normalized device
                        // coordinates, keeping in mind that Android's Y
                        // coordinates are inverted.
                        final float normalizedX = (event.getX() / (float) v.getWidth()) * 2 - 1;
                        final float normalizedY = -((event.getY() / (float) v.getHeight()) * 2 - 1);

                        if (event.getAction() == MotionEvent.ACTION_DOWN) {
                            mSurfaceView.queueEvent(new Runnable() {
                                @Override
                                public void run() {
                                    mRenderer.handleTouchPress(normalizedX, normalizedY);
                                }});
                        }
                        return true;
                    } else {
                        return false;
                    }
                }});
            setContentView(mSurfaceView);
        } else {
            // Should never be seen in production, since the manifest filters
            // unsupported devices.
            Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
                    Toast.LENGTH_LONG).show();
            return;
        }
    }
}
