#ifndef GUARD_minmax_H 
#define GUARD_minmax_H 
#ifdef _MSC_VER 
namespace std
{
  template <class T> inline T max(const T& a, const T& b) 
    { 
      return (a > b) ? a : b;
    } 
  
  template <class T> inline T min(const T& a, const T& b) 
    { 
      return (a < b) ? a : b;
    } 
}
#endif 
#endif 
