// rabbits.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in the arena
const int MAXCOLS = 25;               // max number of columns in the arena
const int MAXRABBITS = 100;           // max number of rabbits allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int STILL = 4;
const int NUMDIRS = 4;

const int EMPTY      = 0;
const int HAS_POISON = 1;

const int RABBIT_OKAY = 0;      //rabbit not poisoned yet
const int RABBIT_POISONED = 1;  //rabbit poisoned once
const int RABBIT_DEAD = 2;      //rabbit dead

const int ATTEMPTED_LAST = 0;
const int NOT_ATTEMPTED_LAST = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Rabbit declaration.

class Rabbit
{
  public:
      // Constructor
    Rabbit(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_poison;
    int    m_movedlast;
};

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string dropPoisonedCarrot();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     rabbitCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfRabbitsAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addRabbit(int r, int c);
    bool addPlayer(int r, int c);
    void moveRabbits();

  private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Rabbit* m_rabbits[MAXRABBITS];
    int     m_nRabbits;
    int     m_turns;

      // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Rabbit implementation
///////////////////////////////////////////////////////////////////////////

Rabbit::Rabbit(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A rabbit must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Rabbit created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_poison = RABBIT_OKAY;
    m_movedlast = ATTEMPTED_LAST;
}

int Rabbit::row() const
{
    return m_row;
}

int Rabbit::col() const
{
    return m_col;
}

bool Rabbit::isDead() const            //if poison is 2 rabbit is dead
{
    if (m_poison >= RABBIT_DEAD){
        return true;}
    return false;
}

void Rabbit::move()                 //not double checked add
{
    int dir = randInt(0, 3);
    
    if(m_poison == RABBIT_POISONED){
        
        if(m_movedlast == NOT_ATTEMPTED_LAST){
            attemptMove(*m_arena, dir, m_row, m_col);
            if (m_arena->getCellStatus(row(), col()) == HAS_POISON){ //if cell has poison
                m_poison++;                                     //add poison to rabbit
                isDead();                                           //kills rabbit
                m_arena->setCellStatus(m_row, m_col, EMPTY);        //makes cell empty
            }
        }
        switch (m_movedlast) {
            case ATTEMPTED_LAST:
                m_movedlast = NOT_ATTEMPTED_LAST;
                break;
            case NOT_ATTEMPTED_LAST:
                m_movedlast = ATTEMPTED_LAST;
                break;
            default:
                break;
        }
    }
    
    if (m_poison == RABBIT_OKAY){
        attemptMove(*m_arena, dir, m_row, m_col);
        if (m_arena->getCellStatus(row(), col()) == HAS_POISON){ //if cell has poison
            m_poison++;                                     //add poison to rabbit
            isDead();                                           //kills rabbit
            m_arena->setCellStatus(m_row, m_col, EMPTY);//makes cell empty
        }
    }
    
    
    
    
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

string Player::dropPoisonedCarrot()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned carrot at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned carrot has been dropped.";
}

string Player::move(int dir)
{
    if (attemptMove(*m_arena, dir, m_row, m_col) == false){
        return "Player couldn't move; player stands.";
    }
    else if (m_arena->numberOfRabbitsAt(m_row, m_col) > 0){
        setDead();
        return "Player walked into a rabbit and died.";
    }
    else if (dir == NORTH)
        return "Player moved north.";
    else if (dir == EAST)
        return "Player moved east.";
    else if (dir == SOUTH)
        return "Player moved south.";
    else if (dir == WEST)
        return "Player moved west.";
    else
        return "Player couldn't move; player stands.";
    
  
       
      // TODO:  Attempt to move the player one step in the indicated
      //        direction.  If this fails,
      //        return "Player couldn't move; player stands."
      //        A player who moves onto a rabbit, and this
      //        returns "Player walked into a rabbit and died."
      //        Otherwise, return one of "Player moved north.",
      //        "Player moved east.", "Player moved south.", or
      //        "Player moved west."
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRabbits = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    delete m_player;
    for (int k = 0; k < m_nRabbits; k++)    //delete all things still alive
        delete m_rabbits[k];

}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::rabbitCount() const
{
    return m_nRabbits;
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r-1][c-1];
    
}

int Arena::numberOfRabbitsAt(int r, int c) const
{
    int count = 0;
    for(int k = 0; k < m_nRabbits; k++){   //if rabbits pos matches pos input add 1 to count
        if(m_rabbits[k]->row() == r && m_rabbits[k]->col() == c && !m_rabbits[k]->isDead())
            count++;
           }
      
    return count;       //return number of rabbits on that spot
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

      // Indicate each rabbit's position
    for (r = 1; r <= rows(); r++){
        for (c = 1; c <= cols(); c++){
            int num = numberOfRabbitsAt(r, c);  //rabbit use (1,1) identify top left
            if (num == 1)
               displayGrid[r-1][c-1] = 'R';
            if (num >= 2 && num <= 8)
                    displayGrid[r-1][c-1] = num + '0';
            if (num >= 9)
                    displayGrid[r-1][c-1] = '9' + '0';
               
        }
    }
    
      // Indicate the player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, rabbit, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << rabbitCount() << " rabbits remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r-1][c-1] = status;
}

bool Arena::addRabbit(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a rabbit on a spot with a poisoned carrot
    if (getCellStatus(r, c) != EMPTY)
        return false;

      // Don't add a rabbit on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;

    
    if (m_nRabbits >= MAXRABBITS)
        return false;
    
    Rabbit* rabbit = new Rabbit(this, r, c);   //dynamic allocating a new rabbit
    m_rabbits[m_nRabbits] = rabbit;            //if conditions permit
    m_nRabbits++;
      
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a rabbit
    if (numberOfRabbitsAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveRabbits()
{
      // Move all rabbits
    for (int k = 0; k < m_nRabbits; k++){
        m_rabbits[k]->move();
        if(m_rabbits[k]->row() == m_player->row() && m_rabbits[k]->col() == m_player->col())
            m_player->setDead();        //if player same spot rabbit, player is dead
        
        if(m_rabbits[k]->isDead()){     //if dead delete pointer and save memory
            delete m_rabbits[k];
            for(int j = k; j < m_nRabbits - 1; j++)
                m_rabbits[j] = m_rabbits[j+1];
            m_nRabbits--;
        }
        
    }
    
      // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRabbits)
{
    if (nRabbits < 0)
    {
        cout << "***** Cannot create Game with negative number of rabbits!" << endl;
        exit(1);
    }
    if (nRabbits > MAXRABBITS)
    {
        cout << "***** Trying to create Game with " << nRabbits
             << " rabbits; only " << MAXRABBITS << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nRabbits - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small too hold a player and "
             << nRabbits << " rabbits!" << endl;
        exit(1);
    }

      // Create arena
    m_arena = new Arena(rows, cols);

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with rabbits
    while (nRabbits > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addRabbit(r, c);
        nRabbits--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/c or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonedCarrot();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'c')
                return player->dropPoisonedCarrot();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/c." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->rabbitCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveRabbits();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
      default:  return false;
      case 'n': dir = NORTH; break;
      case 'e': dir = EAST;  break;
      case 's': dir = SOUTH; break;
      case 'w': dir = WEST;  break;
    }
    return true;
}

  // Return false without changing anything if moving one step from (r,c)
  // in the indicated direction would run off the edge of the arena.
  // Otherwise, update r and c to the position resulting from the move and
  // return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    switch(dir){
        case NORTH:         //up direction
            if (r > 1){
                r--;
                return true;
            }
            break;
        case EAST:         //right direction
            if (c < a.cols()){
                c++;
                return true;
            }
            break;
        case SOUTH:         //down direction
            if (r < a.rows()){
                r++;
                return true;
            }
            break;
        case WEST:         //left direction
            if (c > 1){
                c--;
                return true;
            }
            break;
        default:
            break;
    }
      
    return false;
}




bool checkOutOfBounds(const Arena& a, int dir, int r, int c){
    //false means that new pos is valid. true means new pos is out of bounds
    switch(dir){
        case NORTH:
            r--;
            if (r < 1 || r > a.rows())
                return true;
            break;
        case EAST:
            c++;
            if (c < 1 || c > a.cols())
                return true;
            break;
        case SOUTH:
            r++;
            if (r < 1 || r > a.rows())
                return true;
            break;
        case WEST:
            c--;
            if (c < 1 || c > a.cols())
                return true;
            break;
    }
    return false;
}



//checks the amount of adjecent rabbits if moved in a direction or stayed still
int checkRabbits(const Arena& a, int dir, int r, int c){
    int counter = 0;
    
    switch (dir){
        case NORTH:
            r--;
            if (a.numberOfRabbitsAt(r, c) > 0){   // if theres a rabbit on the spot
                counter = 10;                       // then return large value
                break;}                             // otherwise count surrounding rabbits
            if (a.numberOfRabbitsAt(r+1, c) > 0 && !checkOutOfBounds(a, SOUTH, r, c)){
                counter += a.numberOfRabbitsAt(r+1, c);}
            if (a.numberOfRabbitsAt(r-1, c) > 0 && !checkOutOfBounds(a, NORTH, r, c)){
                counter += a.numberOfRabbitsAt(r-1, c);}
            if (a.numberOfRabbitsAt(r, c+1) > 0 && !checkOutOfBounds(a, EAST, r, c)){
                counter += a.numberOfRabbitsAt(r, c+1);}
            if (a.numberOfRabbitsAt(r, c-1) > 0 && !checkOutOfBounds(a, WEST, r, c)){
                counter += a.numberOfRabbitsAt(r, c-1);}
            break;
        case EAST:
            c++;
            if (a.numberOfRabbitsAt(r, c) > 0){     // if theres a rabbit on the spot
                counter = 10;                       // then return large value
                break;}                             // otherwise count surrounding rabbits
            if (a.numberOfRabbitsAt(r+1, c) > 0 && !checkOutOfBounds(a, SOUTH, r, c)){
                counter += a.numberOfRabbitsAt(r+1, c);}
            if (a.numberOfRabbitsAt(r-1, c) > 0 && !checkOutOfBounds(a, NORTH, r, c)){
                counter += a.numberOfRabbitsAt(r-1, c);}
            if (a.numberOfRabbitsAt(r, c+1) > 0 && !checkOutOfBounds(a, EAST, r, c)){
                counter += a.numberOfRabbitsAt(r, c+1);}
            if (a.numberOfRabbitsAt(r, c-1) > 0 && !checkOutOfBounds(a, WEST, r, c)){
                counter += a.numberOfRabbitsAt(r, c-1);}
            break;
        case SOUTH:
            r++;
            if (a.numberOfRabbitsAt(r, c) > 0){     // if theres a rabbit on the spot
                counter = 10;                       // then return large value
                break;}                             // otherwise count surrounding rabbits
            if (a.numberOfRabbitsAt(r+1, c) > 0 && !checkOutOfBounds(a, SOUTH, r, c)){
                counter += a.numberOfRabbitsAt(r+1, c);}
            if (a.numberOfRabbitsAt(r-1, c) > 0 && !checkOutOfBounds(a, NORTH, r, c)){
                counter += a.numberOfRabbitsAt(r-1, c);}
            if (a.numberOfRabbitsAt(r, c+1) > 0 && !checkOutOfBounds(a, EAST, r, c)){
                counter += a.numberOfRabbitsAt(r, c+1);}
            if (a.numberOfRabbitsAt(r, c-1) > 0 && !checkOutOfBounds(a, WEST, r, c)){
                counter += a.numberOfRabbitsAt(r, c-1);}
            break;
        case WEST:
            c--;
            if (a.numberOfRabbitsAt(r, c) > 0){     // if theres a rabbit on the spot
                counter = 10;                       // then return large value
                break;}                             // otherwise count surrounding rabbits
            if (a.numberOfRabbitsAt(r+1, c) > 0 && !checkOutOfBounds(a, SOUTH, r, c)){
                counter += a.numberOfRabbitsAt(r+1, c);}
            if (a.numberOfRabbitsAt(r-1, c) > 0 && !checkOutOfBounds(a, NORTH, r, c)){
                counter += a.numberOfRabbitsAt(r-1, c);}
            if (a.numberOfRabbitsAt(r, c+1) > 0 && !checkOutOfBounds(a, EAST, r, c)){
                counter += a.numberOfRabbitsAt(r, c+1);}
            if (a.numberOfRabbitsAt(r, c-1) > 0 && !checkOutOfBounds(a, WEST, r, c)){
                counter += a.numberOfRabbitsAt(r, c-1);}
            break;
        case STILL:
            if (a.numberOfRabbitsAt(r+1, c) > 0 && !checkOutOfBounds(a, SOUTH, r, c)){
                counter += a.numberOfRabbitsAt(r+1, c);}
            if (a.numberOfRabbitsAt(r-1, c) > 0 && !checkOutOfBounds(a, NORTH, r, c)){
                counter += a.numberOfRabbitsAt(r-1, c);}
            if (a.numberOfRabbitsAt(r, c+1) > 0 && !checkOutOfBounds(a, EAST, r, c)){
                counter += a.numberOfRabbitsAt(r, c+1);}
            if (a.numberOfRabbitsAt(r, c-1) > 0 && !checkOutOfBounds(a, WEST, r, c)){
                counter += a.numberOfRabbitsAt(r, c-1);}
            break;
    }
    return counter;
}



  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should drop a poisoned carrot and
  // not move; otherwise, this function sets bestDir to the recommended
  // direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // temp value for best dir
    int safestDir;
    
    //represents number of adjacent rats and initializes the array
    int adjRats[5];
    adjRats[NORTH] = checkRabbits(a, NORTH, r, c);
    adjRats[EAST] = checkRabbits(a, EAST, r, c);
    adjRats[SOUTH] = checkRabbits(a, SOUTH, r, c);
    adjRats[WEST] = checkRabbits(a, WEST, r, c);
    adjRats[STILL] = checkRabbits(a, STILL, r, c);

    
    //if no poison in cell and it has no adjacent rats then drop carrot
    if (checkRabbits(a, STILL, r, c) == 0 && a.getCellStatus(r, c) == EMPTY){
        return false;}
    
    //if poison in cell and has no adj rats then check if surrounding also have 0 adj rats
    //if so then move there otherwise stay still
    if (checkRabbits(a, STILL, r, c) == 0 && a.getCellStatus(r, c) == HAS_POISON){
        safestDir = STILL;
        for (int k = 0; k < NUMDIRS; k++){
            if (adjRats[k] == 0 && !checkOutOfBounds(a, k, r, c)){
                if (k == 0 && a.getCellStatus(r - 1, c) == EMPTY)
                    safestDir = k;
                if (k == 1 && a.getCellStatus(r, c + 1) == EMPTY)
                    safestDir = k;
                if (k == 2 && a.getCellStatus(r + 1, c) == EMPTY)
                    safestDir = k;
                if (k == 3 && a.getCellStatus(r, c - 1) == EMPTY)
                    safestDir = k;
            }
        }
        if (safestDir == STILL)
            return false;
        
        bestDir = safestDir;
        return true;
    }
    
    safestDir = STILL;
    for (int k = 0; k < NUMDIRS; k++){       //set lowest rabbit count to safest direction
        if (adjRats[k] < adjRats[safestDir] && !checkOutOfBounds(a, k, r, c)){
            safestDir = k;}
        }
    
    if (safestDir == STILL)                 //if its still, then return false
        return false;
    
    bestDir = safestDir;                //otherwise set best dir to safest dir and true
    return true;
    
    
        
    
    
      
      // Your replacement implementation should do something intelligent.
      // You don't have to be any smarter than the following, although
      // you can if you want to be:  If staying put runs the risk of a
      // rabbit possibly moving onto the player's location when the rabbits
      // move, yet moving in a particular direction puts the player in a
      // position that is safe when the rabbits move, then the chosen
      // action is to move to a safer location.  Similarly, if staying put
      // is safe, but moving in certain directions puts the player in
      // danger of dying when the rabbits move, then the chosen action should
      // not be to move in one of the dangerous directions; instead, the player
      // should stay put or move to another safe position.  In general, a
      // position that may be moved to by many rabbits is more dangerous than
      // one that may be moved to by few.
      //
      // Unless you want to, you do not have to take into account that a
      // rabbit might be poisoned and thus sometimes less dangerous than one
      // that is not.  That requires a more sophisticated analysis that
      // we're not asking you to do.
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(3, 5, 3);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif



