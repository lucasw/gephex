#ifndef INCLUDED_XIMAGE_OUTPUT_H
#define INCLUDED_XIMAGE_OUTPUT_H

struct OutputDriver;

/**
 * The returned Driver must be freed by the caller!
 */
struct OutputDriver* XImage_get_driver();

#endif
