declare namespace win32 {
  function findWindow(windowName: string): BigInt;
  function setParent(hwndChild: BigInt, hwndParent: BigInt): void;
  function enumChildWindows(hwnd: BigInt, callback: (hwnd: BigInt) => boolean): boolean;
  function getWindowTextA(hwnd: BigInt): string | undefined;
  function moveWindow(hwnd: BigInt, x: number, y: number, width: number, height: number, repaint: boolean): boolean;
}

export default win32;