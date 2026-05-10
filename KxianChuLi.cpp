#include "KxianChuLi.h"
#include <algorithm>  // 2026-05-10 22:35 - 缠论原著修正：添加algorithm用于std::max/std::min

// C++23/C++26 兼容修改：移除 using namespace std;，改为显式使用 std:: 前缀
// 原代码：using namespace std;

void KxianChuLi::add(float gao, float di)
{
    KxianRaw kxianRaw;
    kxianRaw.gao = gao;
    kxianRaw.di = di;
    // 保存原始K线
    this->kxianRawList.push_back(kxianRaw);
    if (this->kxianList.empty())
    {
        // 第一根K线先假设方向为上
        Kxian kxian;
        kxian.gao = gao;
        kxian.di = di;
        kxian.fangXiang = 1;
        kxian.kaiShi = 0;
        kxian.jieShu = 0;
        kxian.zhongJian = 0;
        this->kxianList.push_back(kxian);
    }
    else
    {
        if (gao > this->kxianList.back().gao && di > this->kxianList.back().di)
        {
            // 向上
            Kxian kxian;
            kxian.gao = gao;
            kxian.di = di;
            kxian.fangXiang = 1;
            kxian.kaiShi = this->kxianList.back().jieShu + 1;
            kxian.jieShu = kxian.kaiShi;
            kxian.zhongJian = kxian.kaiShi;
            // 新K线
            this->kxianList.push_back(kxian);
        }
        else if (gao < this->kxianList.back().gao && di < this->kxianList.back().di)
        {
            // 向下
            Kxian kxian;
            kxian.gao = gao;
            kxian.di = di;
            kxian.fangXiang = -1;
            kxian.kaiShi = this->kxianList.back().jieShu + 1;
            kxian.jieShu = kxian.kaiShi;
            kxian.zhongJian = kxian.kaiShi;
            // 新K线
            this->kxianList.push_back(kxian);
        }
        else if (gao <= this->kxianList.back().gao && di >= this->kxianList.back().di)
        {
            // 前包含
            // 2026-05-10 22:38 - 缠论原著第29课修正：前包含合并规则
            // 原著规则：向上取高高、高低；向下取低低、低高
            // 原代码：
            // if (this->kxianList.back().fangXiang == 1)
            // {
            //     this->kxianList.back().di = di;
            // }
            // else
            // {
            //     this->kxianList.back().gao = gao;
            // }
            if (this->kxianList.back().fangXiang == 1)
            {
                // 向上：取较高的低点（高低）
                this->kxianList.back().di = std::max(this->kxianList.back().di, di);
            }
            else
            {
                // 向下：取较低的高点（低高）
                this->kxianList.back().gao = std::min(this->kxianList.back().gao, gao);
            }
            this->kxianList.back().jieShu = this->kxianList.back().jieShu + 1;
        }
        else
        {
            // 后包含
            // 2026-05-10 22:40 - 缠论原著第29课修正：后包含合并规则
            // 原著规则：向上取高高、高低；向下取低低、低高
            // 原代码：
            // if (this->kxianList.back().fangXiang == 1)
            // {
            //     this->kxianList.back().gao = gao;
            // }
            // else
            // {
            //     this->kxianList.back().di = di;
            // }
            // this->kxianList.back().jieShu = this->kxianList.back().jieShu + 1;
            // this->kxianList.back().zhongJian = this->kxianList.back().jieShu;
            if (this->kxianList.back().fangXiang == 1)
            {
                // 向上：取较高的高点（高高）和较高的低点（高低）
                this->kxianList.back().gao = std::max(this->kxianList.back().gao, gao);
                this->kxianList.back().di = std::max(this->kxianList.back().di, di);
                this->kxianList.back().zhongJian = this->kxianList.back().jieShu;  // 更新中心点
            }
            else
            {
                // 向下：取较低的高点（低高）和较低的低点（低低）
                this->kxianList.back().gao = std::min(this->kxianList.back().gao, gao);
                this->kxianList.back().di = std::min(this->kxianList.back().di, di);
            }
            this->kxianList.back().jieShu = this->kxianList.back().jieShu + 1;
        }
    }
}
