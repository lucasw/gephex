#ifndef INCLUDED_AA_OUTPUT_H
#define INCLUDED_AA_OUTPUT_H

struct OutputDriver;

/**
 * The returned Driver must be freed by the caller!
 */
struct OutputDriver* AA_get_driver();

#endif
