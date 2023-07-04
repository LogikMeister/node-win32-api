#ifndef _NODE_FIND_WINDOW_H_
#define _NODE_FIND_WINDOW_H_

#include <node_api.h>
#include <string>
#include <Windows.h>
#include "../utils.hpp"

inline napi_value NodeFindWindow(napi_env env, napi_callback_info info) {
	napi_status status;
	size_t argc = 1;
	napi_value argv[1];
	status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
	
	if (status != napi_ok) {
		napi_throw_error(env, nullptr, "Failed to parse arguments");
		return nullptr;
	}

	// check arguments
	if (argc < 1) {
		napi_throw_type_error(env, nullptr, "Wrong number of arguments");
		return NULL;
	}
	napi_valuetype valuetype0;
	napi_typeof(env, argv[0], &valuetype0);
	if (valuetype0 != napi_string) {
		napi_throw_type_error(env, nullptr, "Wrong arguments");
		return NULL;
	}

	// get arguments
	char windowName[1024];
  size_t result;
  napi_get_value_string_utf8(env, argv[0], windowName, sizeof(windowName), &result);
  std::wstring wideWindowName = Utf8ToWide(windowName);

	// function call
	HWND hwnd = FindWindowW(NULL, wideWindowName.c_str());
	napi_value ret;
  napi_create_bigint_int64(env, reinterpret_cast<int64_t>(hwnd), &ret);
	return ret;
}

#endif