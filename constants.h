#ifndef CONSTANTS_H
#define CONSTANTS_H

const int BLOCK_SIZE = 10;//场景中一个方格的尺寸

/**
 * @brief The GameObjectsData enum
 * 为场景中部件添加的额外属性
 */
enum GameObjectsData {
    GD_Type
};
/**
 * @brief The GameObjectTypes enum
 * 场景中属性的列表
 */
enum GameObjectTypes {
    GO_Food,    //食物
    GO_Wall,    //墙体
    GO_Snake    //蛇
};
#endif // CONSTANTS_H
