/*
 * Created: 29.5.2016 13:06:23
 *  Author: Kubas
 *
 * This file is updated by python script at the beginning of every build.
 * DO NOT MODIFY IT MANUALLY!
 */ 

#if !defined(BUILD_INFO_HPP_)

#include "build_info_printer.hpp"

#else

/***** VALUES *****/
const BUILD_INFO::build_number_type BUILD_INFO::pg_build_number			   PROGMEM = 285;
const BUILD_INFO::build_time_type   BUILD_INFO::pg_build_time			   PROGMEM = 1538775303;
const char                          BUILD_INFO::build_time_str			[] PROGMEM = "05.10.2018 23:35:03";
const char                          BUILD_INFO::build_config			[] PROGMEM = "Release";
const char                          BUILD_INFO::build_author			[] PROGMEM = "Admin";


#endif