//
// Created by seifer on 2018/9/12.
//

//this is test for FrameBuffer
#include <jni.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <time.h>

#include <linux/fb.h>
#include <linux/kd.h>

std::string getStringFromOtherFile(void)
{
    return "this string is from frameBuffer.cpp";
}

std::string getFrameBuffer(void)
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    long int location = 0;
    std::string ret;
    fbfd = open("/dev/graphics/fb0", O_RDWR);
    if (!fbfd)
    {
        ret = "Error: cannot open framebuffer device.\n";
        return ret;
    }

    ret = "The framebuffer device was opened successfully.\n";
    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo))
    {
        ret = "Error reading fixed information.\n";
        //return ret;
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))
    {
        ret = "Error reading variable information.\n";
        return ret;
    }
    screensize = finfo.smem_len;
    // screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel >> 3  // >>3 表示算出字节数
    fbp = (char *) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

    if ((int) fbp == -1)
    {
        ret = "Error: failed to map framebuffer device to memory.\n";
        return ret;
    }

    return ret;
}