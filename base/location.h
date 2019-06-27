//
//  location.h
//  MediaKit
//
//  Created by xiewei on 2019/6/17.
//

#ifndef Location_h
#define Location_h

#include <stdio.h>
#include "av_base.h"

#define CALL_FROM_HERE CALL_FROM_HERE_WITH_FUNCTION(__FUNCTION__)
#define CALL_FROM_HERE_WITH_CUNTION(function_name) \
Location(function_name, __FILE__ ":" STRINGIZE(__LINE__))

class Location {
public:
    Location(const char* function_name, const char* file_and_line);
    const char* functionName() const {return mFunctionName;}
    const char* fileAndLine() const {return mFileAndLine;}
private:
    const char* mFunctionName;
    const char* mFileAndLine;
};

#endif /* Location_h */
