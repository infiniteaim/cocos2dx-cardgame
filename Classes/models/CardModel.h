// CardModel.h
#ifndef CARD_MODEL_H_
#define CARD_MODEL_H_

#include "cocos2d.h"
USING_NS_CC;
enum class CardZone {
    Playfield,  // ������
    Stack,      // �����ƶ�
    Hand,
    Unknown     // ����ֵ������Ƿ�״̬
};

enum class CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,      // ÷��
    CST_DIAMONDS,   // ����
    CST_HEARTS,     // ����
    CST_SPADES,     // ����
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
 * @brief ��������ģ���ࣨ��ѭMVC�ܹ���models��淶��
 *
 * @��Ա����˵����
 * - _face�����Ƶ���ö�٣�CardFaceType����ȡֵ��ΧACE��1����KING��13����Ĭ��ֵΪACE������
 * - _suit�����ƻ�ɫö�٣�CardSuitType��������÷�������顢���ҡ��������֣�Ĭ��ֵΪ���ң�����
 * - _zone��������������ö�٣�CardZone����������������Playfield���������ƶѣ�Stack������������Hand���ȣ�Ĭ��ֵΪUnknown��
 * - _position�������ڳ����е����꣨cocos2d::Vec2����Ĭ��ֵΪԭ�㣨0, 0����
 * - _id������Ψһ��ʶ�������ڹ������㣨managers���Ϳ������㣨controllers�����ٶ�λʵ�����ο�����
 *
 * @���캯����
 * - �������캯������ʼ����������ɫ��λ�ã�������Ĭ������Unknown�����Զ�����ID�ĳ�����
 * - ȫ�����캯����֧����ʽָ��ID�����򣬷���"ģ�Ͳ�֧�����л�"����չ���󣨣���
 *
 * @�ӿ���ƣ�
 * - �ṩgetter/setter�����������ԣ���ѭ"��ĳ�Ա����˽�л�"�淶������
 * - �����޸Ľӿڣ���setZone��setPosition����ֱ�Ӹ��¿���״̬��������������ã�����
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