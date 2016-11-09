#include "GamePlayer.h"
#include "GameMove.h"
#include "BreakthroughState.h"
#include "BreakthroughMove.h"
#include <stdio.h>

class ScoredBreakthroughMove : public BreakthroughMove {
public:
	ScoredBreakthroughMove(){
		score = 0;
	}
	ScoredBreakthroughMove(int r1, int c1, int r2, int c2, double s) {
		Move = new BreakthroughMove(r1, c1, r2, c2);
		score = s;
	}
	/*~ScoredBreakthroughMove() {
		delete Move;
	}*/
	void set(int r1, int c1, int r2, int c2, double s) {
		Move->setMv(r1, c1, r2, c2);
		score = s;
	}
	void setScore(double s){
		score = s;
	}
	double score;
	BreakthroughMove *Move;
};