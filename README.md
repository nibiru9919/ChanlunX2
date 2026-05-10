# ChanlunX

通达信缠论分析插件 — 基于通达信 DLL 扩展机制，在主图上绘制笔、线段、中枢。

## 前置条件

- CMake >= 3.20
- MSVC（Visual Studio 2019+，需支持 C++17）
- 通达信金融终端

## 编译

```cmd
mkdir build && cd build
cmake -A <ARCH> ..
cmake --build . --config Release
```

`<ARCH>` 按通达信位数选择：

| 通达信版本 | `<ARCH>` |
|-----------|----------|
| 32 位 | `Win32` |
| 64 位 | `x64` |

> 编译产物为 `ChanlunX.dll`，需与通达信位数匹配。

## 安装

1. 将 `ChanlunX.dll` 复制到通达信安装目录的 `T0002\dlls\`
2. 在通达信中绑定该 DLL 为 **2 号插件函数**

## DLL 函数一览

| 编号 | 功能 | 调用签名 |
|------|------|----------|
| 1 | 简笔顶底端点 | `(1, H, L, 0)` |
| 2 | 标准笔顶底端点 | `(2, H, L, 0)` |
| 3 | 线段端点（标准画法） | `(3, FRAC, H, L)` |
| 4 | 线段端点（1+1 终结画法） | `(4, FRAC, H, L)` |
| 5 | 中枢高点 | `(5, FRAC, H, L)` |
| 6 | 中枢低点 | `(6, FRAC, H, L)` |
| 7 | 中枢起止信号（1=起点, 2=终点） | `(7, FRAC, H, L)` |
| 8 | 中枢方向 | `(8, FRAC, H, L)` |
| 9 | 同方向第 N 个中枢 | `(9, FRAC, H, L)` |

## 主图公式

新建通达信主图公式，粘贴以下代码：

```text
FRAC:=TDXDLL2(2,H,L,0);{标准笔}
NOTEXT画上升笔2:DRAWLINE(FRAC=-1,L,FRAC=+1,H,0), DOTLINE,COLORYELLOW;
NOTEXT画下降笔2:DRAWLINE(FRAC=+1,H,FRAC=-1,L,0), DOTLINE, COLORYELLOW;

BIZG:=TDXDLL2(5,FRAC,H,L);{输出BI中枢高}
BIZD:=TDXDLL2(6,FRAC,H,L);{输出BI中枢低}
BISE:=TDXDLL2(7,FRAC,H,L);{输出BI中枢开始和结束}

NOTEXT_BIZG:IF(BIZG,BIZG,DRAWNULL),COLORYELLOW;{画BI中枢高}
NOTEXT_BIZD:IF(BIZD,BIZD,DRAWNULL),COLORYELLOW;{画BI中枢低}
NOTEXT_BISE:STICKLINE(BISE,BIZD,BIZG,0,0),COLORYELLOW;{画BI中枢起始结束};

DUAN1:=TDXDLL2(3,FRAC,H,L);{计算段的端点,3改成4是1+1终结画法}
NOTEXT画上升段1:DRAWLINE(DUAN1=-1,L,DUAN1=+1,H,0), COLORFF8000;
NOTEXT画下降段1:DRAWLINE(DUAN1=+1,H,DUAN1=-1,L,0), COLORFF8000;

DUANZG1:=TDXDLL2(5,DUAN1,H,L);{输出段中枢高}
DUANZD1:=TDXDLL2(6,DUAN1,H,L);{输出段中枢低}
DUANSE1:=TDXDLL2(7,DUAN1,H,L);{输出段中枢开始和结束}

NOTEXT_DDUANZG1:IF(DUANZG1,DUANZG1,DRAWNULL),COLORFF8000;{画段中枢高}
NOTEXT_DDUANZD1:IF(DUANZD1,DUANZD1,DRAWNULL),COLORFF8000;{画段中枢低}
NOTEXT_DDUANSE1:STICKLINE(DUANSE1,DUANZD1,DUANZG1,0,0),COLORFF8000;{画段中枢起始结束};
```

## 社区

如果你希望获得更快的上手体验，可以参考安装指南或加入社区交流。

### 安装指南

- [番茄缠论插件 FqChan04 TDX 安装指南](https://mp.weixin.qq.com/s/v3uchXfQLACdeEoV6CN65Q)

### 联系方式

- WeChat: kldcty
- QQ: 1106628276
- 微信公众号: kldctymp
- 缠论X星球: https://t.zsxq.com/0aDUuhQC5
- 纷传圈子：http://s.a0.top/uHvyCEy/4KHZ

### 社区参与指南

- [参与订阅](https://mp.weixin.qq.com/s/xKBIlmBp9iyYg7wpLc5bPw)
- [充电助力](http://s.a0c.top/lJ1c8WZ/4KHZ)

## License

[MIT](LICENSE)
