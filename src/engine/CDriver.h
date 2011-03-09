#ifndef CDRIVER_H
#define CDRIVER_H

#include <QTimer>
#include <QPointF>

namespace td {

class ContextMenu;
class GameObject;
class Map;
class NPC;
class Player;
class Projectile;
class ResManager;
class Tower;
class MainWindow;
class Stream;

class CDriver : public QObject {
    Q_OBJECT
  
private:
     /** The game object resource manager. */
    ResManager* mgr_;
     /** The central game timer that initiates all object updates. */
    static QTimer* gameTimer_;
     /** The player on this client. */
    Player* human_;
     /** The main game window, where all graphics will be drawn. */
    MainWindow* mainWindow_;
     /** The game map containing all tiles, waypoints, and access methods. */
    Map* gameMap_;
     /** A context menu that appears around the player. */
    ContextMenu* contextMenu_;
     /** An enemy unit. */
    NPC* npc_;
     /** A projectile fired from a tower. */
    Projectile* projectile_;
     /** A tower built by the players. */
    Tower* tower_;
     /** The single instance of this class that can be created. */
    static CDriver* instance_;
    
    
    CDriver(MainWindow* parent = 0);
    ~CDriver();

public:
    /**
     * Creates an instance of the class if one doesn't exist yet.
     *
     * @author Dean Morin
     * @param mainWindow A pointer to the main window where everything is drawn.
     * @returns An new instance of the class if one doesn't exist yet, or
     * if one does, it returns a pointer to that instance.
     */
    static CDriver* init(MainWindow* mainWindow);
   
    /**
     * Calls the dtor for the singleton instance.
     *
     * @author Dean Morin
     */
    static void shutdown();
   
    /**
     * Returns the instance of this Singleton class. Should only be used if
     * you know that init() has already been called.
     *
     * @author Dean Morin
     * @returns A pointer to the one available instance of this class.
     */
    static CDriver* instance() {
        return instance_;
    }

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

    /**
     * Returns the game timer
     *
     * @author Terence Stenvold
     * @return the game timer
     */
    static QTimer* getTimer();
    
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
