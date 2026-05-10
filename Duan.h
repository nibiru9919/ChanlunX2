#ifndef __DUAN_H__
#define __DUAN_H__

#include <vector>

// C++23/C++26 兼容修改：移除 using namespace std;，改为显式使用 std:: 前缀
// 原代码：无 using namespace std;（原文件未使用）

#pragma pack(push, 1)

std::vector<float> Duan1(int nCount, std::vector<float> pIn, std::vector<float> pHigh, std::vector<float> pLow); // 标准画法（原注释乱码：ĚŘŐ÷ĐňÁĐ）
std::vector<float> Duan2(int nCount, std::vector<float> pIn, std::vector<float> pHigh, std::vector<float> pLow); // 1+1终结画法（原注释乱码：1+1ÖŐ˝á）

#pragma pack(pop)

#endif
