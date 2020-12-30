#include "settingManager.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include "common/debugModule/logManager.h"

using namespace common::coreModule;

settingManager::settingManager() {

}

void settingManager::load() {
	auto defaultResolution = new sDisplaySize("default", 1024.f, 768.f, 1.f);

	// load json
	const std::string &regionStr = cocos2d::FileUtils::getInstance()->getStringFromFile("config/setting.json");
	rapidjson::Document doc;
	doc.Parse<0>(regionStr.c_str());

	if (doc.HasParseError()) {
		LOG_ERROR("settingManager::load: json parse error");
		allResolutions.insert({defaultResolution->resolutionName, defaultResolution});
		return;
	}

	if (doc.IsNull()) {
		LOG_ERROR("settingManager::load: json is empty");
		allResolutions.insert({defaultResolution->resolutionName, defaultResolution});
		return;
	}

	for (auto it = doc.GetObjectJ().begin(); it != doc.GetObjectJ().end(); ++it) {
		auto resName = it->name.GetString();
		auto currentResolution = new sDisplaySize();
		currentResolution->resolutionName = resName;
		for (auto resIt = it->value.GetObjectJ().begin(); resIt != it->value.GetObjectJ().end(); ++resIt) {
			if (!resIt->name.IsString()) {
				continue;
			}
			auto key = std::string(resIt->name.GetString());
			if (key == "width" && resIt->value.IsNumber()) {
				currentResolution->size.width = resIt->value.GetInt();
			} else
			if (key == "height" && resIt->value.IsNumber()) {
				currentResolution->size.height = resIt->value.GetInt();
			} else
			if (key == "desktopScale" && resIt->value.IsNumber()) {
				currentResolution->scale = resIt->value.GetFloat();
			} else
			if (key == "parent" && resIt->value.IsString()) {
				currentResolution->parentName = resIt->value.GetString();
			} else
			if (key == "path" && resIt->value.IsString()) {
				currentResolution->path = resIt->value.GetString();
			} else
			if (key == "showDisplayStats" && resIt->value.IsBool()) {
#ifdef DEBUG
				currentResolution->showStats = resIt->value.GetBool();
#else
				currentResolution->showStats = false;
#endif
			}
		}
		allResolutions.insert({resName, currentResolution});
	}

	if (allResolutions.empty()) {
		LOG_ERROR("settingManager::load: no data in json file!");
		allResolutions.insert({defaultResolution->resolutionName, defaultResolution});
		return;
	}
}
