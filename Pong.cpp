/*the includes*/
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <winuser.h>
#include "Paddle.cpp"
#include "Ball.cpp"
#include "Utils.cpp"
bool bUsePlayerColision = true;
//screen size
int screen_width = 100;//100
int screen_height = 40;//40
//player 
Paddle players[2] = { Paddle(5,(screen_height - 10) / 2),Paddle(screen_width - 5,(screen_height - 10) / 2) };
//the ball
Ball ball = Ball(1, 1, screen_width / 2, (screen_height - 10) / 2);
//windows vars
COORD consoleBufferSize = { screen_width,screen_height };
const SMALL_RECT r = { 0,0,screen_width - 1,screen_height - 1 };
const SMALL_RECT* rect = new SMALL_RECT(r);
int main()
{
	/**windows vars */
	wchar_t* screen = new wchar_t[screen_width * screen_height];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	int lastIndex = screen_width * screen_height - 1;// the last index of the screen string
	int textAreaSize = 10; // the number of rows that is used for text
	wchar_t title[11] = L"Pong ♠♣♦♥ "; // the text that is looped at the bottom of the widow
	/**set up the wait loop*/
	std::chrono::time_point<std::chrono::system_clock> Tp1 = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> Tp2;
	float fps = 10; // the fps that the game should run at (defalt 10)
	long frame = 1;// the frame that the game is on 
	bool playing = true;
	/**game loop*/
	while (playing) {
		playing = !(Skele_lib::Utils::GetKeyDown(VK_ESCAPE));
		//set up the console buffer
		SetConsoleScreenBufferSize(hConsole, consoleBufferSize);
		SetConsoleWindowInfo(hConsole, true, rect);
		// move the ball 
		if (!bUsePlayerColision) {
			ball.Move(textAreaSize, screen_width, screen_height);
		}
		else {
			ball.Move(textAreaSize, screen_width, screen_height, players);
			//move the Player's padel
			if (Skele_lib::Utils::GetKeyDown(VK_UP) || Skele_lib::Utils::GetKeyDown(0x57)) {/** move the player up*/
				players[1].MoveUP();
			}
			else if (Skele_lib::Utils::GetKeyDown(VK_DOWN) || Skele_lib::Utils::GetKeyDown(0x53)) {
				players[1].MoveDOWN(screen_height, textAreaSize);
			}
			//move the AI padel every other frame
			if (frame % 2 == 0) {
				if (players[0].y > ball.y) {
					players[0].MoveUP(1);
				}
				else if (players[0].y < ball.y) {
					players[0].MoveDOWN(screen_height, textAreaSize, 1);
				}
			}
		}
		//start displaying the screen
		for (int y = 0; y < screen_height; y++) {
			for (int x = 0; x < screen_width; x++) {
				screen[y * screen_width + x] = ' '; // init the screen to known state
				if (y == 0 || y == screen_height - textAreaSize || (y < screen_height - textAreaSize && (x == screen_width - 1 || x == 0))) {
					// write the outline
					screen[y * screen_width + x] = 0x2593;
				}
				else {
					/**display the bottom*/
					if (y > screen_height - textAreaSize) {
						screen[y * screen_width + x] = title[(y * screen_width + x) % (10)];
					}
					//display the ball 
					if (x == ball.x) {
						if (y == ball.y) {
							screen[y * screen_width + x] = L'♣';
						}
					}
				}
				if (bUsePlayerColision) {
					for (auto t : players) { // lazily looping through the players to draw them
						if (y >= t.y - t.size && y < t.y + t.size && x == t.x) {
							screen[y * screen_width + x] = '|';
						}
					}
				}
			}
			if (y == screen_height - 1) {
				if (playing) {
					screen[y * screen_width + (screen_width / 2) - 10] = ' ';
					screen[y * screen_width + (screen_width / 2) - 9] = ' ';
					screen[y * screen_width + (screen_width / 2) - 8] = ' ';
					screen[y * screen_width + (screen_width / 2) - 7] = ' ';
					screen[y * screen_width + (screen_width / 2) - 6] = ' ';
					screen[y * screen_width + (screen_width / 2) - 5] = ' ';
					screen[y * screen_width + (screen_width / 2) - 4] = 'B';
					screen[y * screen_width + (screen_width / 2) - 3] = 'Y';
					screen[y * screen_width + (screen_width / 2) - 2] = ' ';
					screen[y * screen_width + (screen_width / 2) - 1] = 'M';
					screen[y * screen_width + (screen_width / 2) + 0] = 'J';
					screen[y * screen_width + (screen_width / 2) + 1] = 'P';
					screen[y * screen_width + (screen_width / 2) + 2] = '!';
					screen[y * screen_width + (screen_width / 2) + 3] = ' ';
					screen[y * screen_width + (screen_width / 2) + 4] = ' ';
					screen[y * screen_width + (screen_width / 2) + 5] = ' ';
					screen[y * screen_width + (screen_width / 2) + 6] = ' ';
					screen[y * screen_width + (screen_width / 2) + 7] = ' ';
					screen[y * screen_width + (screen_width / 2) + 8] = ' ';// display my name at the bottom 
				}
				else {
					screen[y * screen_width + (screen_width / 2) - 10] = ' ';
					screen[y * screen_width + (screen_width / 2) - 9] = ' ';
					screen[y * screen_width + (screen_width / 2) - 8] = ' ';
					screen[y * screen_width + (screen_width / 2) - 7] = ' ';
					screen[y * screen_width + (screen_width / 2) - 6] = '!';
					screen[y * screen_width + (screen_width / 2) - 5] = 'G';
					screen[y * screen_width + (screen_width / 2) - 4] = 'A';
					screen[y * screen_width + (screen_width / 2) - 3] = 'M';
					screen[y * screen_width + (screen_width / 2) - 2] = 'E';
					screen[y * screen_width + (screen_width / 2) - 1] = ' ';
					screen[y * screen_width + (screen_width / 2) + 0] = 'O';
					screen[y * screen_width + (screen_width / 2) + 1] = 'V';
					screen[y * screen_width + (screen_width / 2) + 2] = 'E';
					screen[y * screen_width + (screen_width / 2) + 3] = 'R';
					screen[y * screen_width + (screen_width / 2) + 4] = '!';
					screen[y * screen_width + (screen_width / 2) + 5] = ' ';
					screen[y * screen_width + (screen_width / 2) + 6] = ' ';
					screen[y * screen_width + (screen_width / 2) + 7] = ' ';
					screen[y * screen_width + (screen_width / 2) + 8] = ' ';
				}
			}
		}
		/*wait loop */
		Tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> difference = Tp2 - Tp1;
		/**display player1's score*/
		screen[0] = ((players[0].score / 10) % 10) + 0x30;
		screen[1] = ((players[0].score) % 10) + 0x30;
		/**display player2's score*/
		screen[screen_width - 2] = ((players[1].score / 10) % 10) + 0x30;
		screen[screen_width - 1] = ((players[1].score) % 10) + 0x30;
		while (difference.count() < (float)1 / fps)
		{
			Tp2 = std::chrono::system_clock::now();
			difference = Tp2 - Tp1;
		}
		/**reset the chrono time*/
		Tp1 = std::chrono::system_clock::now();
		frame++;
		/**make the screen a Cstr (null tirminate it) */
		screen[lastIndex] = '\0';
		/**write the screen to the buffer*/
		WriteConsoleOutputCharacter(hConsole, screen, lastIndex + 1, { 0,0 }, &dwBytesWritten);
	}
}