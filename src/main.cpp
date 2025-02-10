#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>

class $modify(PolzEditorUI, EditorUI) {

	static void onModify(auto& self) {
        (void) self.setHookPriorityPost("EditorUI::init", Priority::Late);
    }

	struct Fields {
		std::set<int> m_portalIDs = {13, 47, 111, 660, 1331, 1933, 200, 201, 202, 203, 1334};
		CCMenuItemToggler* m_toggleGuide;
	};

	void onCustomToggleGuide(CCObject*) {
		auto fields = m_fields.self();

		if (EffectGameObject* object = typeinfo_cast<EffectGameObject*>(this->m_selectedObject)) {
			if (!fields->m_portalIDs.contains(this->m_selectedObject->m_objectID)) return;
			object->m_shouldPreview = !object->m_shouldPreview;
			fields->m_toggleGuide->toggle(object->m_shouldPreview);
			this->m_editorLayer->tryUpdateSpeedObject(object, false);
		}
	}

	void fillPaddingButtons() {
		auto fields = m_fields.self();

		auto editorButtonsMenu = this->getChildByID("editor-buttons-menu");
		int childrenCount = editorButtonsMenu->getChildrenCount();
		int padAmount = 16 - childrenCount - 1;

		for (int i = 0; i < padAmount; i++) {
			CCNode* paddingNode = CCNode::create();
			paddingNode->setID("padding"_spr);
			paddingNode->setContentSize({40, 40});
			editorButtonsMenu->addChild(paddingNode);
		}
	}

	bool init(LevelEditorLayer* editorLayer) {
		if (!EditorUI::init(editorLayer)) return false;

		auto fields = m_fields.self();
		
		auto editorButtonsMenu = this->getChildByID("editor-buttons-menu");

		fields->m_toggleGuide = CCMenuItemToggler::createWithStandardSprites(this, nullptr, 1);
		auto toggleGuideContainer = CCMenuItemSpriteExtra::create(fields->m_toggleGuide, this, menu_selector(PolzEditorUI::onCustomToggleGuide));

		toggleGuideContainer->setID("polz-preview-toggle"_spr);

		fields->m_toggleGuide->setVisible(false);
		fields->m_toggleGuide->setPositionX(fields->m_toggleGuide->getPositionX() - 1);
		toggleGuideContainer->setContentSize({40, 40});

		fillPaddingButtons();

		editorButtonsMenu->addChild(toggleGuideContainer);

		if (editorButtonsMenu->getChildrenCount() > 15) {
			CCNode* child15 = static_cast<CCNode*>(editorButtonsMenu->getChildren()->objectAtIndex(15));
			editorButtonsMenu->swapChildIndices(toggleGuideContainer, child15);
		}

		editorButtonsMenu->updateLayout();

		return true;
	}

	void updateButtons() {
		EditorUI::updateButtons();
		auto fields = m_fields.self();

		if (!fields->m_toggleGuide) return;

		if (EffectGameObject* object = typeinfo_cast<EffectGameObject*>(this->m_selectedObject)) {
			if (!fields->m_portalIDs.contains(m_selectedObject->m_objectID)) return;
			fields->m_toggleGuide->toggle(object->m_shouldPreview);
			fields->m_toggleGuide->setVisible(true);
		}
		else {
			fields->m_toggleGuide->setVisible(false);
		}
	}
};
