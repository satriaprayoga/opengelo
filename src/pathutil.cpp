/*
 * pathutil.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: satriaprayoga
 */




#include "pathutil.h"

std::string GetProcPath(){

	char path[PATH_MAX+1];
	int size;
	size=readlink("/proc/self/exe",path,PATH_MAX);
	if(size<0){
		return "./";
	}else{
		path[size]='\0';
		return std::string(dirname(path))+"/";
	}

}
