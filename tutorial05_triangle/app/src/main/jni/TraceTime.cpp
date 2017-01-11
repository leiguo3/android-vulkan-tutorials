//
// Created by root on 1/8/17.
//

#include <android/log.h>
#include <sys/time.h>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

// Android log function wrappers
static const char* kTAG = "TraceTime";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGD(...) \
  ((void)__android_log_print(ANDROID_LOG_DEBUG, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

// Trace time function wrappers
// Trace processor time
clock_t start;
// Trace wall clock time
long int start_time;
long int time_consuming;

char buffer[100];
const char * log_format = "Call function: %s, time consuming: %d";

long int getCurrentTimeMillis(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return ms;
}

void RecordCurrentTime(std::string func_name){
    start_time = getCurrentTimeMillis();
}

void RecordClock(std::string func_name){
    start = clock();
}

// consume time in milliseconds
long int getConsumeTime(){
//    return getCurrentTimeMillis() - start_time;
    clock_t end = clock();
    return (end - start) * 1000 / CLOCKS_PER_SEC;
}

void EndTraceA(std::string func_name){
    time_consuming = getCurrentTimeMillis() - start_time;
//    std::string str = patch::to_string(time_consuming);
    int length = sprintf(buffer, log_format, func_name.c_str(), time_consuming);
    std::string log_info(buffer, length);
    LOGD("%s", log_info.c_str());
}

const char* getFunctionName(std::string func){
    std::size_t pos = func.find("(");
    return func.substr(0, pos).c_str();
}


