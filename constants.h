#ifndef CONSTANTS_H
#define CONSTANTS_H

const int BLOCK_SIZE = 10;//������һ������ĳߴ�

/**
 * @brief The GameObjectsData enum
 * Ϊ�����в�����ӵĶ�������
 */
enum GameObjectsData {
    GD_Type
};
/**
 * @brief The GameObjectTypes enum
 * ���������Ե��б�
 */
enum GameObjectTypes {
    GO_Food,    //ʳ��
    GO_Wall,    //ǽ��
    GO_Snake    //��
};
#endif // CONSTANTS_H
