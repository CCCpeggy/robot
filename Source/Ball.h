#include "../Source/Object.h"
#include "../Include/Common.h"

class Ball: public Object {
private:
	std::vector<float> bTime;
	std::vector<float> bMove;
	int size;
	static int speed;
	int max = 1000;

	static void computePos(glm::vec3& offset, float time, float move) {
		float x = time / speed * 3 - 1.5;
		float y = x * x * 2;
		x += 1.8;
		offset.x = x * cos(move / 180 * 3.14);
		offset.y = y;
		offset.z = -x * sin(move / 180 * 3.14);
	}

public:
	Ball() :{
		addBall();
		update(1);
	}
	void addBall(float move = 0) {
		offsets.push_back(glm::vec3(0, 0, 0));
		bMove.push_back(move);
		bTime.push_back(0);
		computePos(offsets[size], 0, move);
		size++;
	}
	void update(int number) {
		for (int i = 0; i < size; ) {
			if (bTime[i] > (speed * 0.8)) {
				offsets.erase(offsets.begin() + i);
				bMove.erase(bMove.begin() + i);
				bTime.erase(bTime.begin() + i);
				size--;
			}
			else {
				bTime[i] += 1;
				computePos(offsets[i], bTime[i], bMove[i]);
				i++;
			}
		}
		if (size < max) {
			int add = rand() % (number * 2);
			for (int i = 0; i < add; i++) {
				addBall(rand() % 360);
			}
		}
	}
};

int Ball::speed = 100;