// GameController.h
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "managers/CardManager.h"
#include <vector>

class CardManager;
/**
 * @brief ��Ϸ�������ࣨ��ѭMVC�ܹ���controllers��淶��
 * ��������Ϸ���̵ĺ��Ŀ�����������Э��GameModel��GameView/CardView�Ľ�����
 * 1. �������ƶѿ��Ƶ��ƥ���߼���selectCardFromPlayefieldAndMatch������֤�����Ƿ�����������򣨣���
 * 2. ����Stack�����Ƶ���¼���ͨ��UndoManager��¼����״̬������
 * 3. ʵ�ֻ��˹��ܣ�undo��������UndoModel��¼��״̬����ָ�����λ�ú�״̬������
 * 4. Э����ͼ����£������CardView�����ӿ�ִ�п����ƶ�������
 *
 */
class GameController {
public:
    GameController(GameModel gameModel);
    ~GameController();

    // ѡ�����ƶ��з�����ֽ�ƣ�������ƶ��е��ƺ͵���ƥ��
    bool selectCardFromPlayefieldAndMatch(CardModel& selectedCard);

    // ���Stack���Ŀ��ƣ���¼��״̬��UndoModel��
    void clickStackCard(CardModel& card);

    // ����Ƭ����¼�
    void handleCardClicked(CardModel& card);

    // ������˰�ť
    bool undo();

    void GameController::handleLabelClick();
private:
    GameModel _gameModel;
    UndoManager _undoManager;

    // ��ȡ���Ƶ�CardModel
    CardModel getBottomCard();

    // ����������Ƿ�ƥ��
    bool isCardMatch(const CardModel& card1, const CardModel& card2);

    // �ƶ����Ƶ�ԭλ��
    void moveCardToOriginalPosition(const UndoCardState& state);

    // ����CardModel��ȡCardManager
    CardManager* getCardManager(const CardModel& card);


};
#endif