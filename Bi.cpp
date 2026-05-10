#include <iostream>
#include <fstream>
#include "Bi.h"
#include "KxianChuLi.h"
#include "BiChuLi.h"

// C++23/C++26 兼容修改：移除 using namespace std;，改为显式使用 std:: 前缀
// 原代码：using namespace std;

std::vector<float> Bi1(int nCount, std::vector<float> pHigh, std::vector<float> pLow)
{
    std::vector<float> pOut(nCount);
    KxianChuLi kxianChuLi;
    for (int i = 0; i < nCount; i++)
    {
        kxianChuLi.add(pHigh[i], pLow[i]);
    }
    for (unsigned int i = 1; i < kxianChuLi.kxianList.size(); i++)
    {
        if (kxianChuLi.kxianList.at(i - 1).fangXiang != kxianChuLi.kxianList.at(i).fangXiang)
        {
            if (kxianChuLi.kxianList.at(i - 1).fangXiang == 1)
            {
                pOut[kxianChuLi.kxianList.at(i - 1).zhongJian] = 1;
            }
            else if (kxianChuLi.kxianList.at(i - 1).fangXiang == -1)
            {
                pOut[kxianChuLi.kxianList.at(i - 1).zhongJian] = -1;
            }
        }
    }
    if (!kxianChuLi.kxianList.empty())
    {
        if (kxianChuLi.kxianList.back().fangXiang == 1)
        {
            pOut[kxianChuLi.kxianList.back().zhongJian] = 1;
        }
        else if (kxianChuLi.kxianList.back().fangXiang == -1)
        {
            pOut[kxianChuLi.kxianList.back().zhongJian] = -1;
        }
    }
    return pOut;
}

std::vector<float> Bi2(int nCount, std::vector<float> pHigh, std::vector<float> pLow)
{
    std::vector<float> pOut(nCount);
    KxianChuLi kxianChuLi;
    for (int i = 0; i < nCount; i++)
    {
        kxianChuLi.add(pHigh[i], pLow[i]);
    }
    BiChuLi biChuLi;
    biChuLi.handle(kxianChuLi.kxianList);
    // C++23/C++26 兼容修改：使用 auto 替换显式迭代器类型
    // 原代码：for (vector<Bi>::iterator iter = biChuLi.biList.begin(); iter != biChuLi.biList.end(); iter++)
    for (auto iter = biChuLi.biList.begin(); iter != biChuLi.biList.end(); ++iter)
    {
        if ((*iter).fangXiang == 1)
        {
            pOut[(*iter).kxianList.back().zhongJian] = 1;
        }
        else if ((*iter).fangXiang == -1)
        {
            pOut[(*iter).kxianList.back().zhongJian] = -1;
        }
    }
    return pOut;
}
