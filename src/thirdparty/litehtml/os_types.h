﻿#ifndef LH_OS_TYPES_H
#define LH_OS_TYPES_H

namespace litehtml
{
#if defined( WIN32 ) || defined( _WIN32 ) || defined( WINCE )

	typedef std::string			tstring;
	typedef char				tchar_t;
	typedef std::stringstream	tstringstream;

	#define _t(quote)			quote

	#define t_strlen			strlen
	#define t_strcmp			strcmp
	#define t_strncmp			strncmp
	#define t_strcasecmp		_stricmp
	#define t_strncasecmp		_strnicmp
	#define t_strtol			strtol
	#define t_atoi				atoi
	#define t_strtod			strtod
	#define t_itoa(value, buffer, size, radix)	_itoa_s(value, buffer, size, radix)
	#define t_strstr			strstr
	#define t_tolower			tolower
	#define t_isdigit			isdigit
	#define t_to_string(val)	std::to_string(val)



	#ifdef _WIN64
		typedef unsigned __int64 uint_ptr;
	#else
		typedef unsigned int	uint_ptr;
	#endif

#else
	#define LITEHTML_UTF8

	typedef std::string			tstring;
	typedef char				tchar_t;
	typedef std::uintptr_t			uint_ptr;
	typedef std::stringstream	tstringstream;

	#define _t(quote)			quote

	#define t_strlen			strlen
	#define t_strcmp			strcmp
	#define t_strncmp			strncmp

	#define t_strcasecmp		strcasecmp
	#define t_strncasecmp		strncasecmp
	#define t_itoa(value, buffer, size, radix)	snprintf(buffer, size, "%d", value)

	#define t_strtol			strtol
	#define t_atoi				atoi
	#define t_strtod			strtod
	#define t_strstr			strstr
	#define t_tolower			tolower
	#define t_isdigit			isdigit
	#define t_to_string(val)	std::to_string(val)

#endif
}

#endif  // LH_OS_TYPES_H