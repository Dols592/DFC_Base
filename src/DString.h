/*
  The things i miss on the build-in "String" class
*/
#ifndef DPrint_h
#define DPrint_h

#include <WString.h>
 
class DString: public String
{
public: //Constructors
  DString();                                              // Implement default constructor
  DString(const String& SrcStr);                          // Implement copy constructor
  DString(const DString& SrcStr);                         // Implement copy constructor
  using String::String;                                   // Using the constructor of String. C++11 specific

public: //Operators
  DString& operator =(const String& b);                   // Assignment operator from String
  
public: //String overrides
  const char* c_str();

public:
  virtual size_t Format(const char *format, ...);         // (= printf) Format string
  virtual size_t Format(const char *format, va_list args);         // (= printf) Format string
  virtual size_t FormatCopy(const char *format, ...);

  virtual size_t AppendFormat(const char *format, ...);   // Append formated string
  virtual String Mid(int32_t Start, int32_t Count=-1);         // Very close to String::substring
  virtual size_t AppendFront(const String& AddString);
};  

#endif //#ifndef DPrint_h
