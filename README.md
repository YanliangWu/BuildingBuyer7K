# BuildingBuyer7000
BuildingBuyer7000 is a monopoly styled game inspired by the University of Waterloo.  

Including features: 
- Support 2-8 player
- Load-save feature supported

### Version
1.0

### TODO List
- OpenGL Support

### Implementation
- Player class is a usage of observer pattern, containing a Controller pointer and a array of pointers, with a fixed size of 40, each pointers is either NULL or pointing to a Block object that   the player owns. Basically, Player class is mainly used to stored all the information that a player has. Moreover, we implemented methods to give other classes access to Player’s fields, and we put the implementations of “mortgage”, “unmortgage”, “assets”, and “improve” in Player.
- Controller class is a usage of observer pattern. It contains a pointer pointing at Board, and an array of pointers , with a fixed size of 8, each pointer is either NULL or pointing to a Player object. Controller class is used to control all the players created, and to create players. Almost every command a player entered is read by controller, and controller would response and make changes to the game board and each player. Also, we put the implementations of “roll”, “next”, “trade”, “save”, and “loading a game”. And Controller decides when to print the updated game board.
- Board class is where we created the initial game board. And it is to store all the basic information for each square, and track the position of each player. There are 40 Block object in total, and each Block object represents a square on the game board. This class uses observer pattern.
- Block class is used to store information for each square, such as the name and position. The pure virtual methods in Block class allow Player, Board, and Controller to access the information about each square and make changes to it. Block class can update the improvement level, and the owner of a specific square. Most importantly, the key feature of this class is to calculate the  tuition fee to pay for each player landed on the square. It is a super class with 11 child classes, it is also a usage of decorator pattern as well.
- These classes inherit the field from their super class Block. The action is different for each square after a player landing, so the implementation of land() is different, and it overwrite the virtual method land() in class Block. Each child class would store unique information, which means each child class has different fields, therefore, the way to change the fields of each child class is different, which for each child class, overwriting every virtual method in class Block.

