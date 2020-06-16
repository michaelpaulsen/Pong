
class Paddle {
public:
	Paddle(int x, int y, int size = 2) {
		this->x = x;
		this->y = y;
		this->size = size;
		this->score = 0;
	};
	int x, y, size, score;
	void MoveUP(int step = 2) {
		if (this->y - (this->size) - 1 > 0) {
			this->y -= step;
		}
	}
	void MoveDOWN(int screen_height, int TextAreaSize, int step = 2) {
		if (this->y + this->size + step < (screen_height - (TextAreaSize))) {
			this->y += step;
		}
	}
};