#ifndef GAME_MODEL_FROM_LEVEL_GENERATOR_H_
#define GAME_MODEL_FROM_LEVEL_GENERATOR_H_

#include "models/GameModel.h"
#include "views/GameView.h"
#include "configs/models/LevelConfig.h"  // 假设 LevelConfig 包含卡牌配置数据
#include <vector>

USING_NS_CC;

/**
 * @brief 服务层：将静态关卡配置（LevelConfig）转换为运行时游戏模型（GameModel）
 * @note 遵循 Service 层规范：无状态、纯函数式接口、可静态调用
 */
class GameModelFromLevelGenerator {
public:
    /**
     * @brief 生成 GameModel 对象
     * @param config 关卡配置数据（从 LevelConfigLoader 加载）
     * @return 初始化后的 GameModel 对象
     * @throws 若 config 为空或卡牌数据非法，返回空模型（需根据实际情况处理异常）
     */
    static GameModel generateGameModel(const std::string levelFile) {
        auto config = LevelConfigLoader::loadLevelConfig("level_1.json");
        GameModel gameModel(config);
        return gameModel;
    }

    static void generateGameView(GameModel& gameModel, Node* parent) {
        // 创建 GameView 实例
        auto gameView = GameView::create(gameModel);
        if (gameView) {
            parent->addChild(gameView, 1); // 将 GameView 添加到场景中
        }
    }
private:
    /**
     * @brief 私有构造函数：禁止实例化（静态类）
     */
    GameModelFromLevelGenerator() = default;
};

#endif // GAME_MODEL_FROM_LEVEL_GENERATOR_H_