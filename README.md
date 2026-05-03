# ChanlunX2

## 如何编译

### Visual Studio 2026

通达信插件需要编译成32位，下面以Visual Studio 2019举例，作者用的是Visual Studio 2019社区版。

```cmd
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A Win32 ..
cmake --build . --config Release
```

### Visual Studio 2026

在项目根目录下依次执行以下命令

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## 主图代码

把编译好的DLL放到通达信的T0002\dlls目录，绑定为2号函数，下面的代码做成通达信主图公式。

具体内容见缠论主图-chanlunX2.txt

