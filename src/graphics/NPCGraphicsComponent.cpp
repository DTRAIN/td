#include "NPCGraphicsComponent.h"
#include "../engine/NPC.h"
#include "../engine/CDriver.h"

namespace td {

QPixmap * NPCGraphicsComponent::pixmapImgs_ = 0;
bool NPCGraphicsComponent::keyHeld_ = false;

NPCGraphicsComponent::NPCGraphicsComponent()
        : GraphicsComponent(), damageDisplayTime_(0) {
    //emit created(this);
}

NPCGraphicsComponent::~NPCGraphicsComponent() {
    delete healthbarItem_;
    disconnect(this);
}

void NPCGraphicsComponent::update(GameObject* obj) {
    NPC* npc = (NPC*)obj;
    if (!npc->isDirty()) {
        return;
    }
    npc->resetDirty();

    DrawParams* dp = new DrawParams();
    dp->pos     = npc->getPos();
    dp->moving  = 1;
    dp->degrees = npc->getOrientation();
    npcHealth   = (npc->getHealth() / (double)npc->getMaxHealth());
    //npcHealth   = npcHealth - 0.003; //This and the following lines are for tests.
    if(npcHealth < 0) {
        npcHealth = 0;
    }
    
    setLayer(dp);
}

void NPCGraphicsComponent::draw(DrawParams* dp, int layer) {

    if (--damageDisplayTime_ > 0 || keyHeld_) {
        healthbarItem_->setVisible(true);
        healthbarItem_->setRect(QRectF(0, 0, HEALTHBAR_WIDTH * npcHealth, 
                                       HEALTHBAR_HEIGHT));
        if(npcHealth > 0.25 && npcHealth < 0.51) {
            healthbarItem_->setBrush(QBrush(Qt::yellow));
        } else if (npcHealth <= 0.25) {
            healthbarItem_->setBrush(QBrush(Qt::red));
        } else {
            healthbarItem_->setBrush(QBrush(Qt::green));
        }
        healthbarItem_->setPos((dp->pos.x()
                    - healthbarItem_->boundingRect().center().x()),
                    (dp->pos.y()
                    - (getPixmapItem()->boundingRect().height())/2));
        healthbarItem_->setZValue(layer);
        healthbarItem_->update();
    } else {
        healthbarItem_->setVisible(false);
        healthbarItem_->update();
    }

    GraphicsComponent::draw(dp, layer);
}

void NPCGraphicsComponent::initHealthbar() {
    healthbarItem_ = new QGraphicsRectItem(QRectF(OFFSCREEN, OFFSCREEN,
                                           HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT));
    npcHealth = 1;
    CDriver::instance()->getMainWindow()->getScene()->addItem(healthbarItem_);
}

void NPCGraphicsComponent::showHealth(bool keyHeld) {
    keyHeld_ = keyHeld;
}

void NPCGraphicsComponent::showDamage() {
    damageDisplayTime_ = DAMAGE_DISPLAY_TIME;
}

QPixmap * NPCGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

void NPCGraphicsComponent::animate() {
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ > arrayIndexMax_ ? pixmapIndex_ = arrayIndexMin_
            : pixmapIndex_;
        setImgIndex(pixmapIndex_);

    }
}

} /* end namespace td */
