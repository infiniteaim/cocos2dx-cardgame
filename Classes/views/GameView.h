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
 * @brief ��Ϸ����ͼ�ࣨ��ѭMVC�ܹ���views��淶��
 *
 * @ְ��
 * 1. ����GameModel������Ⱦ��Ϸ�����棬������������playfield���ͱ����ƶѣ�stackfield����
 * 2. ��������CardViewʵ�����������ڣ�����ģ�����ݶ�̬���ɻ����ٿ�����ͼ��
 * 3. ����ȫ�ִ����¼���UI��������״̬��ǩ���������ͨ���ص�֪ͨ��������
 * 4. �ṩ��Ϸ״̬�Ŀ��ӻ�չʾ����_statusLabel��ʾ��ǰ��Ϸ״̬����
 *
 * @��Ⱦ�ṹ��
 * - _playfieldCardViews��������������ͼ���ϣ���ӦGameModel�е�_playfield��
 * - _stackfieldCardViews�������ƶѿ�����ͼ���ϣ���ӦGameModel�е�_stackfield��
 * - _statusLabel����Ϸ״̬�ı���ǩ�������ǻ��˱�ǩ��
 *
 */
class GameView : public Node {
public:
    /**
     * @brief ��̬���� GameView �ķ���
     * @param model GameModel �������ڳ�ʼ�� GameView
     */
    static GameView* create(GameModel& model);

protected:
    /**
     * @brief ��ʼ�� GameView ���߼�
     * @param model GameModel �������ڳ�ʼ�� GameView
     * @return ��ʼ���ɹ����� true�����򷵻� false
     */
    bool init(GameModel& model);

    /**
     * @brief ���� GameModel ���ɶ�Ӧ�� CardView ����
     * @param model GameModel ���󣬰�����Ƭ��Ϣ
     */
    void generateCardViews(GameModel& model);

private:
    std::vector<CardView*> _playfieldCardViews; // �洢 playfield ��Ӧ�� CardView ����
    std::vector<CardView*> _stackfieldCardViews; // �洢 stackfield ��Ӧ�� CardView ����

    // Label ��Ա����
    cocos2d::Label* _statusLabel;


    // GameController ��Ա����
    GameController* _gameController;
    // ���� Label ����Ļص�����
    void onLabelClicked();

    // ע�ᴥ���¼�
    void registerTouchEvents();
};

#endif // GAME_VIEW_H_