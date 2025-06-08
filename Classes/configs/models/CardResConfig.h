
#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H
#include <string>
#include <array>
#include "LevelConfig.h"
#include "models/CardModel.h"

/**
 * @brief ������Դ�����ࣨ��ѭMVC�ܹ���configs��淶��
 *
 * ���ฺ���ṩ������ص�������Դ·�����ã�������������ɫͼ�ꡢ���ֵ���Դ��·�������߼���
 * ����Ϸ��ϳ�����Ƽܹ�Ҫ���е�"��̬���������"ְ�𣨣�������Դ·�����й���
 * ���ں�����չ�¿�����Դ���޸���Դ·������ͬʱ����Ӳ�������⣬���������ά���ԡ�
 *
 * @note ����CardSuitType��CardFaceTypeö�ٶ��壨����
 * ���з�����Ϊ��̬����������ʵ�������ɵ��ã�����"�������ṩͨ�ù���"�ı���淶������
 */

class CardResConfig {
public:
    /**
     * @brief ��ȡ��Ƭ����·��
     * @param suit ��ɫö��
     * @return ��Դ�ļ�·������"club.png"��
     */
    static std::string getBackGround() {
        return "res/card_general.png";
    }

    /**
     * @brief ��ȡ��ɫͼ����Դ·�������Ͻǣ�
     * @param suit ��ɫö��
     * @return ��Դ�ļ�·������"club.png"��
     */
    static std::string getSuitRes(CardSuitType suit) {
        switch (suit) {
        case CardSuitType::CST_CLUBS:    return "res/suits/club.png";
        case CardSuitType::CST_DIAMONDS: return "res/suits/diamond.png";
        case CardSuitType::CST_HEARTS:   return "res/suits/heart.png";
        case CardSuitType::CST_SPADES:   return "res/suits/spade.png";
        default: return ""; // ����Ƿ�ö��
        }
    }

    /**
     * @brief ��ȡ���Ͻ�С������Դ·��
     * @param suit ��ɫ��������ɫ����/�죩
     * @param face ����
     * @return ��Դ�ļ�·������"small_black_3.png"��
     */
    static std::string getSmallNumberRes(CardSuitType suit, CardFaceType face) {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (color.empty() || faceStr.empty()) {
            return ""; // �Ƿ����������ؿ�
        }
        return "res/number/small_" + color + "_" + faceStr + ".png";
    }

    /**
     * @brief ��ȡ�м��������Դ·��
     * @param suit ��ɫ��������ɫ����/�죩
     * @param face ����
     * @return ��Դ�ļ�·������"big_red_3.png"��
     */
    static std::string getBigNumberRes(CardSuitType suit, CardFaceType face) {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (color.empty() || faceStr.empty()) {
            return ""; // �Ƿ����������ؿ�
        }
        return "res/number/big_" + color + "_" + faceStr + ".png";
    }

private:
    /**
     * @brief ������ö��ת��Ϊ�ַ�������CardFaceType::Three �� "3"��
     * @param face ����ö��
     * @return �����ַ���
     */
    static std::string faceToString(CardFaceType face) {
        const std::string faceNames[] = {
        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
        };

        int index = static_cast<int>(face);
        // У��ö�ٷ�Χ���ų�CFT_NONE��CFT_NUM_CARD_FACE_TYPES��
        if (index < 0 || index >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES)) {
            return ""; // �Ƿ�ö�٣����ؿ�
        }
        return faceNames[index];
    }

     /**
     * @brief ���ݻ�ɫ�ж���ɫ����/�죩
     * @param suit ��ɫö��
     * @return ��ɫ�ַ�����"black" �� "red"��
     */
    static std::string suitToColor(CardSuitType suit) {
        if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES) {
            return "black";
        }
        else {
            return "red";
        }
    }
};

#endif // CARD_RES_CONFIG_H