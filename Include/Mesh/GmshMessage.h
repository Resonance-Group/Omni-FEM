// Gmsh - Copyright (C) 1997-2017 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@onelab.info>.

#ifndef _GMSH_MESSAGE_H_
#define _GMSH_MESSAGE_H_

#include <map>
#include <vector>
#include <string>
#include <stdarg.h>
#include <stdio.h>

#include <common/OmniFEMMessage.h>

// a class to manage messages
class Msg {
 public:
	static void Fatal(const char *fmt, ...)
	{
		char str[5000];
		va_list args;
		va_start(args, fmt);
		vsnprintf(str, sizeof(str), fmt, args);
		va_end(args);
		
		OmniFEMMsg::instance()->wxMsgFatal(wxString(str));
	}
	
	static void Error(const char *fmt, ...)
	{
		char str[5000];
		va_list args;
		va_start(args, fmt);
		vsnprintf(str, sizeof(str), fmt, args);
		va_end(args);
	  
		OmniFEMMsg::instance()->wxMsgError(wxString(str));
	}
	
	static void Warning(const char *fmt, ...)
	{
		char str[5000];
		va_list args;
		va_start(args, fmt);
		vsnprintf(str, sizeof(str), fmt, args);
		va_end(args);
		
		OmniFEMMsg::instance()->wxMsgWarning(wxString(str));
	}
	
	static void Info(const char *fmt, ...)
	{
		char str[5000];
		va_list args;
		va_start(args, fmt);
		vsnprintf(str, sizeof(str), fmt, args);
		va_end(args);
		
		OmniFEMMsg::instance()->wxMsgInfo(wxString(str));
	}
	
	static void Debug(const char *fmt, ...)
	{
		char str[5000];
		va_list args;
		va_start(args, fmt);
		vsnprintf(str, sizeof(str), fmt, args);
		va_end(args);
		
		OmniFEMMsg::instance()->wxMsgStatus(wxString(str));
	}
};

#endif
