#include "Chapter14.h"

#include <SimpleAudioEngine.h>

USING_NS_CC;

Scene* Chapter14::createScene()
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a scene
    // 'scene' is an autorelease object
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto scene = Scene::create();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("grossini-aliases.plist");
    
    auto sprite = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
    sprite->setPosition(Vec2(100,100));
    scene->addChild(sprite);
    
    //add the first frame of animation
    auto spriteFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("grossini_dance_02.png");
    
    //animation frame with no event
    auto animationFrame1 = AnimationFrame::create(spriteFrame1, 0.08, ValueMap());
    
    auto spriteFrame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("grossini_dance_03.png");
    
    //animation frame with event
    ValueMap eventValueMap;
    eventValueMap["key1"] = Value(2);
    eventValueMap["key2"] = Value("Hello Event");
    
    auto animationFrame2 = AnimationFrame::create(spriteFrame2, 0.08, eventValueMap);
    
    
    Vector<AnimationFrame*> frames;
    frames.pushBack(animationFrame1->clone());
    frames.pushBack(animationFrame2->clone());
    eventValueMap["frame"] = Value(3);
    animationFrame1->setUserInfo(eventValueMap);
    frames.pushBack(animationFrame1);
    frames.pushBack(animationFrame2);
    auto animation = Animation::create(frames, 0.08);
    
    sprite->runAction(Animate::create(animation));
    
    //add custom event listener to
    auto eventListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [](EventCustom* event)
                                                     {
                                                         auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
                                                         auto valueMap = userData->userInfo;
                                                         if (valueMap->find("frame") != valueMap->end())
                                                         {
                                                             CCLOG("The %d frame played!", valueMap->at("frame").asInt());
                                                             //do whatever you want to after playing 3rd animation frame.
                                                             return;
                                                         }
                                                         CCLOG("key1 = %d, key2 = %s",valueMap->at("key1").asInt(), valueMap->at("key2").asString().c_str());
                                                     });
    
    scene->getEventDispatcher()->addEventListenerWithFixedPriority(eventListener, -1);
    
    
    // return the scene
    return scene;
}
