#ifndef CARD_VIEW_H_
#define CARD_VIEW_H_

#include "cocos2d.h"
#include "models/CardModel.h"      // ������������ģ��
#include "configs/models/CardResConfig.h"    // ������Դ·������
#include "managers/CardManager.h"

// ǰ������ CardManager ��
class CardManager;
USING_NS_CC;
/**
 * @brief ������ͼ�ࣨ��ѭMVC�ܹ���views��淶��
 *
 * @ְ��
 * 1. ����CardModel������Ⱦ�����Ӿ�Ԫ�أ��������������֡���ɫͼ��ȣ�
 * 2. �������¼����жϵ�����򲢴����ص�֪ͨ��������
 * 3. �ṩ����ѡ��״̬���Ӿ�����������������ŵȣ���
 *
 * @��Ⱦ�ṹ��
 * - ���Ʊ�����_background�����������Σ����忨��������
 * - ���Ͻ�С���֣�_smallNumber������ʾ���Ƶ�����С��ͼ�ꣻ
 * - �м�����֣�_bigNumber����ͻ����ʾ�Ŀ��Ƶ�����
 * - ���Ͻǻ�ɫͼ�꣨_suitIcon������ʾ���ƻ�ɫ��ͼ�ꡣ
 */

class CardView : public Node {
public:
    /**
     * @brief ��̬��������������ģʽ��
     * @param model ��������ģ�ͣ�������ɫ��������
     */
    static CardView* create(const CardModel& model, const Vec2& offset);
    // ���Ƶ���ص�����
    using ClickCallback = std::function<void(CardView* cardView)>;
    // ���õ���ص�
    void setClickCallback(const ClickCallback& callback);

    // ========== ��Դ���ط��� ==========
    void loadBackground();
    void loadSmallNumber(const CardModel& model);
    void loadBigNumber(const CardModel& model);
    void loadSuitIcon(const CardModel& model);

    bool init(const CardModel& model, const Vec2& offset);  // ��ʼ��

    // ��鴥�����Ƿ��ڿ���������
    bool isTouchInside(const cocos2d::Vec2& touchPos);

    CardManager* _cardManager;     // ��� CardManager ʵ��

private:
    // ========== �ӽڵ��Ա ==========
    Sprite* _background = nullptr;  // ���Ʊ���
    Sprite* _smallNumber = nullptr; // ���Ͻ�С����
    Sprite* _bigNumber = nullptr;   // �м������
    Sprite* _suitIcon = nullptr;    // ���Ͻǻ�ɫͼ��

    // ========== ���ֲ������ɸ���������Դ������ ==========
    const Vec2 _smallNumberPos = Vec2(-80, 130);  // ���Ͻ�С����λ�ã���Ա������ģ�
    const Vec2 _suitIconPos = Vec2(80, 130);     // ���Ͻǻ�ɫͼ��λ�ã���Ա������ģ�
    const Vec2 _bigNumberPos = Vec2(0, 0);       // �м������λ�ã���Ա������ģ�

    ClickCallback _clickCallback;  // ����ص�����
    bool _isSelected;              // �����Ƿ�ѡ��״̬
};

#endif // CARD_VIEW_H_