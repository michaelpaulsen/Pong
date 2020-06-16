class Ball {
public:
	int xVel, yVel, x, y;
	Ball(int xVel, int yVel, int x, int y) {
		this->xVel = xVel;
		this->yVel = yVel;
		this->y = y;
		this->x = x;
	}
	void Move(int TextareaSize, int screen_width, int screen_height) {/** don't take players into account*/
		this->x += this->xVel;
		this->y += this->yVel;
		if (this->y <= 1 || this->y >= screen_height - (TextareaSize + 1)) {
			this->yVel *= -1;
		}
		if (this->x <= 2) {
			this->xVel *= -1;
			// add point to player 2
		}
		else if (this->x >= (screen_width - 2)) {
			this->xVel *= -1;
			//add point to player one
		}

	}
	void Move(int TextareaSize, int screen_width, int screen_height, Paddle players[2]) {/** take players into account*/
		this->x += this->xVel;
		this->y += this->yVel;
		/**colide with player one*/
		if (this->x == players[0].x) {
			if (this->y >= players[0].y - players[0].size && this->y <= players[0].y + players[0].size) {
				this->xVel *= -1;
			}
		}
		/**colide with player two*/
		if (this->x == players[1].x) {
			if (this->y >= players[1].y - players[1].size && this->y <= players[1].y + players[1].size) {
				this->xVel *= -1;
			}
		}
		/**normal Move Function*/
		if (this->y <= 1 || this->y >= screen_height - (TextareaSize + 1)) {
			this->yVel *= -1;
		}
		if (this->x <= 2) {
			this->xVel *= -1;
			// add point to player 2
			players[1].score++;
		}
		else if (this->x >= (screen_width - 2)) {
			//add point to player 1
			players[0].score++;
			this->xVel *= -1;
		}
	}
};