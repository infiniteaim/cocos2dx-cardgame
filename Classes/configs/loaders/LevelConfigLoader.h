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

using namespace rapidjson; // �����ռ�


/**
 * @class LevelConfigLoader
 * @brief �ؿ����ü���������̬�ࣩ���������JSON��ʽ�Ĺؿ������ļ�
 * @note ����configs/loadersģ�飬��ѭ���ü����߼�������ģ�ͷ���ԭ��
 * @warning �����rapidjson��ʵ��JSON������cpp�ļ���ʵ�־�������߼���
 */
    class LevelConfigLoader final {
    public:
        /**
         * @brief ����ָ���ؿ�����������
         * @param levelId �ؿ�ID����ӦJSON�ļ����еı�ʶ����"level_1.json"��ӦlevelId=1��
         * @return ������Ĺؿ����ö�������ָ�룩������ʧ��ʱ����nullptr
         */
        static LevelConfig* loadLevelConfig(std::string fileName);

    private:

        static int currentId;

        /**
         * @brief ˽�й��캯������ֹʵ��������̬����ƣ�
         */
        LevelConfigLoader() = default;

        /**
         * @brief ��ֹ�������캯��
         */
        LevelConfigLoader(const LevelConfigLoader&) = delete;

        /**
         * @brief ��ֹ��ֵ�����
         */
        LevelConfigLoader& operator=(const LevelConfigLoader&) = delete;

        static bool parseCardModel(const rapidjson::Value& cardNode, std::vector<CardModel>& target, CardZone zone);
};



#endif // CONFIGS_LOADERS_LEVELCONFIGLOADER_H