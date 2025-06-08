// CardModel.h
#ifndef CARD_MODEL_H_
#define CARD_MODEL_H_

#include "cocos2d.h"
USING_NS_CC;
enum class CardZone {
    Playfield,  // 主牌区
    Stack,      // 备用牌堆
    Hand,
    Unknown     // 兜底值，避免非法状态
};

enum class CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};


enum class CardFaceType {
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

/**
 * @brief 卡牌数据模型类（遵循MVC架构的models层规范）
 *
 * @成员变量说明：
 * - _face：卡牌点数枚举（CardFaceType），取值范围ACE（1）至KING（13），默认值为ACE（）；
 * - _suit：卡牌花色枚举（CardSuitType），包含梅花、方块、红桃、黑桃四种，默认值为黑桃（）；
 * - _zone：卡牌所在区域枚举（CardZone），包括主牌区（Playfield）、备用牌堆（Stack）、手牌区（Hand）等，默认值为Unknown；
 * - _position：卡牌在场景中的坐标（cocos2d::Vec2），默认值为原点（0, 0）；
 * - _id：卡牌唯一标识符，用于管理器层（managers）和控制器层（controllers）快速定位实例（参考）。
 *
 * @构造函数：
 * - 基础构造函数：初始化点数、花色、位置，适用于默认区域（Unknown）和自动分配ID的场景；
 * - 全量构造函数：支持显式指定ID和区域，符合"模型层支持序列化"的扩展需求（）。
 *
 * @接口设计：
 * - 提供getter/setter方法访问属性，遵循"类的成员变量私有化"规范（）；
 * - 属性修改接口（如setZone、setPosition）可直接更新卡牌状态，供控制器层调用（）。
 */
class CardModel {
public:
    CardModel(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position):   
        _face(face)
        , _suit(suit)
        , _position(position) {}

    CardModel(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position, int id, CardZone zone): 
        _face(face)
        , _suit(suit)
        , _position(position)
        , _id(id)
        , _zone(zone){}

    CardFaceType getFace() const { return _face; }
    CardSuitType getSuit() const { return _suit; }
    const cocos2d::Vec2& getPosition() const { return _position; }
    const CardZone getZone() const { return _zone; }
    void setZone(CardZone zone) { _zone = zone; }
    void setPosition(Vec2 position) { _position = position; }
    int _id;

private:
    CardFaceType _face{ CardFaceType::CFT_ACE };
    CardSuitType _suit{ CardSuitType::CST_SPADES };

    CardZone _zone;
    cocos2d::Vec2 _position{ cocos2d::Vec2::ZERO };
};

#endif // CARD_MODEL_H_