// CardManager.h
#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H

#include "models/CardModel.h"
#include "views/CardView.h"
#include "cocos2d.h"

class CardView;
/**
 * @brief ���ƹ�������
 * @ְ��
 * 1. ��ʼ�����ƴ����¼���������setupTouchEvents��������������߼���
 *    ����������ʼ��onTouchBegan�����ƶ���onTouchMoved����������onTouchEnded�����¼���
 * 2. ά������ģ�ͣ�CardModel������ͼ��CardView����˫�����ã�
 *    ͨ��setCard������ģ������ͼʵ��������
 * 3. �ṩ����ص��ӿڣ�setCardClickedCallback�������û������¼����ݸ���������Controller����
 *    ��ѭ"Managersͨ���ص��ӿ�������ģ�齻��"�����ԭ�򣨣���
 * 4. ������ѡ��״̬��_isSelected���������Ӿ������������Ŷ�������
 *
 */
class CardManager {
public:
    CardManager(const CardModel& model);
    ~CardManager();

    void setCard(const CardModel& model, CardView* view);
    void setupTouchEvents();

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

    // ���õ���ص�����
    void setCardClickedCallback(const std::function<void(CardModel&)>& callback);
    CardView* getView() { return _view; }
    CardModel getModel() {return _model;}

private:
    CardModel _model;
    CardView* _view;
    bool _isSelected;

    std::function<void(CardModel&)> _cardClickedCallback;
};

#endif // CARD_MANAGER_H