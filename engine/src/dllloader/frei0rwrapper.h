
#ifndef INCLUDED_FREI0RWRAPPER_H
#define INCLUDED_FREI0RWRAPPER_H

#include <string>
#include <vector>

class CModuleFunctionTable;

extern "C"
{
#include "frei0r.h"
}

  typedef int  (*f0r_init_t)();
  typedef void (*f0r_deinit_t)();
  typedef void (*f0r_get_plugin_info_t)(f0r_plugin_info_t* info);
  typedef void (*f0r_get_param_info_t)(f0r_param_info_t* info,
				       int param_index);
  typedef f0r_instance_t (*f0r_construct_t)(int width, int height);
  typedef void (*f0r_destruct_t)(f0r_instance_t instance);

  typedef void (*f0r_set_param_value_t)(f0r_instance_t instance, 
				      f0r_param_t param, int param_index);

  typedef void (*f0r_get_param_value_t)(f0r_instance_t instance,
				      f0r_param_t param, int param_index);

  typedef void (*f0r_update_t)(f0r_instance_t isntance, double time,
			       const uint32_t* inframe, uint32_t* outframe);

  struct frei0r_funs_t
  {
    f0r_init_t            init;
    f0r_deinit_t          deinit;
    f0r_get_plugin_info_t get_plugin_info;
    f0r_get_param_info_t  get_param_info;
    f0r_construct_t       construct;
    f0r_destruct_t        destruct;
    f0r_set_param_value_t set_param_value;
    f0r_get_param_value_t  get_param_value;
    f0r_update_t          update;
  };

void create_f0r_wrapper(CModuleFunctionTable& fTable);

std::string frei0r_create_spec(const f0r_plugin_info_t&);

std::string
frei0r_create_in_param_spec(const f0r_plugin_info_t& f0r_info,
                            frei0r_funs_t* frei0r, int input,
                            std::vector<f0r_param_info_t>& param_infos);

std::string frei0r_create_out_spec();


std::vector<char>
frei0r_create_info(const f0r_plugin_info_t& f0r_info,
                   const std::vector<f0r_param_info_t>& param_infos);

void frei0r_check_plugin_info(const f0r_plugin_info_t& f0r_info);

int frei0r_num_inputs(const f0r_plugin_info& f0r_info);

#endif

