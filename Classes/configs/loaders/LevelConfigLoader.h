#pragma once
#ifndef CONFIGS_LOADERS_LEVELCONFIGLOADER_H
#define CONFIGS_LOADERS_LEVELCONFIGLOADER_H

#include "configs/models/LevelConfig.h"
#include "cocos2d.h"
#include <memory>
#include <fstream>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include "json/filereadstream.h"
#include "models/CardModel.h"

using namespace rapidjson; // 命名空间


/**
 * @class LevelConfigLoader
 * @brief 关卡配置加载器（静态类），负责解析JSON格式的关卡配置文件
 * @note 属于configs/loaders模块，遵循配置加载逻辑与数据模型分离原则
 * @warning 需配合rapidjson库实现JSON解析（cpp文件中实现具体解析逻辑）
 */
    class LevelConfigLoader final {
    public:
        /**
         * @brief 加载指定关卡的配置数据
         * @param levelId 关卡ID（对应JSON文件名中的标识，如"level_1.json"对应levelId=1）
         * @return 解析后的关卡配置对象（智能指针），加载失败时返回nullptr
         */
        static LevelConfig* loadLevelConfig(std::string fileName);

    private:

        static int currentId;

        /**
         * @brief 私有构造函数，禁止实例化（静态类设计）
         */
        LevelConfigLoader() = default;

        /**
         * @brief 禁止拷贝构造函数
         */
        LevelConfigLoader(const LevelConfigLoader&) = delete;

        /**
         * @brief 禁止赋值运算符
         */
        LevelConfigLoader& operator=(const LevelConfigLoader&) = delete;

        static bool parseCardModel(const rapidjson::Value& cardNode, std::vector<CardModel>& target, CardZone zone);
};



#endif // CONFIGS_LOADERS_LEVELCONFIGLOADER_H