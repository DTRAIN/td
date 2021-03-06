#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QMutexLocker>
#include <QObject>
#include <QPointF>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "DrawParams.h"
#include "PixmapFiles.h"
#include "../client/MainWindow.h"
#include "../util/mutex_magic.h"
#include <QGraphicsTextItem>


#define OFFSCREEN -1000
#define LAYER_TOWER 1
#define LAYER_TOWER_TRI 2
#define LAYER_PLAYER 3
#define LAYER_NPC 4
#define LAYER_PROJECTILE 5
#define LAYER_FLYNPC 6
#define LAYER_MENU 7
#define LAYER_DEFAULT 0

namespace td {

class GameObject;

class GraphicsComponent : public QObject {
    Q_OBJECT

protected:
    /** The current index for the currently drawn pixmap. */
    int pixmapIndex_;

    /** Slows down how often the images animate from the timer. Should only be
     *  used in the graphics thread. */
    int animateMod_;

    /** The number of times the timer has ticked. */
    int animateCount_;

    /** If the obect is currently moving (used for animations). */
    bool isMoving_;

    /** True if the GameObject should currently be animate. */
    bool animate_;

    /** The pixelmapItem which is is used to draw a pixel map at a location. */
    QGraphicsPixmapItem* pixmapItem_;

    /** The rectangle for the last rectangle created by switching images */
    QRectF graphicsRect_;

private:
    /** copy of the last used states to limit unnecessary calls */
    DrawParams oldDP_;

public:
    /**
     * Sets up the necessary signals and slots to create the 
     * QGraphicsPixmapItem for this component in the rendering thread. This
     * is done to ensure that updates on the pixmap item are thread-safe.
     *
     * @author Dean Morin, Warren Voelkl
     */
    GraphicsComponent();

    virtual ~GraphicsComponent();
    
    /**
     * Safely deletes the graphics component. It must be deleted after all
     * events related to it are cleared from the graphics thread event queue.
     * 
     * @author Dean Morin
     */
    virtual void deleteComponent();

    /**
     * This is where all animation logic will be implemented. If this version
     * is ever called, then the calling subclass has no animation method, so
     * animate_ is set to false.
     *
     * @author Warren Voelkl
     * @author Dean Morin
     */
    virtual void animate() { 
        animate_ = false;
    }

    /**
     * For each GraphicsComponent update function
     * 1. check for dirty value
     * 2. Instantiate DrawParams structure
     * 3. load only the modifiable values of structure rest will be set to a 
     * default.
     * @author Warren Voelkl
     */
    virtual void update(GameObject* obj) = 0;

    /**
     * Resets the matrix then builds the transformation matrix from the
     * structure values.
     *
     * @author Warren Voelkl, Terence Stenvold
     * @param dp Pointer to the drawstruct that contains all the values on how
     * to render an image.
     * @param layer is what layer to draw image defaults to 0
     */
    virtual void draw(void * dp, int layer=0);

    /**
     * Called from main. instantiates the QGRaphicsPixmapItem
     * @author Warren Voelkl
     */
    QGraphicsPixmapItem* initGraphicsComponent();

    /**
     * the function where the pixmap container is loaded
     * called on construction of the object but not in the constructor
     * @author Warren Voelkl
     */
    virtual void initPixmaps() = 0;

    /**
     * returns the current pixmap image pointed to from the pixmapimg
     * @author Warren Voelkl
     */
    QPixmap getCurrentPixmap();
    
    /**
     * Gets the graphics item that can only be changed in the graphics thread.
     *
     * @author Dean Morin
     * @return The graphics item used by this object.
     */
    QGraphicsPixmapItem* getPixmapItem() {
        return pixmapItem_;
    }

    /**
     * updates the img index
     * @author Warren Voelkl
     **/
    void setImgIndex(int index);

    /**
     * @returns the pixmap array from the subclasses
     */
    virtual QPixmap* getPixmapArray() = 0;

    
signals:
    void created(GraphicsComponent* gc);
    void signalDraw(void *, GraphicsComponent* gc, int layer);

    /**
     * Lets the graphics thread know that this object should be deleted.
     * Connected to removeGraphicRepr in MainWindow.
     *
     * @author Dean Morin
     * @param gc The graphics component to be deleted
     */
    void removeGraphicsItem(GraphicsComponent* gc);
};

} /* end namespace td */

#endif
