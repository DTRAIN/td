#ifndef CDRIVER_H
#define CDRIVER_H

#include <QTimer>
#include <QPointF>
#include "ContextMenu.h"
#include "GameObject.h"
#include "Map.h"
#include "NPC.h"
#include "Player.h"
#include "Projectile.h"
#include "ResManager.h"
#include "Tower.h"
#include "../client/MainWindow.h"

namespace td {

class CDriver : public QObject {
    Q_OBJECT
  
private:
    /** The game object resource manager. */
    ResManager* mgr_;
    /** The central game timer that initiates all object updates. */
    QTimer* gameTimer_;
    /** The player on this client. */
    Player* human_;
    /** The main game window, where all graphics will be drawn. */
    MainWindow* mainWindow_;
    /** The game map containing all the tiles, waypoints, and access methods. */
    Map* gameMap_;
    /** A context menu that appears around the player. */
    ContextMenu* contextMenu_;
    /** An enemy unit. */
    NPC* npc_;
    /** A projectile fired from a tower. */
    Projectile* projectile_;
    /** A tower built by the players. */
    Tower* tower_;

public:
    CDriver(MainWindow* parent = 0);
    ~CDriver();

    /**
     * Connects the client driver to the server. This must be called
     * at some point before the updateServer() method is ever called,
     * as it creates the stream that updateServer() uses to push updates
     * to the server.
     * 
     * @author Duncan Donaldson
     */
    void connectToServer(const QString& servaddr);

    /**
     * Disconnects the client driver from the server,
     * and destroys the stream used to update the server, call this on cleanup.
     * 
     * @author Duncan Donaldson
     */
    void disconnectFromServer();

    /**
     * Sends client updates to the server, static method, this
     * call this method from the update() function of the GameObject
     * whose state you want to send to the server.
     * 
     * @author Duncan Donaldson
     * @param obj The GameObject to transmit.
     */
    static void updateServer(GameObject* obj);

    /**
     *
     * @author Duncan Donaldson
     */
    void readObject(Stream* s);

    /**
     * Creates a human player object.
     * Sets event filter for key presses to be passed to PlayerInputComponent.
     * 
     * @author Tom Nightingale
     * @author Duncan Donaldson
     * @author Darryl Pogue
     * @return pointer to new player instance.
     */
    void createHumanPlayer(MainWindow *);

    /**
     * creates npc object
     * @author Marcel Vangrootheest
     */
    void createNPC();

    /**
     * Stop game timer.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void endGame();
    
public slots:
    /**
    * Initialize and start game timer.
    * [Hijacked and updated by Tom Nightingale] 
    * Client side objects are created here.
    *
    * @author Duncan Donaldson
    * @return void
    */
    void startGame();

private slots:
    /**
     * Creates a projectile object.
     *
     * @author Pan Khantidhara
     * @param int A key pressed. Doesn't really use it.
     * @return Pointer to new projectile instance.
     */
    void createProjectile();

    /**
     * Temp testing method.
     *
     * @author Dean Morin
     */
    void createTower(int towerType, QPointF pos);

    /**
     *
     * @author Duncan Donaldson
     */
    void UDPReceived(Stream* s);
};

} /* end namespace td */

#endif
