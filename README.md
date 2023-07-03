# node-win32-api

功能：Windows.h部分函数的 Node 扩展

为 Node.js 提供对 Windows.h 库中部分函数的封装，在 Node.js 中调用这些 Windows API。

## 安装

使用 npm 进行安装：

```shell
npm install
npm run build
```

## 使用示例

```javascript
const win32api = require('node-win32-api');

// 调用 Windows API
const hWnd = win32api.findWindow('WindowName');
console.log(`窗口句柄：${hWnd}`);

// 调用其他 Windows API...
// ...

```
