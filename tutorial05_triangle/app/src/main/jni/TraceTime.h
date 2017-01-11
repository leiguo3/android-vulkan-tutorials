//
// Created by root on 1/8/17.
//

#ifndef TUTORIAL04_FIRST_WINDOW_VULKANFUNCNAME_H
#define TUTORIAL04_FIRST_WINDOW_VULKANFUNCNAME_H

#include <string>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define BeginTrace(func_name) \
      RecordClock(func_name);
#define EndTrace(func_name) \
      __android_log_print(ANDROID_LOG_DEBUG, "TraceTime",               \
                        "Time consuming: %ld, Function Name: %s, File[%s], line[%d]", getConsumeTime(), func_name, \
                        __FILENAME__, __LINE__);

long int getCurrentTimeMillis();

void RecordCurrentTime(std::string func_name);
void EndTraceA(std::string func_name);
long int getConsumeTime();

void RecordClock(std::string func_name);

const char* getFunctionName(std::string func);

#endif //TUTORIAL04_FIRST_WINDOW_VULKANFUNCNAME_H


