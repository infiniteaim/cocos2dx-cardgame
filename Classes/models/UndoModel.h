#ifndef UNDO_MODEL_H_
#define UNDO_MODEL_H_

#include "cocos2d.h"
#include "CardModel.h"  

USING_NS_CC;


struct UndoCardState {
    int id;
    Vec2 position;       // 操作前的位置
    CardZone zone;
};
/**
 * @brief 撤销操作数据模型类（遵循MVC架构的models层规范）
 *
 * @职责：
 * 1. 通过`record`方法记录卡牌操作前的状态（位置、区域），保存为UndoCardState结构体；
 * 2. 通过`undo`方法获取最近一次操作的状态，支持按"后进先出"顺序恢复历史；
 * 3. 提供`clearHistory`和`canUndo`方法管理历史记录生命周期，满足回退功能的交互需求（）。
 */
class UndoModel {
public:
    UndoModel() = default;


    void record(const UndoCardState& state) {
        _history.push_back(state);  // 追加操作快照到历史
    }

    bool UndoModel::undo(UndoCardState& outState) {
        if (_history.empty()) {
            return false;  // 无历史可回退
        }
        // 取出最后一次操作的状态
        outState = _history.back();
        // 从历史中移除（回退）
        _history.pop_back();
        return true;
    }

    void UndoModel::clearHistory() {
        _history.clear();  // 清空所有快照
    }

    /**
     * @brief 检查是否有可回退的操作
     */
    bool canUndo() const { return !_history.empty(); }

    int getSize() const { return _history.size(); }

private:
    std::vector<UndoCardState> _history;  // 操作历史（按时间顺序存储，回退时逆序弹出）
};

#endif // UNDO_MODEL_H_