#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>
#include <vector>
#include <Windows.h>

inline std::wstring Utf8ToWide(const std::string& utf8Str) {
  int length = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
  std::vector<wchar_t> buffer(length);
  MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, buffer.data(), length);

  return std::wstring(buffer.data());
}

#endif