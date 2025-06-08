#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H
#include "models/UndoModel.h"
/**
 * @brief 撤销管理器类（遵循MVC架构的managers层规范）
 *
 * 该类属于管理器层（managers），负责统一管理游戏中的撤销操作，符合程序设计架构中"managers层提供全局性服务，可持有model数据并加工"的职责定义（）。
 * @职责：
 * 1. 通过构造函数注入UndoModel模型，建立与撤销数据的绑定关系，确保状态记录与恢复逻辑的完整性（）；
 * 2. 提供`recordUndoState`方法记录每次操作的卡牌状态（如位置、层级），基于栈结构实现"后进先出"的撤销顺序（）；
 * 3. `undo`方法执行撤销时，从UndoModel中获取最近一次记录的状态，逆向恢复卡牌位置和属性（）；
 * 4. 辅助方法`canUndo`、`clearUndoHistory`等用于查询撤销状态和清空历史记录，满足回退功能的交互需求（）。
 */
class UndoManager {
public:

    UndoManager(UndoModel& undoModel) {
        _undoModel = undoModel;
    }


    void recordUndoState(const UndoCardState& state) {
        _undoModel.record(state);
    }

    bool undo(UndoCardState& outState) {
        return _undoModel.undo(outState);
    }

    bool canUndo() const {
        return _undoModel.canUndo();
    }

    void clearUndoHistory() {
        _undoModel.clearHistory();
    }

    int getUndoSize() {
        return _undoModel.getSize();
    }


private:
    UndoModel _undoModel;

};
#endif