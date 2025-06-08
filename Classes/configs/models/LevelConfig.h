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
 * @brief �ؿ������࣬�洢��̬�ؿ����ݣ��������ͱ����ƶ����ã�
 * @note ��ѭMVC�ܹ���configs��淶��������洢��̬��������
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
    std::vector<CardModel> _playfieldCards;  ///< �������������ã���Ӧ�ĵ�Playfield�ֶΣ�
    std::vector<CardModel> _stackCards;      ///< �����ƶ����ã���Ӧ�ĵ�Stack�ֶΣ�

    // ��ֹĬ�Ϲ���/����/��ֵ����LevelConfigLoader�����ʼ��
    LevelConfig() = default;
    ~LevelConfig() = default;
    LevelConfig(const LevelConfig&) = delete;
    LevelConfig& operator=(const LevelConfig&) = delete;

    friend class LevelConfigLoader;  ///< �������ü���������˽�г�Ա
};


#endif // CONFIGS_MODELS_LEVELCONFIG_H