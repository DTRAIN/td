#ifndef BUILDINGTOWERGRAPHICSCOMPONENT_H
#define BUILDINGTOWERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"
#include "./util/defines.h"

#define ICON_MAX 3

namespace td {

struct DrawParamsBuildTower {
    /** location */
    QPointF pos;
    /** in degrees 0 is up 180 down... */
    int degrees;
    /** normal is 1 .5 is half 2 is double */
    float scale;
    /** true if animate() should be called to set the current image. */
    bool animate;
    /** movement for animation projectiles get bigger/smaller during arc */
    bool moving;
    /** index of pixmap image to use */
    int pixmapIdx;
    /** current number of wood to display */
    int wood;
    /** current number of stone to display */
    int stone;
    /** current number of bone to display */
    int bone;
    /** current number of oil to display */
    int oil;
    /** current building tower stage to display */
};

class BuildingTowerGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a Tower graphics component
     * @author Warren Voelkl
     */
    BuildingTowerGraphicsComponent();
    virtual ~BuildingTowerGraphicsComponent();

    /**
     * Loads a structure from the item and game component class then sends
     * the structure to the generic draw slot in GraphicsComponent.
     *
     * @author Warren Voelkl
     */
    void update(GameObject* obj);

    /**
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelkl
     */
    void initPixmaps();

    /**
     * Sets the currently dispalyed graphics item for the current stage
     * @param i the current building stage
     * @author Warren Voelkl
     */
    void setBuildingStage(int i);

    /**
     * Draw functions that displays icons on top of tower when r is pressed
     * @author Warren Voelkl
     */
    virtual void draw(void* dp, int layer=0);

private:
    /** container for all pixmaps which pertain to the current object */
    static QPixmap * pixmapImgs_;

    /** arragy of pix map items for the required resources **/
    QGraphicsPixmapItem* resourcePixmapItemArray_[RESOURCE_TYPE_MAX][ICON_MAX];

    /** The current building stage of the graphics component */
    int buildingStage_;

    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    QPixmap * getPixmapArray() {
        return pixmapImgs_;
    }

    /**
     * Sets the default images and visibilities for all the tower icons.
     * @author Warren Voelkl
     */
    void setIconImages();

    /**
     * Sets or unsets visibility of icon.
     *
     * @param iconGraphic current graphics item being evaluated
     * @param index current index to be shown
     * @param current number of resources required for tower completing
     * @author Warren Voelkl
     */
    void setIconVisibility(QGraphicsPixmapItem *iconGraphic, int index,
            int resourceReq);
    /**
     * Sets the position and scale for each icon
     * @param icon the current icon being set
     * @param x the x position of parent
     * @param y the y position of parent
     * @param layer draw icons above tower
     * @param i used to determine y offset of each icon
     * @author Warren Voelkl
     */
    void iconDrawingHelper(QGraphicsPixmapItem *icon, int x, int y,
            int layer, int i);
    /**
     * Updates the current graphic to represent the current building stage
     * @param gpi the graphics pixmap item for wich the image is being set
     * @author Warren Voelkl
     */
    void setBuildingGraphic(QGraphicsPixmapItem * gpi);
};

} /* end namespace td */

#endif

