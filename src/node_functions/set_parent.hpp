#ifndef _NODE_SET_PARENT_H_
#define _NODE_SET_PARENT_H_

#include <node_api.h>
#include <Windows.h>

inline napi_value NodeSetParent(napi_env env, napi_callback_info info) {
	napi_status status;
	size_t argc = 2;
	napi_value argv[2];
	status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

	// check arguments
	if (argc < 2) {
		napi_throw_type_error(env, nullptr, "Wrong number of arguments");
		return NULL;
	}
	napi_valuetype valuetype0, valuetype1;
	napi_typeof(env, argv[0], &valuetype0);
	napi_typeof(env, argv[1], &valuetype1);
	if (valuetype0 != napi_bigint || valuetype1 != napi_bigint) {
		napi_throw_type_error(env, nullptr, "Wrong arguments");
		return NULL;
	}

	// get arguments
	int64_t hwnd_child_value, hwnd_parent_value;
	bool lossless;
	napi_get_value_bigint_int64(env, argv[0], &hwnd_child_value, &lossless);
	if (!lossless) {
		napi_throw_error(env, NULL, "BigInt value out of range");
		return NULL;
	}
	napi_get_value_bigint_int64(env, argv[1], &hwnd_parent_value, &lossless);
	if (!lossless) {
		napi_throw_error(env, NULL, "BigInt value out of range");
		return NULL;
	}
	HWND hwnd_child = reinterpret_cast<HWND>(hwnd_child_value);
	HWND hwnd_parent = reinterpret_cast<HWND>(hwnd_parent_value);

	// function call
	SetParent(hwnd_child, hwnd_parent);
	return NULL;
}

#endif