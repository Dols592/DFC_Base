//
#include "DString.h"

DString::DString()
 : String()
{
}

DString::DString(const String& SrcStr)
 : String()
{
  *this = SrcStr;             // = operator will copy string, not the pointer.
}

DString::DString(const DString& SrcStr)
 : String()
{
  *this = SrcStr;             // = operator will copy string, not the pointer.
}

DString& DString::operator =(const String& b)
{
  if(this == &b)
    return *this;

  if(b.c_str())
    copy(b.c_str(), b.length());
  else
    invalidate();

  return *this;
}

DString DString::FormatNew(const char *format, ...)
{
  DString NewString;
  
  va_list args;
  va_start(args, format);
  NewString.Format(format, args);
  va_end(args);
  
  return NewString;
}

size_t DString::Format(const char *format, ...) 
{
  va_list args;
  va_start(args, format);
  size_t NewSize = Format(format, args);
  va_end(args);
 
  return NewSize;
}

size_t DString::Format(const char *format, va_list args) 
{
  size_t NewLen = vsnprintf(buffer, capacity, format, args);
 
  if (NewLen > capacity) 
  {
    changeBuffer(NewLen);
    NewLen = vsnprintf(buffer, capacity, format, args);
  }
  
  len = NewLen;
  return len;
}

size_t DString::FormatCopy(const char *format, ...) 
{
  DString CopyString;
  va_list args;
  va_start(args, format);
  size_t NewSize = CopyString.Format(format, args);
  va_end(args);

  *this = CopyString;           // = operator will copy string, not the pointer.
  return len;
}

size_t DString::AppendFormat(const char *format, ...) 
{
  va_list args;
  va_start(args, format);
  size_t NewLen = vsnprintf(buffer+len, capacity-len, format, args);
  va_end(args);

  if (NewLen > capacity-len) 
  {
    changeBuffer(len+NewLen);
    va_start(args, format);
    NewLen = vsnprintf(buffer+len, capacity-len, format, args);
    va_end(args);
  }

  len = len+NewLen;
  return len;
}

size_t DString::AppendFront(const String& AddString) 
{
  int32_t AddLen = AddString.length();
  int32_t NewLen = len + AddLen;
  if (NewLen > capacity) 
  {
    changeBuffer(NewLen);
  }
  memmove(buffer+AddLen, buffer, len+1);        // +1 is for null termination
  memcpy(buffer, AddString.c_str(), AddLen);    // Without null termination

  len = NewLen;
  return len;
}

/*
Almost the same as String::substring
- Instead of "end" in has a Count (length) of the new string
- First (start) can be negative, indicating First is relative to the right.
*/
String DString::Mid(int32_t First, int32_t Count/*=-1*/) const
{
  if (First < 0)                    // First is counted from right
  {
    First = len + First;            // Remember, First is negative.
    if (First < 0)
      First = 0;
  }
  if (Count < 0)
    Count = len;

  int32_t End = First + Count;
  return substring(First, End);
}

/*
  more safe
*/
const char* DString::c_str()
{
  reserve(1);                         //make sure it's valid.
  
  return String::c_str();
}
