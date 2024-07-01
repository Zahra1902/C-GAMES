#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>
using namespace std;
// Maze
class Maze
{
int numRow;
size_t numCol;
int** mat;
public:
Maze() : numRow(0), numCol(0), mat(nullptr) {}
void showMazeProperty();
void readMaze();
void drawMaze();
int getNumRow() const;
size_t getNumCol() const { return numCol; }
int** getMat() const;
};
void Maze::showMazeProperty()
{
cout << "Num rows: " << numRow << endl;
cout << "Num columns: " << numCol << endl;
}
void Maze::readMaze()
{
string myText;
ifstream MyReadFile("maze.txt");
int r = 0;
while (getline(MyReadFile, myText))
{
r++;
}
numRow = r;
numCol = myText.length();
MyReadFile.close();
mat = new int* [numRow];
for (int i = 0; i < numRow; i++)
mat[i] = new int[numCol];
MyReadFile.open("maze.txt");
r = 0;
while (getline(MyReadFile, myText))
{
for (size_t i = 0; i < myText.length(); ++i)
{
mat[r][i] = (int)myText.at(i) - 48;
}
r++;
}
MyReadFile.close();
}
void Maze::drawMaze()
{
system("cls");
cout << endl;
for (int i = 0; i < numRow; i++)
{
for (size_t j = 0; j < numCol; j++)
{
if (mat[i][j] == 1)
cout << "|";
else if (mat[i][j] == 0)
cout << " ";
else if (mat[i][j] == 2)
cout << "*";
else if (mat[i][j] == 3)
cout << "P";
else if (mat[i][j] == 4)
cout << "M";
}
cout << endl;
}
}
int Maze::getNumRow() const
{
return numRow;
}
int** Maze::getMat() const
{
return mat;
}
class Creature {
int row;
int col;
const Maze& maze;
public:
Creature() : row(0), col(0), maze(Maze()) {}
Creature(int a_row, int a_col, const Maze& a_maze)
: row(a_row), col(a_col), maze(a_maze) {}
void getPosition(int& a_row, int& a_col);
void setPosition(int a_row, int a_col);
void updatePosition(char move);
bool isValidMove(int row, int col);
};
void Creature::getPosition(int& a_row, int& a_col) {
a_row = row;
a_col = col;
}
void Creature::setPosition(int a_row, int a_col) {
row = a_row;
col = a_col;
}
void Creature::updatePosition(char move) {
int newRow = row;
int newCol = col;
if (move == 'w') // move up
{
newRow = row - 1;
}
if (move == 'd') // move right
{
newCol = col + 1;
}
if (move == 'z') // move down
{
newRow = row + 1;
}
if (move == 'a') // move left
{
newCol = col - 1;
}
if (isValidMove(newRow, newCol)) {
row = newRow;
col = newCol;
}
}
bool Creature::isValidMove(int row, int col) {
if (row < 0 || row >= maze.getNumRow() || col < 0 || col >= maze.getNumCol()) {
return false; // Out of bounds
}
int** mat = maze.getMat();
if (mat[row][col] == 1) {
return false; // Wall
}
return true;
}
// Monster
class Monster
{
int row;
int col;
public:
Monster() : row(0), col(0) {}
Monster(int a_row, int a_col)
{
row = a_row;
col = a_col;
}
void getPosition(int& a_row, int& a_col);
void setPosition(int a_row, int a_col);
};
void Monster::getPosition(int& a_row, int& a_col)
{
a_row = row;
a_col = col;
}
void Monster::setPosition(int a_row, int a_col)
{
row = a_row;
col = a_col;
}
//GAME
class CGame {
Maze maze;
Creature player;
Monster monster;
int FoodPoints;
public:
CGame()
: player(1, 3, maze), monster(2, 10), FoodPoints(0) {
maze.readMaze();
maze.drawMaze();
maze.showMazeProperty();
PacmanGame();
}
void PacmanGame();
void moveMonster();
bool checkWinCondition();
bool checkLoseCondition();
};
void CGame::PacmanGame() {
int row, col;
char move = 'y';
bool restart = true;
while (restart) {
// Reset game variables
move = 'y';
player.setPosition(1, 3);
monster.setPosition(2, 10);
FoodPoints = 0;
while (move != 'q') { // press q to quit
if (checkLoseCondition()) {
cout << "GAME OVER" << endl;
break;
}
if (checkWinCondition()) {
cout << "Congrats! You won the game" << endl;
break;
}
maze.drawMaze();
maze.showMazeProperty();
player.getPosition(row, col);
cout << "Pacman at position (" << row << "," << col << ")" << endl;
monster.getPosition(row, col);
cout << "Monster at position (" << row << "," << col << ")" << endl;
bool validMove = false;
while (!validMove) {
cout << "Enter move (w - up, d - right, z - down, a - left, q - quit): ";
cin >> move;
cout << move << endl;
if (move == 'q')
break;
// Validate the move
if (move == 'w' || move == 'd' || move == 'z' || move == 'a') {
validMove = true;
}
else {
cout << "Invalid move. Please enter a valid move." << endl;
}
}
if (move == 'q')
break;
maze.drawMaze();
player.getPosition(row, col);
maze.getMat()[row][col] = 0;
player.updatePosition(move);
player.getPosition(row, col);
maze.getMat()[row][col] = 3;
moveMonster(); // Update monster's position
maze.drawMaze();
}
char choice;
cout << "Do you want to restart the game? (y/n): ";
cin >> choice;
if (choice == 'n' || choice == 'N') {
cout << "Goodbye!" << endl;
restart = false;
}
}
}
void CGame::moveMonster() {
int playerRow, playerCol, monsterRow, monsterCol;
player.getPosition(playerRow, playerCol);
monster.getPosition(monsterRow, monsterCol);
int newRow, newCol;
if (playerRow < monsterRow && player.isValidMove(monsterRow - 1, monsterCol)) {
newRow = monsterRow - 1; // Move up
newCol = monsterCol;
}
else if (playerRow > monsterRow && player.isValidMove(monsterRow + 1, monsterCol)) {
newRow = monsterRow + 1; // Move down
newCol = monsterCol;
}
else if (playerCol < monsterCol && player.isValidMove(monsterRow, monsterCol - 1)) {
newRow = monsterRow;
newCol = monsterCol - 1; // Move left
}
else if (playerCol > monsterCol && player.isValidMove(monsterRow, monsterCol + 1)) {
newRow = monsterRow;
newCol = monsterCol + 1; // Move right
}
else {
int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // Up, down, left, right
int numDirections = 4;
bool foundValidMove = false;
while (numDirections > 0 && !foundValidMove) {
int randIndex = rand() % numDirections;
int dx = directions[randIndex][0];
int dy = directions[randIndex][1];
if (player.isValidMove(monsterRow + dx, monsterCol + dy)) {
newRow = monsterRow + dx;
newCol = monsterCol + dy;
foundValidMove = true;
}
// Swap the chosen direction with the last direction to remove it from the available directions
int tempX = directions[numDirections - 1][0];
int tempY = directions[numDirections - 1][1];
directions[randIndex][0] = tempX;
directions[randIndex][1] = tempY;
numDirections--;
}
if (!foundValidMove) {
// The monster is surrounded by walls and cannot move
return;
}
}
maze.getMat()[monsterRow][monsterCol] = 0; // Clear previous monster position
monster.setPosition(newRow, newCol);
maze.getMat()[newRow][newCol] = 4; // Update new monster position
}
bool CGame::checkWinCondition() {
int foodRemaining = 0;
for (int i = 0; i < maze.getNumRow(); ++i) {
for (int j = 0; j < maze.getNumCol(); ++j) {
if (maze.getMat()[i][j] == 2) {
foodRemaining++;
}
}
}
return foodRemaining == 0;
}
bool CGame::checkLoseCondition() {
int playerRow, playerCol, monsterRow, monsterCol;
player.getPosition(playerRow, playerCol);
monster.getPosition(monsterRow, monsterCol);
return (playerRow == monsterRow && playerCol == monsterCol);
}
int main()
{
CGame play;
play.PacmanGame();
return 0;

}