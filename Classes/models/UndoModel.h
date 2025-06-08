#ifndef UNDO_MODEL_H_
#define UNDO_MODEL_H_

#include "cocos2d.h"
#include "CardModel.h"  

USING_NS_CC;


struct UndoCardState {
    int id;
    Vec2 position;       // ����ǰ��λ��
    CardZone zone;
};
/**
 * @brief ������������ģ���ࣨ��ѭMVC�ܹ���models��淶��
 *
 * @ְ��
 * 1. ͨ��`record`������¼���Ʋ���ǰ��״̬��λ�á����򣩣�����ΪUndoCardState�ṹ�壻
 * 2. ͨ��`undo`������ȡ���һ�β�����״̬��֧�ְ�"����ȳ�"˳��ָ���ʷ��
 * 3. �ṩ`clearHistory`��`canUndo`����������ʷ��¼�������ڣ�������˹��ܵĽ������󣨣���
 */
class UndoModel {
public:
    UndoModel() = default;


    void record(const UndoCardState& state) {
        _history.push_back(state);  // ׷�Ӳ������յ���ʷ
    }

    bool UndoModel::undo(UndoCardState& outState) {
        if (_history.empty()) {
            return false;  // ����ʷ�ɻ���
        }
        // ȡ�����һ�β�����״̬
        outState = _history.back();
        // ����ʷ���Ƴ������ˣ�
        _history.pop_back();
        return true;
    }

    void UndoModel::clearHistory() {
        _history.clear();  // ������п���
    }

    /**
     * @brief ����Ƿ��пɻ��˵Ĳ���
     */
    bool canUndo() const { return !_history.empty(); }

    int getSize() const { return _history.size(); }

private:
    std::vector<UndoCardState> _history;  // ������ʷ����ʱ��˳��洢������ʱ���򵯳���
};

#endif // UNDO_MODEL_H_