#ifndef COMMON_WINDOWSYSTEM_H
#define COMMON_WINDOWSYSTEM_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include <map>
#include <string>
#include <vector>

namespace common::coreModule {
	class windowBase;

	class windowSystem : public cocos2d::Node {
	public:
		windowSystem();
		~windowSystem() = default;

		CREATE_FUNC(windowSystem);
		void registerWindow(const std::string&, const std::function<windowBase*()>&);
		bool requestWindow(const std::string&, bool force = false);

	private:
		std::map<std::string, std::function<windowBase*()>> registeredWindowList;
		std::vector<windowBase*> windowList;
	};
}//common::coreModule


#endif //COMMON_WINDOWSYSTEM_H