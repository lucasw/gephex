#ifndef INCLUDED_VIDEODEV_OSTREAMS
#define INCLUDED_VIDEODEV_OSTREAMS

#include <iostream>

struct video_capability;
struct video_window;
struct video_mbuf;
struct video_channel;
struct video_picture;

std::ostream& operator<<(std::ostream&s , const video_capability cap);
std::ostream& operator<<(std::ostream&s , const video_window vidwin);
std::ostream& operator<<(std::ostream&s , const video_mbuf mbuf);
std::ostream& operator<<(std::ostream&s , const video_channel channel);
std::ostream& operator<<(std::ostream&s , const video_picture);

#endif
