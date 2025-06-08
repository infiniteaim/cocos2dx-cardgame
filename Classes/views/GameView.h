#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include "cocos2d.h"
#include "models/GameModel.h"
#include "CardView.h"
#include <vector>
#include "managers/UndoManager.h"
#include "controllers/GameController.h"

USING_NS_CC;
/**
 * @brief 游戏主视图类（遵循MVC架构的views层规范）
 *
 * @职责：
 * 1. 基于GameModel数据渲染游戏主界面，包括主牌区（playfield）和备用牌堆（stackfield）；
 * 2. 管理所有CardView实例的生命周期，根据模型数据动态生成或销毁卡牌视图；
 * 3. 处理全局触摸事件和UI交互（如状态标签点击），并通过回调通知控制器；
 * 4. 提供游戏状态的可视化展示（如_statusLabel显示当前游戏状态）。
 *
 * @渲染结构：
 * - _playfieldCardViews：主牌区卡牌视图集合，对应GameModel中的_playfield；
 * - _stackfieldCardViews：备用牌堆卡牌视图集合，对应GameModel中的_stackfield；
 * - _statusLabel：游戏状态文本标签，这里是回退标签。
 *
 */
class GameView : public Node {
public:
    /**
     * @brief 静态创建 GameView 的方法
     * @param model GameModel 对象，用于初始化 GameView
     */
    static GameView* create(GameModel& model);

protected:
    /**
     * @brief 初始化 GameView 的逻辑
     * @param model GameModel 对象，用于初始化 GameView
     * @return 初始化成功返回 true，否则返回 false
     */
    bool init(GameModel& model);

    /**
     * @brief 根据 GameModel 生成对应的 CardView 数组
     * @param model GameModel 对象，包含卡片信息
     */
    void generateCardViews(GameModel& model);

private:
    std::vector<CardView*> _playfieldCardViews; // 存储 playfield 对应的 CardView 数组
    std::vector<CardView*> _stackfieldCardViews; // 存储 stackfield 对应的 CardView 数组

    // Label 成员变量
    cocos2d::Label* _statusLabel;


    // GameController 成员变量
    GameController* _gameController;
    // 处理 Label 点击的回调函数
    void onLabelClicked();

    // 注册触摸事件
    void registerTouchEvents();
};

#endif // GAME_VIEW_H_