//
// Created by root on 1/8/17.
//

#include <android/log.h>
#include <sys/time.h>
#include <string>
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

void BeginTrace(std::string func_name){
    start_time = getCurrentTimeMillis();
}

void EndTrace(std::string func_name){
    time_consuming = getCurrentTimeMillis() - start_time;
//    std::string str = patch::to_string(time_consuming);
    int length = sprintf(buffer, log_format, func_name.c_str(), time_consuming);
    std::string log_info(buffer, length);
    LOGD("%s", log_info.c_str());
}


