#pragma once
#ifndef CONFIGS_MODELS_LEVELCONFIG_H
#define CONFIGS_MODELS_LEVELCONFIG_H

#include "cocos2d.h"
#include <vector>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include "json/filereadstream.h"
#include "models/CardModel.h"

using namespace rapidjson; 
/**
 * @class LevelConfig
 * @brief 关卡配置类，存储静态关卡数据（主牌区和备用牌堆配置）
 * @note 遵循MVC架构的configs层规范，仅负责存储静态配置数据
 */
class LevelConfig final {
public:

    std::vector<CardModel> getPlayfield() {
        return _playfieldCards;
    }

    std::vector<CardModel> getStack() {
        return _stackCards;
    }

private:
    std::vector<CardModel> _playfieldCards;  ///< 主牌区卡牌配置（对应文档Playfield字段）
    std::vector<CardModel> _stackCards;      ///< 备用牌堆配置（对应文档Stack字段）

    // 禁止默认构造/拷贝/赋值，由LevelConfigLoader负责初始化
    LevelConfig() = default;
    ~LevelConfig() = default;
    LevelConfig(const LevelConfig&) = delete;
    LevelConfig& operator=(const LevelConfig&) = delete;

    friend class LevelConfigLoader;  ///< 允许配置加载器访问私有成员
};


#endif // CONFIGS_MODELS_LEVELCONFIG_H