#ifndef _NODE_MOVE_WINDOW_H_
#define _NODE_MOVE_WINDOW_H_

#include <node_api.h>
#include <Windows.h>

napi_value NodeMoveWindow(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 6;
  napi_value argv[6];
  status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
  if (status != napi_ok) {
    napi_throw_error(env, nullptr, "Failed to get arguments");
    return nullptr;
  }

  // check parameters
  if (argc < 6) {
    napi_throw_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }
  napi_valuetype valuetype[5];
  for (int i=0; i<6; i++) {
    napi_typeof(env, argv[i], &valuetype[i]);
  }
  if (
    valuetype[0] != napi_bigint ||
    valuetype[1] != napi_number ||
    valuetype[2] != napi_number ||
    valuetype[3] != napi_number ||
    valuetype[4] != napi_number || 
    valuetype[5] != napi_boolean
  ) {
    napi_throw_type_error(env, nullptr, "Wrong arguments");
		return NULL;
  }

  // get arguments
  int64_t hwnd_value;
  bool lossless;
  napi_get_value_bigint_int64(env, argv[0], &hwnd_value, &lossless);
  if (!lossless) {
    napi_throw_error(env, NULL, "BigInt hwnd value out of range");
    return NULL;
  }
  HWND hwnd = reinterpret_cast<HWND>(hwnd_value);
  int32_t x, y, width, height;
  napi_get_value_int32(env, argv[1], &x);
  napi_get_value_int32(env, argv[2], &y);
  napi_get_value_int32(env, argv[3], &width);
  napi_get_value_int32(env, argv[4], &height);
  bool repaint;
  napi_get_value_bool(env, argv[5], &repaint);
  
  // function call
  BOOL result = MoveWindow(hwnd, x, y, width, height, repaint);

  napi_value result_value;
  napi_get_boolean(env, result, &result_value);

  return result_value;
}

#endif