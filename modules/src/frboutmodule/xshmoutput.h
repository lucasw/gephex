#ifndef INCLUDED_XSHM_OUTPUT_H
#define INCLUDED_XSHM_OUTPUT_H

struct OutputDriver;

/**
 * The returned Driver must be freed by the caller!
 */
struct OutputDriver* XShm_get_driver();

#endif
