#ifndef NPC_H
#define NPC_H

#include <QVector2D>
#include <QEvent>
#include <QKeyEvent>

#include "Unit.h"
#include "Effect.h"

class NPC : public Unit {
    Q_OBJECT

public:
    /**
     * Gets the unique class index for this object type.
     *
     * @author Darryl Pogue
     * @return The class index.
     */
    static unsigned char clsIdx() {
        return td::clsidx::kNPC;
    }

public:
    NPC(InputComponent* input,PhysicsComponent* physics, GraphicsComponent* graphics);
    NPC();
    virtual ~NPC() {}

    virtual void update();
    size_t getHealth();
    void setHealth(size_t);
    size_t getDamage();
    void setDamage(size_t);

private:
    size_t health_;
    size_t damage_;
    QList<Effect*> effects_;
};

#endif // NPC_H
