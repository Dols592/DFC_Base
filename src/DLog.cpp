  /*
  */
  
#include "DLog.h"
  
DLog* DLog::mLogPointer = NULL;

void DLog::Log(int32_t Severity, const char *format, ...)
{
  //Expand string
  DString NewString; 
  va_list args;
  va_start(args, format);
  NewString.Format(format, args);
  va_end(args);

  DLog::Log(Severity, NewString);
}

void DLog::Log(int32_t Severity, DString& Msg)
{
  DLog* LogPointer = DLog::GetLogPointer();
  if (LogPointer == NULL)
    return;
  
  LogPointer->AddLog(Severity, Msg);
}

void DLog::AddCallback(CBFuncLogMsg CBFunc)
{
  DLog* LogPointer = DLog::GetLogPointer();
  if (LogPointer == NULL)
    return;

  LogPointer->AddCallbackToList(CBFunc);
}

void DLog::AddCallbackToList(CBFuncLogMsg CBFunc)
{
  CBFuncLogMsg NewCB(CBFunc);
  
  mCBFunctions.push_back(NewCB);
}

DLog* DLog::GetLogPointer()
{
  if (DLog::mLogPointer == NULL)
    DLog::mLogPointer = new DLog;

  return DLog::mLogPointer;
}

void DLog::AddLog(int32_t Severity, DString& Msg)
{
  for (std::vector<CBInfo>::iterator it=mCBFunctions.begin(); it!= mCBFunctions.end(); it++)
  {
    it->Func(Msg.c_str());
  }
}
