#ifndef __BI_H__
#define __BI_H__

#include <vector>

// C++23/C++26 兼容修改：移除 using namespace std;，改为显式使用 std:: 前缀
// 原代码：无 using namespace std;（原文件未使用）

#pragma pack(push, 1)

std::vector<float> Bi1(int nCount, std::vector<float> pHigh, std::vector<float> pLow);
std::vector<float> Bi2(int nCount, std::vector<float> pHigh, std::vector<float> pLow);

#pragma pack(pop)

#endif
