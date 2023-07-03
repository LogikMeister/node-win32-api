#include <node_api.h>
#include <cassert>
#include <string>
#include <Windows.h>
#include "./node_functions.hpp"

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;

  napi_value fn_find_window;
  status = napi_create_function(env, nullptr, 0, NodeFindWindow, nullptr, &fn_find_window);
  assert(status == napi_ok);
  status = napi_set_named_property(env, exports, "findWindow", fn_find_window);
  assert(status == napi_ok);

	napi_value fn_set_parent;
	status = napi_create_function(env, nullptr, 0, NodeSetParent, nullptr, &fn_set_parent);
	assert(status == napi_ok);
	status = napi_set_named_property(env, exports, "setParent", fn_set_parent);
	assert(status == napi_ok);

  napi_value fn_enum_child_windows;
  status = napi_create_function(env, nullptr, 0, NodeEnumChildWindows, nullptr, &fn_enum_child_windows);
  assert(status == napi_ok);
  status = napi_set_named_property(env, exports, "enumChildWindows", fn_enum_child_windows);
  assert(status == napi_ok);

  napi_value fn_get_window_text_a;
  status = napi_create_function(env, nullptr, 0, NodeGetWindowTxetA, nullptr, &fn_get_window_text_a);
  assert(status == napi_ok);
  status = napi_set_named_property(env, exports, "getWindowTextA", fn_get_window_text_a);
  assert(status == napi_ok);

  napi_value fn_move_window;
  status = napi_create_function(env, nullptr, 0, NodeMoveWindow, nullptr, &fn_move_window);
  assert(status == napi_ok);
  status = napi_set_named_property(env, exports, "moveWindow", fn_move_window);
  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)