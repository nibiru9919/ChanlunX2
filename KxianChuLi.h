#ifndef __KXIANCHULI_H__
#define __KXIANCHULI_H__

#include <vector>

// C++23/C++26 兼容修改：移除 using namespace std;，改为显式使用 std:: 前缀
// 原代码：using namespace std;

#pragma pack(push, 1)

// 原始K线
struct KxianRaw
{
    float gao;
    float di;
};

// 表示合并后的K线
struct Kxian
{
    float gao;     // K线高
    float di;      // K线低
    int fangXiang; // K线方向
    int kaiShi;    // 开始K线坐标
    int jieShu;    // 结束K线坐标
    int zhongJian;
};

class KxianChuLi
{
public:
    std::vector<KxianRaw> kxianRawList; // 元素K线表
    std::vector<Kxian> kxianList;       // 包含处理后的K线表
    void add(float gao, float di); // 添加一根K线高和低进行处理
};

#pragma pack(pop)

#endif
