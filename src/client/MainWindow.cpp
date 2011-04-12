#include "MainWindow.h"
#include <QScrollArea>
#include <QSize>
#include "map.h"
#include "maprenderer.h"
#include "../audio/manager.h"
#include "../graphics/GraphicsComponent.h"
#include "../graphics/MapDisplayer.h"
#include "../util/DelayedDelete.h"
#include <QLabel>

namespace td {

MainWindow::MainWindow() : QMainWindow() {
    scene_ = new QGraphicsScene();
    view_ = new QGraphicsView(scene_);

    scene_->setItemIndexMethod(QGraphicsScene::NoIndex);
    keysHeld_ = 0;
    keysTimer_ = new QTimer(this);
    keysTimer_->start(50);

    view_->setFocusPolicy( Qt::NoFocus );
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->releaseKeyboard();

    //MapDisplayer * mapDisplayer_ = NULL;
    mapDisplayer_ = new MapDisplayer(scene_);
    mapDisplayer_->viewMap(QString("./maps/netbookmap3.tmx"));
    Tiled::MapRenderer* mRenderer = mapDisplayer_->getMRenderer();
    QSize mapSize = mRenderer->mapSize();

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);    
    this->setCentralWidget(view_);
    scene_->setSceneRect(0,0,mapSize.width(), mapSize.height());
    view_->setFixedSize(mapSize.width(), mapSize.height());
    //this->showFullScreen();
    
    // This focus policy may be implied by default...
    this->setFocusPolicy(Qt::StrongFocus);
    //this->grabKeyboard();

    connect(keysTimer_, SIGNAL(timeout()), this, SLOT(keyHeld()));
}

MainWindow::~MainWindow() {
    /* driver_.shutdown() or something */
}

void MainWindow::createGraphicRepr(GraphicsComponent* gc) {
    scene_->addItem(gc->initGraphicsComponent());
}

void MainWindow::removeGraphicRepr(GraphicsComponent* gc) {
    scene_->removeItem(gc->getPixmapItem());
    new DelayedDelete<GraphicsComponent>(gc);
}

void MainWindow::drawItem(DrawParams* dp, GraphicsComponent* gc, int layer) {
    gc->draw(dp,layer);
}

void MainWindow::keyHeld()
{

    if(keysHeld_ & KEYUP && keysHeld_ & KEYDOWN) {
        emit signalKeyReleased(Qt::Key_Up);
        emit signalKeyReleased(Qt::Key_Down);
        return;
    } else if(keysHeld_ & KEYLEFT && keysHeld_ & KEYRIGHT) {
        emit signalKeyReleased(Qt::Key_Left);
        emit signalKeyReleased(Qt::Key_Right);
        return;
    }

    if(keysHeld_ & KEYUP) {
        emit signalKeyPressed(Qt::Key_Up);
    }
    if(keysHeld_ & KEYDOWN) {
        emit signalKeyPressed(Qt::Key_Down);
    }
    if(keysHeld_ & KEYLEFT) {
        emit signalKeyPressed(Qt::Key_Left);
    }
    if(keysHeld_ & KEYRIGHT) {
        emit signalKeyPressed(Qt::Key_Right);
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event) {

    if(event->isAutoRepeat()) {
        return;
    }

    switch (event->key()) {

        case Qt::Key_Space:
            emit signalSpacebarPressed();
            break;
        case Qt::Key_R:
            emit signalAltHeld(true);
            break;
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
        case Qt::Key_0:
            emit signalNumberPressed(event->key());
            break;

        case Qt::Key_Up:
            keysHeld_ |= KEYUP;
            break;
        case Qt::Key_Down:
            keysHeld_ |= KEYDOWN;
            break;
        case Qt::Key_Left:
            keysHeld_ |= KEYLEFT;
            break;
        case Qt::Key_Right:
            keysHeld_ |= KEYRIGHT;
            break;

        default:
            QMainWindow::keyPressEvent(event);
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent * event) {

    if(event->isAutoRepeat()) {
        return;
    }

    switch (event->key()) {

        case Qt::Key_Up:
            keysHeld_ ^= KEYUP;
            emit signalKeyReleased(event->key());
            break;
        case Qt::Key_Down:
            keysHeld_ ^= KEYDOWN;
            emit signalKeyReleased(event->key());
            break;
        case Qt::Key_Left:
            keysHeld_ ^= KEYLEFT;
            emit signalKeyReleased(event->key());
            break;
        case Qt::Key_Right:
            keysHeld_ ^= KEYRIGHT;
            emit signalKeyReleased(event->key());
            break;
        case Qt::Key_R:
            emit signalAltHeld(false);
            break;
        case Qt::Key_Space:
            emit signalSpacebarReleased();
    
        default:
            QMainWindow::keyPressEvent(event);
            break;
    }
}

} /* end namespace td */
