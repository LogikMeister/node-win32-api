{
  "targets": [
    {
      "target_name": "win32",
      "sources": ["src/win32.cpp"],
      # "include_dirs": [ "<!(node -p \"require('node-addon-api').include\")" ],
      # "dependencies": [ "<!(node -p \"require('node-addon-api').gyp\")" ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
    }
  ]
}