#include "mainScene.h"
#include "debugModule/logManager.h"
#include "debugModule/imGuiLayer.h"
#include "coreModule/gameManager.h"
#include "coreModule/scenes/scenesFactory/scenesFactoryInstance.h"

using namespace mb::coreModule;
using namespace cocos2d;

Scene *mainScene::createScene() {
	return mainScene::create();
}

bool mainScene::init() {
	if (!Scene::init()) {
		return false;
	}
	LOG_INFO("mainScene::init()");

#ifdef DEBUG
	/// insert debug layer
	auto imGuiLayer = mb::debugModule::imGuiLayer::create();
	this->addChild(imGuiLayer, eGameLayers::DEBUG_LAYER);
#endif

	return true;
}

void mainScene::menuCloseCallback(Ref *pSender) {
	Director::getInstance()->end();
}

void mainScene::setRoom(eGameStates state) {
	auto director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();
	if (nodes.empty()) {
		auto currentNode = scenesFactoryInstance::getInstance().getStateRoot(state);
		this->addChild(currentNode, eGameLayers::ROOT);
		nodes.push_back(currentNode);
		return;
	}
	nodes.reserve(2);

	nodes.front()->setLocalZOrder(nodes.front()->getLocalZOrder() - 1);
	auto nextNode = scenesFactoryInstance::getInstance().getStateRoot(state);
	nextNode->setCascadeOpacityEnabled(true);
	nextNode->setOpacity(0);
	auto seq = Sequence::create(FadeIn::create(0.5f), CallFunc::create([this](){
		nodes.front()->removeFromParentAndCleanup(true);
		nodes.erase(nodes.begin());
	}), nullptr);
	nextNode->setContentSize(visibleSize);
	this->addChild(nextNode, eGameLayers::ROOT);
	nodes.push_back(nextNode);
	nextNode->runAction(seq);
	director->getRunningScene()->getDefaultCamera()->setPosition(visibleSize.width/2, visibleSize.height/2);
}