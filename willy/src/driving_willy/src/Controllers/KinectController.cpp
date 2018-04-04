#include "../include.h"

using namespace std;

KinectController::KinectController(WillyController *Controller, int argc, char **argv)
{
    _controller = Controller;
}

void KinectController::Start()
{
    void depth_cb(freenect_device * dev, void *data, uint32_t timestamp)
    {
        printf("Received depth frame at %d\n", timestamp);
    }

    void video_cb(freenect_device * dev, void *data, uint32_t timestamp)
    {
        printf("Received video frame at %d\n", timestamp);
    }

    volatile bool running = true;
    void signalHandler(int signal)
    {
        if (signal == SIGINT || signal == SIGTERM || signal == SIGQUIT)
        {
            running = false;
        }
    }

    int main(int argc, char **argv)
    {
        // Handle signals gracefully.
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);
        signal(SIGQUIT, signalHandler);

        // Initialize libfreenect.
        freenect_context *fn_ctx;
        int ret = freenect_init(&fn_ctx, NULL);
        if (ret < 0)
            return ret;

        // Show debug messages and use camera only.
        freenect_set_log_level(fn_ctx, FREENECT_LOG_DEBUG);
        freenect_select_subdevices(fn_ctx, FREENECT_DEVICE_CAMERA);

        // Find out how many devices are connected.
        int num_devices = ret = freenect_num_devices(fn_ctx);
        if (ret < 0)
            return ret;
        if (num_devices == 0)
        {
            printf("No device found!\n");
            freenect_shutdown(fn_ctx);
            return 1;
        }

        // Open the first device.
        freenect_device *fn_dev;
        ret = freenect_open_device(fn_ctx, &fn_dev, 0);
        if (ret < 0)
        {
            freenect_shutdown(fn_ctx);
            return ret;
        }

        // Set depth and video modes.
        ret = freenect_set_depth_mode(fn_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_MM));
        if (ret < 0)
        {
            freenect_shutdown(fn_ctx);
            return ret;
        }
        ret = freenect_set_video_mode(fn_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB));
        if (ret < 0)
        {
            freenect_shutdown(fn_ctx);
            return ret;
        }

        // Set frame callbacks.
        freenect_set_depth_callback(fn_dev, depth_cb);
        freenect_set_video_callback(fn_dev, video_cb);

        // Start depth and video.
        ret = freenect_start_depth(fn_dev);
        if (ret < 0)
        {
            freenect_shutdown(fn_ctx);
            return ret;
        }
        ret = freenect_start_video(fn_dev);
        if (ret < 0)
        {
            freenect_shutdown(fn_ctx);
            return ret;
        }

        // Run until interruption or failure.
        while (running && freenect_process_events(fn_ctx) >= 0)
        {
        }

        printf("Shutting down\n");

        // Stop everything and shutdown.
        freenect_stop_depth(fn_dev);
        freenect_stop_video(fn_dev);
        freenect_close_device(fn_dev);
        freenect_shutdown(fn_ctx);

        printf("Done!\n");

        return 0;
    }
}