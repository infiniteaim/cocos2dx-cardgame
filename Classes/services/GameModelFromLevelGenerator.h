#ifndef GAME_MODEL_FROM_LEVEL_GENERATOR_H_
#define GAME_MODEL_FROM_LEVEL_GENERATOR_H_

#include "models/GameModel.h"
#include "views/GameView.h"
#include "configs/models/LevelConfig.h"  // ���� LevelConfig ����������������
#include <vector>

USING_NS_CC;

/**
 * @brief ����㣺����̬�ؿ����ã�LevelConfig��ת��Ϊ����ʱ��Ϸģ�ͣ�GameModel��
 * @note ��ѭ Service ��淶����״̬��������ʽ�ӿڡ��ɾ�̬����
 */
class GameModelFromLevelGenerator {
public:
    /**
     * @brief ���� GameModel ����
     * @param config �ؿ��������ݣ��� LevelConfigLoader ���أ�
     * @return ��ʼ����� GameModel ����
     * @throws �� config Ϊ�ջ������ݷǷ������ؿ�ģ�ͣ������ʵ����������쳣��
     */
    static GameModel generateGameModel(const std::string levelFile) {
        auto config = LevelConfigLoader::loadLevelConfig("level_1.json");
        GameModel gameModel(config);
        return gameModel;
    }

    static void generateGameView(GameModel& gameModel, Node* parent) {
        // ���� GameView ʵ��
        auto gameView = GameView::create(gameModel);
        if (gameView) {
            parent->addChild(gameView, 1); // �� GameView ��ӵ�������
        }
    }
private:
    /**
     * @brief ˽�й��캯������ֹʵ��������̬�ࣩ
     */
    GameModelFromLevelGenerator() = default;
};

#endif // GAME_MODEL_FROM_LEVEL_GENERATOR_H_