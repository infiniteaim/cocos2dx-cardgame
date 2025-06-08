// gamemodel.h
#ifndef GAME_MODEL_H_
#define GAME_MODEL_H_

#include "cocos2d.h"
#include "CardModel.h"
#include "UndoModel.h"
#include <vector>
#include "configs/loaders/LevelConfigLoader.h"
#include "configs/models/LevelConfig.h"

USING_NS_CC;
/**
 * @brief 游戏全局数据模型类（遵循MVC架构的models层规范）
 *
 * @职责：
 * 1. 维护游戏中两个核心区域的卡牌集合：
 *    - _playfield：主牌区卡牌列表，对应LevelConfig中的Playfield配置（）；
 *    - _stackfield：备用牌堆卡牌列表，对应LevelConfig中的Stack配置（）。
 * 2. 管理撤销操作的历史记录，通过UndoModel实现状态回退功能（）。
 * 3. 提供卡牌集合的增删改查接口，供控制器层（controllers）调用以更新游戏状态（）。
 *
 */

class GameModel {
public:
    GameModel(LevelConfig* config) {
        if (config) {
            // 初始化游戏区域卡片
            _playfield = config->getPlayfield();
            // 初始化堆叠卡片
            _stackfield = config->getStack();

            _undoModel.clearHistory();
        }
    }

    // 获取 playfield 向量
    const std::vector<CardModel>& getPlayfield() const {
        return _playfield;
    }

    // 获取 stackfield 向量
    const std::vector<CardModel>& getStackfield() const {
        return _stackfield;
    }

    // 获取 UndoModel 对象
    UndoModel& getUndoModel() {
        return _undoModel;
    }


    // 向 playfield 添加一张卡片
    void addCardToPlayfield(const CardModel& card) {
        _playfield.push_back(card);
    }

    // 向 stackfield 添加一张卡片
    void addCardToStackfield(const CardModel& card) {
        _stackfield.push_back(card);
    }

    // 从 playfield 移除一张卡片
    void removeCardFromPlayfield(int id) {
        for (auto it = _playfield.begin(); it != _playfield.end(); ++it) {
            if (it->_id == id) {
                _playfield.erase(it);
                break;
            }
        }
    }

    // 从 stackfield 移除一张卡片
    void removeCardFromStackfield(int id) {
        for (auto it = _stackfield.begin(); it != _stackfield.end(); ++it) {
            if (it->_id == id) {
                _stackfield.erase(it);
                break;
            }
        }
    }

private:
    std::vector<CardModel> _playfield; // 游戏场地区域的卡片向量
    std::vector<CardModel> _stackfield; // 堆叠区域的卡片向量
    UndoModel _undoModel; // 用于记录撤销历史的对象
};

#endif // GAME_MODEL_H_