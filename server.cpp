#include "server.h"

Server::Server()
{
    init();

    counter = new QElapsedTimer();
    loop = new QTimer();
    connect(loop, SIGNAL(timeout()), this, SLOT(onLoop()));

    TICKS_PER_SECOND = 1;
    SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    MAX_FRAMESKIP = 5;
    counter->start();
    next_game_tick = counter->elapsed();
    loop->start(0);

    QVariantMap map;
    map.insert("login", "kabanov");
    map.insert("password", "");
    map.insert("uids", "1,2");
    API::gi().request("users.getInfo", map);
}

Server::~Server()
{
    Console::print("Server has been deleted");
    delete p_server;
}

void Server::init()
{
    port = 560;
    p_server = new QTcpServer(this);
    if (!p_server->listen(QHostAddress::Any, port))
    {
        Console::print("Connection failed");
        p_server->close();
    }
    else
    {
        Console::print(QString("Server has started at port: ") + QVariant(port).toString());
    }
    connect(p_server, SIGNAL(newConnection()), this, SLOT(onClientConnected()));
}

void Server::onClientConnected()
{
    Console::print("Client connected");
    QTcpSocket* socket = p_server->nextPendingConnection();
    NetworkClient* player = new NetworkClient(socket);
    players.push_back(player);
}

void Server::onClientDisconnected()
{
    Console::print("Client disconnected");
}

void Server::broadcast(const QString& message)
{
    //Console::print(QString("Broadcast: "+message));
    for (std::vector<NetworkClient*>::iterator i = players.begin(); i != players.end();)
    {
        NetworkClient* current = *i;
        if (current->isValid())
        {
            current->send(message);
            ++i;
        }
        else
        {
            i = players.erase(i);
        }
    }
}

void Server::onLoop()
{
    int loops = 0;
    while (counter->elapsed() > next_game_tick && loops < MAX_FRAMESKIP)
    {
        tick(1.0 / TICKS_PER_SECOND);
        next_game_tick += SKIP_TICKS;
        loops++;
    }
}

void Server::tick(double dt)
{
    broadcast("Hello, clients!");
}
