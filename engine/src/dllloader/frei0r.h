
/** \file
 * This is frei0r - a minimalistic plugin API for video effects.
 *
 * The main emphasis is on simplicity - there are many different applications
 * that use video effects, and they all have different requirements regarding
 * their internal plugin API. And that's why frei0r does not try to be a
 * one-in-all general video plugin API, but instead an API for the most
 * common video effects: simple filters or sources that can be controlled by
 * parameters.
 *
 * It's our hope that this way these simple effects can be shared between
 * many applications, avoiding their reimplementation by different
 * projects.
 *
 * On the other hand, this is not meant as a competing standard to
 * more ambitious efforts that try to satisfy the needs of many different
 * applications and more complex effects (like multiple inputs, multiple
 * outputs, different color models, keyframing, ...).
 *
 */

#ifndef INCLUDED_FREI0R_H
#define INCLUDED_FREI0R_H

//#include <inttypes.h>
#include "basic_types.h"

/**
 * The frei0r API major version
 */
#define FREI0R_MAJOR_VERSION 1

/**
 * The frei0r API minor version
 */
#define FREI0R_MINOR_VERSION 0

//---------------------------------------------------------------------------

/**
 * f0r_init() is called once when the plugin is loaded by the application.
 */
int f0r_init();

/**
 * f0r_deinit is called once when the plugin is unloaded by the application.
 */
void f0r_deinit();

//---------------------------------------------------------------------------


/*@{*/
/**
 * These defines determine whether the plugin is a filter
 * or a source (sometimes also called generator)
 */
#define F0R_PLUGIN_TYPE_FILTER 0
#define F0R_PLUGIN_TYPE_SOURCE 1
/*@}*/

/**
 * List of supported color models - so far only BGRA8888.
 */
#define F0R_COLOR_MODEL_BGRA8888 0

/**
 * The f0r_plugin_info_t structure is filled in by the plugin
 * to tell the application about its name, type, number of parameters,
 * and version. 
 *
 */
typedef struct f0r_plugin_info
{
  const char* name;    /**< The (short) name of the plugin                   */
  const char* author;  /**< The plugin author                                */
  int plugin_type;     /**< The plugin type (source or filter)               */
  int color_model;     /**< The color model used                             */
  int frei0r_version;  /**< The frei0r major version this plugin is built for*/
  int major_version;   /**< The major version of the plugin                  */
  int minor_version;   /**< The minor version of the plugin                  */
  int num_params;      /**< The number of parameters of the plugin           */
  const char* explanation; /**< An optional explanation string (can be 0)    */
} f0r_plugin_info_t;


/**
 * Is called once after init. The plugin has to fill in the values
 * in info.
 * \param info Pointer to an info struct allocated by the application.
 */
void f0r_get_plugin_info(f0r_plugin_info_t* info);

//---------------------------------------------------------------------------

/**
 * Parameter type for boolean values
 */
#define F0R_PARAM_BOOL      0

/**
 * Parameter type for doubles
 */
#define F0R_PARAM_DOUBLE    1

/**
 * Parameter type for color
 */
#define F0R_PARAM_COLOR     2
/**
 * Parameter type for position
 */
#define F0R_PARAM_POSITION  3


/**
 * The boolean type. The allowed range of values is [0, 1].
 * [0, 0.5[ is mapped to false and [0.5, 1] is mapped to true.
 */
typedef double f0r_param_bool;

/**
 * The double type. The allowed range of values is [0, 1].
 */
typedef double f0r_param_double;

/**
 * The color type. All three color components are in the range
 * [0, 1].
 */
typedef struct f0r_param_color
{
  float r;
  float g;
  float b;
} f0r_param_color_t;

/**
 * The position type. Both position coordinates are in the range
 * [0, 1].
 */
typedef struct f0r_param_position
{
  double x;
  double y;
} f0r_param_position_t;


/**
 * Similar to f0r_plugin_info_t, this structure
 * is filled by the plugin for every parameter.
 */
typedef struct f0r_param_info
{
  const char* name;         /**<The (short) name of the param */
  int type;                 /**<The type (see the F0R_PARAM_* defines) */
  const char* explanation;  /**<Optional explanation (can be 0) */
} f0r_param_info_t;

/**
 * f0r_get_param_info is called by the application to query the type of
 * each parameter.
 * \param info is allocated by the application and filled by the plugin
 * \param param_index the index of the parameter to be queried (from 0 to
 *   num_params-1)
 */
void f0r_get_param_info(f0r_param_info_t* info, int param_index);

//---------------------------------------------------------------------------

typedef void* f0r_instance_t;

/**
 * Constructor for effect instances. The plugin returns a pointer to
 * its internal instance structure. The resolution has to be
 * a multiple of 8 in both dimension.
 * \param width The x-resolution of the processed video frames
 * \param height The y-resolution of the processed video frames
 * \returns 0 on failure or a pointer != 0 on success
 */
f0r_instance_t f0r_construct(unsigned int width, unsigned int height);

/**
 * Destroys an effect instance.
 * \param instance The pointer to the plugins internal instance structure.
 */
void f0r_destruct(f0r_instance_t instance);

//---------------------------------------------------------------------------

typedef void* f0r_param_t;

/**
 * This function allows the application to set the parameter values of an
 * effect instance. Validity of the parameter pointer is handled by the
 * application thus the data must be copied.
 * \param instance the effect instance
 * \param param pointer to the parameter value
 * \param param_index index of the parameter
 */
void f0r_set_param_value(f0r_instance_t instance, 
			 f0r_param_t param, int param_index);

/**
 * This function allows the application to query the parameter values of an
 * effect instance.
 * \param instance the effect instance
 * \param param pointer to the parameter value
 * \param param_index index of the parameter
 */
void f0r_get_param_value(f0r_instance_t instance,
			 f0r_param_t param, int param_index);

//---------------------------------------------------------------------------

/**
 * This is where the core effect processing happens. The application calls it
 * after it has set the necessary parameter values.
 * inframe and outframe data has to be aligned to a multiple of eight.
 *
 * \param instance the effect instance
 * \param time the application time in seconds but with subsecond resolution
 *        (e.g. milli-second resolution). The resolution should be at least
 *        the inter-frame period of the application.
 * \param inframe the incoming video frame (can be zero for sources)
 * \param outframe the resulting video frame
 */
void f0r_update(f0r_instance_t instance, 
		double time, const uint32_t* inframe, uint32_t* outframe);

//---------------------------------------------------------------------------

#endif
