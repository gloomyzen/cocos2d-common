#ifndef MERCENARY_BATTLES_ARMATUREHOLDERNODE_H
#define MERCENARY_BATTLES_ARMATUREHOLDERNODE_H

#include "cocos2d.h"
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"
#include <vector>

namespace mb {
	namespace coreModule {
		using namespace cocos2d;
		using namespace dragonBones;

		class armatureHolderNode : public Node {
		public:
			static Node* createNode() {
				return armatureHolderNode::create();
			}

			virtual bool init() {
				if(!Node::init())
				{
					return false;
				}

				return true;
			}

			CREATE_FUNC(armatureHolderNode);

			void addArmature(CCArmatureDisplay* armature) {
				_armatureList.emplace_back(armature);
				addChild(armature);
			}
			std::vector<CCArmatureDisplay*> getArmatureList() {
				return _armatureList;
			}
		private:
			std::vector<CCArmatureDisplay*> _armatureList{};
		};
	}
}

#endif //MERCENARY_BATTLES_ARMATUREHOLDERNODE_H
