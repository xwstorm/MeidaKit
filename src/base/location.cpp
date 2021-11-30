//
//  Location.cpp
//  MediaKit
//
//  Created by xiewei on 2019/6/17.
//

#include "location.h"

MK_BEGIN
MKLocation::MKLocation(const char* function_name, const char* file_and_line)
: mFunctionName(function_name)
, mFileAndLine(file_and_line)
{
    
}

MKLocation::MKLocation() {
    
}
MK_END
