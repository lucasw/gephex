#ifndef IFRAMEGRABBER_H
#define IFRAMEGRABBER_H

namespace image
{
    typedef int* Frame;
}

class IFrameGrabber {
public:
  /**
   * Grabs next Frame from the Camera
   */
  virtual void grabNextImage() = 0;

  /**
   * Get last grabbed Frame
   */
  virtual void getGrabbedImage(image::Frame&) = 0;

  virtual ~IFrameGrabber(){};
};

#endif
