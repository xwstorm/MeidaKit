//
//  location.h
//  MediaKit
//
//  Created by xiewei on 2019/6/17.
//
#pragma once

#include "base/mk_base.h"
MK_BEGIN
#ifndef RTC_BASE_STRINGIZE_MACROS_H_
#define RTC_BASE_STRINGIZE_MACROS_H_

#define STRINGIZE_NO_EXPANSION(x) #x

#define STRINGIZE(x) STRINGIZE_NO_EXPANSION(x)

#endif  // RTC_BASE_STRINGIZE_MACROS_H_


class MKLocation {
public:
    MKLocation();
    MKLocation(const char* function_name, const char* file_and_line);
    const char* functionName() const {return mFunctionName;}
    const char* fileAndLine() const {return mFileAndLine;}
private:
    const char* mFunctionName = nullptr;
    const char* mFileAndLine = nullptr;
};

#define CALL_FROM_HERE CALL_FROM_HERE_WITH_FUNCTION(__FUNCTION__)
#define CALL_FROM_HERE_WITH_FUNCTION(function_name) \
::mk::MKLocation(function_name, __FILE__ ":" STRINGIZE(__LINE__))

MK_END
