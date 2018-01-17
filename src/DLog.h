#ifndef DLog_h
#define DLog_h

#include <c_types.h>
#include <vector>
#include <functional>
#include <DString.h>

enum LogSeverity
{
  LOGSEVERITY_TRACE = 0,
  LOGSEVERITY_INFO_LOW,
  LOGSEVERITY_INFO_MED,
  LOGSEVERITY_INFO_HIGH,
  LOGSEVERITY_USER,
  LOGSEVERITY_ERROR,
  LOGSEVERITY_FATAL,
  LOGSEVERITY_COUNT  
};

//typedef void CBFuncLogMsg(const char*);

typedef std::function<void(const char*)> CBFuncLogMsg;

struct CBInfo
{
    CBFuncLogMsg Func;
    int32_t MinLogSeverity;
    
    CBInfo(CBFuncLogMsg CBFunc)
    : Func(CBFunc)
    {
      MinLogSeverity = LOGSEVERITY_INFO_HIGH;
    }
};


class DLog
{
public: //Interface
  static void Log(int32_t Severity, const char *format, ...);
  static void Log(int32_t Severity, DString& Msg);

  static void AddCallback(CBFuncLogMsg CBFunc);
  
protected: //Help Functions
  static DLog* GetLogPointer();
  void AddLog(int32_t Severity, DString& Msg);
  void AddCallbackToList(CBFuncLogMsg CBFunc);
  
protected: //Variables
  static DLog* mLogPointer;
  std::vector<CBInfo> mCBFunctions;
};

#endif //DLog_h

