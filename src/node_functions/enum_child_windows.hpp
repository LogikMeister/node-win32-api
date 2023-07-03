#ifndef _ENUM_CHILD_WINDOWS_H_
#define _ENUM_CHILD_WINDOWS_H_

#include <node_api.h>
#include <Windows.h>

typedef struct {
  napi_ref callback_ref;
  napi_env env;
} callback_data_t;

// 定义回调函数
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
  callback_data_t* data = (callback_data_t*)lParam;
  napi_env env = data->env;
  napi_value callback;
  napi_get_reference_value(env, data->callback_ref, &callback);

  napi_value hwnd_value;
  napi_create_bigint_int64(env, (int64_t)hwnd, &hwnd_value);

  napi_value result;
  napi_call_function(env, callback, callback, 1, &hwnd_value, &result);

  bool continueEnum;
  napi_get_value_bool(env, result, &continueEnum);

  return continueEnum;
}

napi_value NodeEnumChildWindows(napi_env env, napi_callback_info info) {
	napi_status status;
	size_t argc = 2;
	napi_value argv[2];
	status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
  if (status != napi_ok) {
    napi_throw_error(env, nullptr, "Failed to parse arguments");
    return nullptr;
  }

  // check arguments
	if (argc < 2) {
		napi_throw_type_error(env, nullptr, "Wrong number of arguments");
		return NULL;
	}
  napi_valuetype argTypes[2];
  for (int i = 0; i < 2; i++) {
    napi_typeof(env, argv[i], &argTypes[i]);
  }
  if (argTypes[0] != napi_bigint || argTypes[1] != napi_function) {
    napi_throw_type_error(env, nullptr, "Invalid argument types");
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

  callback_data_t data;
  data.env = env;
  napi_create_reference(env, argv[1], 1, &(data.callback_ref));

  // function call
  BOOL result = EnumChildWindows(hwnd, EnumChildProc, reinterpret_cast<LPARAM>(&data));
  napi_value result_value;
  napi_get_boolean(env, result, &result_value);

  return result_value;
}

#endif