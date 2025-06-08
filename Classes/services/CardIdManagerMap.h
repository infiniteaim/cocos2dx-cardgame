// CardIdViewMap.h
#ifndef CARD_ID_VIEW_MAP_H
#define CARD_ID_VIEW_MAP_H

#include "managers/CardManager.h"
#include <unordered_map>

/**
 * @brief 卡牌ID与管理器映射服务类
 * @职责：
 * 1. 通过单例模式（getInstance）提供全局唯一访问点，实现卡牌管理器的注册（addCardManager）与检索（getCardManager）；
 * 2. 基于unordered_map实现高效的O(1)复杂度映射查询，支持跨控制器（Controller）共享卡牌管理实例；
 * 3. 严格遵循"无状态"原则，不持有卡牌模型（CardModel）或视图（CardView）的生命周期，仅通过ID操作引用（）。
 *
 */
class CardIdManagerMap {
public:
    static CardIdManagerMap& getInstance() {
        static CardIdManagerMap instance;
        return instance;
    }

    void addCardManager(int cardId, CardManager* manager) {
        _cardIdManagerMap[cardId] = manager;
    }

    CardManager* getCardManager(int cardId) {
        auto it = _cardIdManagerMap.find(cardId);
        if (it != _cardIdManagerMap.end()) {
            return it->second;
        }
        return nullptr;
    }

private:
    CardIdManagerMap() {}
    ~CardIdManagerMap() {}

    std::unordered_map<int, CardManager*> _cardIdManagerMap;
};

#endif 