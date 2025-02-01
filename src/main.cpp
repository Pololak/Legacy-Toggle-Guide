#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>

class $modify(PolzEditorUI, EditorUI) {
	struct Fields {
		std::set<int>gameModePortals_ids = {13, 47, 111, 660, 1331, 1933};
		std::set<int>speedPortals_ids = {200, 201, 202, 203, 1334};
	};

	void onCustomToggleGuide(CCObject*) {
		if (this->getSelectedObjects()->count()) {
			auto obj = reinterpret_cast<EffectGameObject*>(this->m_selectedObject);
			obj->m_shouldPreview = !obj->m_shouldPreview;
			this->m_editorLayer->tryUpdateSpeedObject(obj, false);
		}
	}

	bool init(LevelEditorLayer* editorLayer) {
		if (!EditorUI::init(editorLayer)) return false;
		
		auto editorButtonsMenu = this->getChildByID("editor-buttons-menu");

		auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");

		auto toggleGuide = CCMenuItemToggler::create(toggleOn, toggleOff, this, menu_selector(PolzEditorUI::onCustomToggleGuide));
		toggleGuide->setID("polz-preview-toggle"_spr);
		toggleGuide->setVisible(0);
		editorButtonsMenu->addChild(toggleGuide);
		editorButtonsMenu->updateLayout();
		toggleGuide->setPosition({m_editHSVBtn->getPosition().x - 38.5f, m_editHSVBtn->getPosition().y - 3.f});

		return true;
	}

	void updateButtons() {
		EditorUI::updateButtons();

		auto editorButtonsMenu = this->getChildByID("editor-buttons-menu");
		if (editorButtonsMenu) {
			auto toggleGuide = static_cast<CCMenuItemToggler*>(editorButtonsMenu->getChildByID("polz-preview-toggle"_spr));
			if (toggleGuide) {
				if (this->getSelectedObjects()->count() == 1 && (m_fields->gameModePortals_ids.contains(this->m_selectedObject->m_objectID) || m_fields->speedPortals_ids.contains(this->m_selectedObject->m_objectID))) {
						toggleGuide->setVisible(1);
				}
				else {
						toggleGuide->setVisible(0);
				}
				if (reinterpret_cast<EffectGameObject*>(this->m_selectedObject)) {
					toggleGuide->toggle(reinterpret_cast<EffectGameObject*>(this->m_selectedObject)->m_shouldPreview == 0);
				}
			}
		}
	}

	// Idk why i started recreating 1.9-2.1 function xd, im so strange

	// void toggleGuideButton() {
	// 	m_fields->bVar2 = false;
	// 	m_fields->local_8 = 0;
	// 	if (this->m_selectedObject != nullptr) {
	// 		m_fields->iVar1 = this->m_selectedObject->m_objectID;
	// 		if (m_fields->iVar1 < 0xcc) {
	// 			if (((m_fields->iVar1 < 200) && (m_fields->iVar1 != 0xd)) && ((m_fields->iVar1 != 0x2f && (m_fields->iVar1 != 0x6f)))) PolzEditorUI::lab_00479126();
	// 		}
	// 		else if (((m_fields->iVar1 != 0x294) && (m_fields->iVar1 != 0x533)) && (m_fields->iVar1 != 0x536)) PolzEditorUI::lab_00479126();
	// 		m_fields->bVar2 = true;
	// 		m_fields->local_8 = 1;
	// 	} 
	// }

	// void lab_00479126() {
	// 	auto editorButtonsMenu = this->getChildByID("editor-buttons-menu");
	// 	if (editorButtonsMenu)
	// 	{
	// 		auto toggleGuide = static_cast<CCMenuItemToggler *>(editorButtonsMenu->getChildByID("polz-preview-toggle"_spr));
	// 		if (toggleGuide)
	// 		{
	// 			toggleGuide->m_bVisible = m_fields->local_8;
	// 			if (m_fields->bVar2) {
	// 				toggleGuide->toggle(reinterpret_cast<EffectGameObject*>(this->m_selectedObject)->m_shouldPreview == 0);
	// 			}
	// 		}
	// 	}
	// }
};