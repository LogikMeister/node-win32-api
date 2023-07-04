#ifndef _NODE_GET_WINDOW_TXEX_A_H_
#define _NODE_GET_WINDOW_TXEX_A_H_

#include <node_api.h>
#include <Windows.h>

inline napi_value NodeGetWindowTxetA(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
	if (status != napi_ok) {
		napi_throw_error(env, nullptr, "Failed to parse arguments");
		return NULL;
	}

  // check parameters
  if (argc < 1) {
    napi_throw_error(env, nullptr, "Wrong number of arguments");
    return NULL;
  }
  napi_valuetype valuetype0;
	napi_typeof(env, argv[0], &valuetype0);
  if (valuetype0 != napi_bigint) {
    napi_throw_type_error(env, nullptr, "Wrong arguments");
		return NULL;
  }

  // get parameters
  int64_t hwnd_value;
  bool lossless;
  napi_get_value_bigint_int64(env, argv[0], &hwnd_value, &lossless);
  if (!lossless) {
    napi_throw_error(env, NULL, "BigInt hwnd value out of range");
    return NULL;
  }
  HWND hwnd = reinterpret_cast<HWND>(hwnd_value);

  // function call
  char buffer[256];
  int result = GetWindowTextA(hwnd, buffer, sizeof(buffer));

  if (result == 0) {
    return NULL;
  }
  napi_value result_value;
  napi_create_string_utf8(env, buffer, NAPI_AUTO_LENGTH, &result_value);
  return result_value;
}

#endif _NODE_GET_WINDOW_TXEX_A_H_