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
 * @brief ��Ϸȫ������ģ���ࣨ��ѭMVC�ܹ���models��淶��
 *
 * @ְ��
 * 1. ά����Ϸ��������������Ŀ��Ƽ��ϣ�
 *    - _playfield�������������б���ӦLevelConfig�е�Playfield���ã�����
 *    - _stackfield�������ƶѿ����б���ӦLevelConfig�е�Stack���ã�����
 * 2. ��������������ʷ��¼��ͨ��UndoModelʵ��״̬���˹��ܣ�����
 * 3. �ṩ���Ƽ��ϵ���ɾ�Ĳ�ӿڣ����������㣨controllers�������Ը�����Ϸ״̬������
 *
 */

class GameModel {
public:
    GameModel(LevelConfig* config) {
        if (config) {
            // ��ʼ����Ϸ����Ƭ
            _playfield = config->getPlayfield();
            // ��ʼ���ѵ���Ƭ
            _stackfield = config->getStack();

            _undoModel.clearHistory();
        }
    }

    // ��ȡ playfield ����
    const std::vector<CardModel>& getPlayfield() const {
        return _playfield;
    }

    // ��ȡ stackfield ����
    const std::vector<CardModel>& getStackfield() const {
        return _stackfield;
    }

    // ��ȡ UndoModel ����
    UndoModel& getUndoModel() {
        return _undoModel;
    }


    // �� playfield ���һ�ſ�Ƭ
    void addCardToPlayfield(const CardModel& card) {
        _playfield.push_back(card);
    }

    // �� stackfield ���һ�ſ�Ƭ
    void addCardToStackfield(const CardModel& card) {
        _stackfield.push_back(card);
    }

    // �� playfield �Ƴ�һ�ſ�Ƭ
    void removeCardFromPlayfield(int id) {
        for (auto it = _playfield.begin(); it != _playfield.end(); ++it) {
            if (it->_id == id) {
                _playfield.erase(it);
                break;
            }
        }
    }

    // �� stackfield �Ƴ�һ�ſ�Ƭ
    void removeCardFromStackfield(int id) {
        for (auto it = _stackfield.begin(); it != _stackfield.end(); ++it) {
            if (it->_id == id) {
                _stackfield.erase(it);
                break;
            }
        }
    }

private:
    std::vector<CardModel> _playfield; // ��Ϸ��������Ŀ�Ƭ����
    std::vector<CardModel> _stackfield; // �ѵ�����Ŀ�Ƭ����
    UndoModel _undoModel; // ���ڼ�¼������ʷ�Ķ���
};

#endif // GAME_MODEL_H_