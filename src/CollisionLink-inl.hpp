#ifndef __COLLISION_LINK_INL_HPP
#define __COLLISION_LINK_INL_HPP
#include "CollisionLink.hpp"

/**
 * Default constructor
 */
template <typename S>
CollisionLink<S>::CollisionLink(){}

/**
 * Use this constructor
 * 
 */
template <typename S>
CollisionLink<S>::CollisionLink(int firstlink, int secondlink)
    :  link1(firstlink), link2(secondlink)
{
    robot_model = RobotModel::GetRobotModel(); 
}

/**
 * Default Constructor
 */
template <typename S>
CollisionLink<S>::~CollisionLink(){}

/**
 * Main function to call
 */
template<typename S>
fcl::CollisionObject<S>* CollisionLink<S>::computeCollisionObject(sejong::Vector& robot_q, int linkType) {
    // Get positions
    sejong::Vect3 joint1Pos;
    sejong::Vect3 joint2Pos;
    robot_model->getPosition(robot_q, link1, joint1Pos);
    robot_model->getPosition(robot_q, link2, joint2Pos);

    // Get orientations
    sejong::Quaternion joint1Orien;
    sejong::Quaternion joint2Orien;
    robot_model->getOrientation(robot_q, link1, joint1Orien);
    robot_model->getOrientation(robot_q, link2, joint2Orien);

    // Distance between joints
    double dist = calcDistance(joint1Pos, joint2Pos);

    // Create a shape based on what type of appendage we have
    if(linkType == collisionLinkType::CLT_appendage_arm){
        collisionShape = std::make_shared<fcl::Cylinder<S> >(armWidth, dist);
    }
    else if(linkType == collisionLinkType::CLT_appendage_leg){
        collisionShape = std::make_shared<fcl::Cylinder<S> >(legWidth, dist);
    }
    else{
        collisionShape = std::make_shared<fcl::Box<S> >(torsoWidth, torsoWidth, dist);
    }

    // Populate transform (TODO doesn't include orientation)
    collisionTran = fcl::Translation3<S>(joint1Pos);

    // TODO, this is really ugly but directly make shared doesn't work
    std::shared_ptr<fcl::CollisionGeometry<S>> temp(collisionShape.get()); 
    collisionGeo = temp;
    collisionGeo->setUserData(this);

    collisionObj = std::make_shared<fcl::CollisionObject<S>>(collisionGeo, collisionTran);
    collisionObj->setUserData(this);

    return collisionObj.get();
}



#endif
