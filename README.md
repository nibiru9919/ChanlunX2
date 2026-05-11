# ChanlunX2

通达信缠论分析插件 — 基于通达信 DLL 扩展机制，在主图上绘制笔、线段、中枢。
2026.5.10更新了代码，符合c++26规范。
另外，大部分代码重新更新了。

## 前置条件

- CMake >= 3.20
- c++环境：mingw-w64
- 通达信金融终端64位、通达信期货通64位

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

{CHANLUNX2主图 2026年5月10日 优化版}
{绑定2号DLL函数}
说明:=1;
DRAWTEXT_FIX(说明,0,0,0,'笔：黄色虚线；笔中枢：黄色线段'),COLORYELLOW;
DRAWTEXT_FIX(说明,0,0.03,0,'段：蓝色实线；段中枢：蓝色线段'),COLORFF8000;
DRAWTEXT_FIX(说明,0,0.06,0,'缠论买卖点：一买(深红) 类二买(紫红) 二买(紫色) 三买(粉紫)'),COLORWHITE;
DRAWTEXT_FIX(说明,0,0.09,0,'          一卖(深青) 类二卖(青蓝) 二卖(青色) 三卖(浅青)'),COLORWHITE;

{画笔}
FRAC:=TDXDLL2(2,H,L,0);
DRAWLINE(FRAC=-1,L,FRAC=1,H,0),LINETHICK1,COLORYELLOW;
DRAWLINE(FRAC=1,H,FRAC=-1,L,0),LINETHICK1,COLORYELLOW;

{笔中枢}
BIZG:=TDXDLL2(5,FRAC,H,L);
BIZD:=TDXDLL2(6,FRAC,H,L);
BISE:=TDXDLL2(7,FRAC,H,L);
BIZZ:=(BIZG+BIZD)/2;

{画段}
DUAN:=TDXDLL2(3,FRAC,H,L);
DRAWLINE(DUAN=-1,L,DUAN=1,H,0),LINETHICK1,COLORFF8000;
DRAWLINE(DUAN=1,H,DUAN=-1,L,0),LINETHICK1,COLORFF8000;

{段中枢}
DUANZG:=TDXDLL2(5,DUAN,H,L);
DUANZD:=TDXDLL2(6,DUAN,H,L);
DUANSE:=TDXDLL2(7,DUAN,H,L);
DUANZZ:=(DUANZG+DUANZD)/2;

{笔中枢画线}
IF(BIZG,BIZG,DRAWNULL),COLORYELLOW;
IF(BIZD,BIZD,DRAWNULL),COLORYELLOW;
STICKLINE(BISE,BIZD,BIZG,0,0),COLORYELLOW;
DRAWLINE(BISE,BIZZ,BISE,BIZZ,0),DOTLINE,COLORYELLOW;

{段中枢画线}
IF(DUANZG,DUANZG,DRAWNULL),COLORFF8000;
IF(DUANZD,DUANZD,DRAWNULL),COLORFF8000;
STICKLINE(DUANSE,DUANZD,DUANZG,0,0),COLORFF8000;
DRAWLINE(DUANSE,DUANZZ,DUANSE,DUANZZ,0),DOTLINE,COLORFF8000;

{均线}
MA26:=EMA(C,26);
MA13:=EMA(C,13);

{基础变量}
VAR2:=FRAC;
A1:=BARSLAST(VAR2<>0);
A2:=REF(VAR2,A1);
AA1:=REF(A1+1,1);
AA2:=-REF(A2,1);
方向:=AA2;
AA3:=AA1+REF(AA1+1,AA1);
AA4:=AA3+REF(AA1+1,AA3);
H1:=BARSLAST(VAR2=1);
HH1:=REF(H1+1,1);
L1:=BARSLAST(VAR2=-1);
LL1:=REF(L1+1,1);

GG:=REF(H,H1);
GG1:=REF(H,HH1);
GG2:=REF(GG1,HH1);
GG3:=REF(GG2,HH1);
GG4:=REF(GG3,HH1);
GG5:=REF(GG4,HH1);
DD:=REF(L,L1);
DD1:=REF(L,LL1);
DD2:=REF(DD1,LL1);
DD3:=REF(DD2,LL1);
DD4:=REF(DD3,LL1);
DD5:=REF(DD4,LL1);

{========== 买点判断 ==========}

{一买：趋势背驰或盘整背驰后的第一类买点}
买1T1:=方向=1 AND L<MA13 AND LL1<=5;                          {向上笔开始，5周期内}
买1W5:=DD1<GG1 AND DD1<DD2 AND DD1<DD3 AND GG1<GG2 AND GG1<GG3;  {趋势背驰条件：新低+新高降低}
买1JA:=GG1<DD3;                                                {盘整背驰：最后一个中枢高点低于前中枢低点}
买1JB:=GG1>DD3;                                                {趋势背驰：最后一个中枢高点高于前中枢低点}
买1A:=买1T1 AND 买1W5 AND 买1JA;                               {盘整背驰一买}
买1B:=买1T1 AND 买1W5 AND 买1JB;                               {趋势背驰一买}
一买:=买1A OR 买1B;

{类二买：在一买之后，回调不创一买新低的买点}
L2MT1:=方向=1 AND C<MA13 AND LL1<=8;                           {向上笔开始，8周期内}
L2MT2:=DD1<GG1 AND DD3<DD2 AND DD3<DD1 AND DD3<DD4;            {前低是序列中最低}
类二买:=L2MT1 AND L2MT2 AND NOT(一买);                          {排除一买信号}

{二买：回调不破前低，形成新的向上笔}
买2T1:=方向=1 AND L<MA26 AND LL1<=8;                          {向上笔开始，8周期内，靠近MA26}
买2TJ:=DD1<GG1 AND DD1>DD2;                                    {不跌破前低}
二买:=买2T1 AND 买2TJ AND NOT(一买) AND NOT(类二买);            {排除一买和类二买}

{三买：向上离开中枢后，回抽不回到中枢区间}
三买:=方向=1 AND L<MA13 AND LL1<=5 AND DD1>MIN(GG2,GG3);       {回抽低点高于前两中枢高点的较小值}

{========== 卖点判断 ==========}

{一卖：趋势背驰或盘整背驰后的第一类卖点}
卖1T1:=方向=-1 AND H>MA13 AND HH1<=5;                          {向下笔开始，5周期内}
卖1W5:=GG1>DD1 AND GG1>GG2 AND GG1>GG3 AND DD1>DD2 AND DD1>DD3;  {趋势背驰条件：新高+新低抬高}
卖1JA:=GG1>DD3;                                                {趋势背驰：最后一个中枢低点低于前中枢高点}
卖1JB:=GG1<DD3;                                                {盘整背驰：最后一个中枢高点低于前中枢低点}
卖1A:=卖1T1 AND 卖1W5 AND 卖1JA;                               {趋势背驰一卖}
卖1B:=卖1T1 AND 卖1W5 AND 卖1JB;                               {盘整背驰一卖}
一卖:=卖1A OR 卖1B;

{类二卖：在一卖之后，反弹不创一卖新高的卖点}
L2ST1:=方向=-1 AND H>MA13 AND HH1<=8;                           {向下笔开始，8周期内}
L2ST2:=GG1>DD1 AND GG3>GG2 AND GG3>GG1;                        {前高是序列中最高}
类二卖:=L2ST1 AND L2ST2 AND NOT(一卖);                          {排除一卖信号}

{二卖：反弹不破前高，形成新的向下笔}
卖2T1:=方向=-1 AND H>MA13 AND HH1<=8;                          {向下笔开始，8周期内}
卖2TJ:=GG1>DD1 AND GG1<GG2;                                    {不突破前高}
二卖:=卖2T1 AND 卖2TJ AND NOT(一卖) AND NOT(类二卖);            {排除一卖和类二卖}

{三卖：向下离开中枢后，回抽不回到中枢区间}
三卖:=方向=-1 AND H>MA13 AND HH1<=5 AND GG1<MAX(DD2,DD3);       {回抽高点低于前两中枢低点的较大值}

{========== 买卖点显示 ==========}

{买点显示（红色系）}
DRAWTEXT(一买 AND FILTER(一买,8),REF(L,1),'●一买'),COLORRED;        {深红色一买}
DRAWTEXT(类二买 AND FILTER(类二买,8),REF(L,1),'○类二买'),COLORMAGENTA; {紫红色类二买}
DRAWTEXT(二买 AND FILTER(二买,8),REF(L,1),'△二买'),COLORFF00FF;     {紫色二买}
DRAWTEXT(三买 AND FILTER(三买,8),REF(L,1),'☆三买'),COLORFF66FF;     {粉紫色三买}

{卖点显示（青色系）}
DRAWTEXT(一卖 AND FILTER(一卖,8),REF(H,1),'●一卖'),COLORFF0080;      {深青色一卖}
DRAWTEXT(类二卖 AND FILTER(类二卖,8),REF(H,1),'○类二卖'),COLORFF00CC; {青蓝色类二卖}
DRAWTEXT(二卖 AND FILTER(二卖,8),REF(H,1),'△二卖'),COLORCYAN;        {青色二卖}
DRAWTEXT(三卖 AND FILTER(三卖,8),REF(H,1),'☆三卖'),COLOR80FFFF;      {浅青色三卖}

{========== 辅助标记 ==========}

{标注最近笔的高低点}
{DRAWTEXT(FRAC=1,H,'顶'),COLORYELLOW;}
{DRAWTEXT(FRAC=-1,L,'底'),COLORYELLOW;}

{标注线段端点}
{DRAWTEXT(DUAN=1,H,'┬'),COLORFF8000;}
{DRAWTEXT(DUAN=-1,L,'┴'),COLORFF8000;}

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
