#include "gameManager.h"
#include "coreModule/scenes/mainScene.h"
#include "debugModule/logManager.h"

using namespace mb;
using namespace mb::coreModule;

gameManager *currentGameManager = nullptr;

gameManager::gameManager() {
	currentState = eGameStates::LOADING_SCREEN;
	mainSceneIns = dynamic_cast<mainScene *>(mainScene::createScene());
};

gameManager::~gameManager() = default;

gameManager &gameManager::getInstance() {
	if (currentGameManager == nullptr) {
		currentGameManager = new gameManager();
	}
	return *currentGameManager;
}

void gameManager::run(eGameStates state) {
	/// Starting from state
	changeState(state);
	Director::getInstance()->runWithScene(mainSceneIns);

	//todo remove after testing
//	auto seq = Sequence::create(DelayTime::create(7.f), CallFunc::create([this](){
//		changeState(eGameStates::BATTLE_SCENE);
//	}), nullptr);
//	mainSceneIns->runAction(seq);

//	auto seq = Sequence::create(DelayTime::create(7.f), CallFunc::create([this](){
//		changeState(eGameStates::BATTLE_SCENE);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::MAIN_MENU);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::BATTLE_SCENE);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::MAIN_MENU);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::BATTLE_SCENE);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::MAIN_MENU);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::BATTLE_SCENE);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::MAIN_MENU);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::BATTLE_SCENE);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::MAIN_MENU);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::BATTLE_SCENE);
//	}),DelayTime::create(5.f), CallFunc::create([this](){
//		changeState(eGameStates::MAIN_MENU);
//	}), nullptr);
//	mainSceneIns->runAction(seq);

}

void gameManager::changeState(eGameStates state) {
	if (mainSceneIns == nullptr) {
		LOG_ERROR("gameManager::changeState Instance mainSceneIns is null!");
		return;
	}
	currentState = state;
	mainSceneIns->setRoom(currentState);
}
