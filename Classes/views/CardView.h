#ifndef CARD_VIEW_H_
#define CARD_VIEW_H_

#include "cocos2d.h"
#include "models/CardModel.h"      // 包含卡牌数据模型
#include "configs/models/CardResConfig.h"    // 包含资源路径工具
#include "managers/CardManager.h"

// 前向声明 CardManager 类
class CardManager;
USING_NS_CC;
/**
 * @brief 卡牌视图类（遵循MVC架构的views层规范）
 *
 * @职责：
 * 1. 基于CardModel数据渲染卡牌视觉元素，包括背景、数字、花色图标等；
 * 2. 处理触摸事件，判断点击区域并触发回调通知控制器；
 * 3. 提供卡牌选中状态的视觉反馈（如高亮、缩放等）。
 *
 * @渲染结构：
 * - 卡牌背景（_background）：基础矩形，定义卡牌轮廓；
 * - 左上角小数字（_smallNumber）：显示卡牌点数的小型图标；
 * - 中间大数字（_bigNumber）：突出显示的卡牌点数；
 * - 右上角花色图标（_suitIcon）：显示卡牌花色的图标。
 */

class CardView : public Node {
public:
    /**
     * @brief 静态创建方法（工厂模式）
     * @param model 卡牌数据模型（包含花色、点数）
     */
    static CardView* create(const CardModel& model, const Vec2& offset);
    // 卡牌点击回调类型
    using ClickCallback = std::function<void(CardView* cardView)>;
    // 设置点击回调
    void setClickCallback(const ClickCallback& callback);

    // ========== 资源加载方法 ==========
    void loadBackground();
    void loadSmallNumber(const CardModel& model);
    void loadBigNumber(const CardModel& model);
    void loadSuitIcon(const CardModel& model);

    bool init(const CardModel& model, const Vec2& offset);  // 初始化

    // 检查触摸点是否在卡牌区域内
    bool isTouchInside(const cocos2d::Vec2& touchPos);

    CardManager* _cardManager;     // 添加 CardManager 实例

private:
    // ========== 子节点成员 ==========
    Sprite* _background = nullptr;  // 卡牌背景
    Sprite* _smallNumber = nullptr; // 左上角小数字
    Sprite* _bigNumber = nullptr;   // 中间大数字
    Sprite* _suitIcon = nullptr;    // 右上角花色图标

    // ========== 布局参数（可根据美术资源调整） ==========
    const Vec2 _smallNumberPos = Vec2(-80, 130);  // 左上角小数字位置（相对背景中心）
    const Vec2 _suitIconPos = Vec2(80, 130);     // 右上角花色图标位置（相对背景中心）
    const Vec2 _bigNumberPos = Vec2(0, 0);       // 中间大数字位置（相对背景中心）

    ClickCallback _clickCallback;  // 点击回调函数
    bool _isSelected;              // 卡牌是否被选中状态
};

#endif // CARD_VIEW_H_