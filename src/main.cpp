#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include <algorithm>
#include <array>
#include <string>

using namespace geode::prelude;

namespace {

constexpr std::array<char const*, 20> kRoasts{
    "Skill issue.",
    "Have u considered being good",
    "{:.0f}% never stood a chance",
    "The checkpoint was right there",
    "That death was {:.0f}% avoidable",
    "practice mode is free. use it",
    "{:.0f}% and a dream. nothing more",
    "Genuinely impressive failure rate",
    "ur icon is fine. ur not.",
    "Only {:.0f}% away from giving up",
    "Have you tried the other button",
    "That one is on the level fr",
    "67%? okay that was just mean",
    "L. rubber-stamped.",
    "you jumped a little too much",
    "{:.0f}% fumbled",
    "try holding instead of tapping eh",
    "velocity is not your friend rn",
    "skill diff revealed at {:.0f}%",
    "mum says quit and go do homework",
};

size_t s_deathIdx = 0;

float playerPercent(PlayLayer* pl) {
    float const len = pl->m_levelLength;
    if (len <= 0.f) return 0.f;
    return std::clamp(pl->m_player1->getPositionX() / len * 100.f, 0.f, 100.f);
}

void showText(CCLabelBMFont* label, std::string const& text) {
    float const target = text.size() < 18 ? 0.55f : (text.size() < 34 ? 0.45f : 0.35f);
    label->setString(text.c_str());
    label->setVisible(true);
    label->stopAllActions();
    label->setOpacity(0);
    label->setScale(0.5f);
    auto pop = CCSpawn::create(
        CCEaseBackOut::create(CCScaleTo::create(0.30f, target)),
        CCFadeIn::create(0.20f),
        nullptr
    );
    label->runAction(CCSequence::create(
        pop,
        CCDelayTime::create(2.4f),
        CCFadeTo::create(0.30f, 0),
        nullptr
    ));
}

} // namespace

class $modify(SIRPlayLayer, PlayLayer) {
    struct Fields {
        CCLabelBMFont* m_label = nullptr;
    };

    void onEnterTransitionDidFinish() {
        PlayLayer::onEnterTransitionDidFinish();
        if (m_fields->m_label) {
            m_fields->m_label->removeFromParent();
            m_fields->m_label = nullptr;
        }
        if (Mod::get()->getSettingValue<bool>("show-overlay")) {
            auto label = CCLabelBMFont::create("", "bigFont.fnt");
            auto const win = CCDirector::get()->getWinSize();
            label->setPosition({ win.width / 2.f, win.height - 100.f });
            label->setZOrder(999);
            label->setOpacity(0);
            addChild(label);
            m_fields->m_label = label;
        }
    }

    void destroyPlayer(PlayerObject* p0, GameObject* p1) {
        PlayLayer::destroyPlayer(p0, p1);
        if (!m_player1->m_isDead) return;
        if (!m_fields->m_label || !Mod::get()->getSettingValue<bool>("show-overlay")) return;
        showText(
            m_fields->m_label,
            fmt::format(fmt::runtime(kRoasts[s_deathIdx++ % kRoasts.size()]), playerPercent(this))
        );
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        clearRoast();
    }

    void loadFromCheckpoint(CheckpointObject* p0) {
        PlayLayer::loadFromCheckpoint(p0);
        clearRoast();
    }

    void clearRoast() {
        if (m_fields->m_label) {
            m_fields->m_label->stopAllActions();
            m_fields->m_label->setOpacity(0);
        }
    }
};