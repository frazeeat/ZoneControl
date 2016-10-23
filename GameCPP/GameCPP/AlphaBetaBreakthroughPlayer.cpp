#include "AlphaBetaBreakthroughPlayer.h"
#include "BreakthroughMove.h"
#include "BreakthroughState.h"
#include "Heuristic.h"


AlphaBetaBreakthroughPlayer::AlphaBetaBreakthroughPlayer(std::string nickname)
: GamePlayer(nickname, "Breakthrough") {}

GameMove* AlphaBetaBreakthroughPlayer::getMove(GameState &state,
	const std::string &lastMv) {
	Heuristic h;
	
	BreakthroughState st = static_cast<BreakthroughState&>(state);

	h.firstHeuristic(st,1.0);

	std::vector<BreakthroughMove> mvArray;
	for (int r = 0; r < st.ROWS; r++) {
		for (int c = 0; c < st.COLS; c++) {
			int rowDelta = state.getWho() == Who::HOME ? +1 : -1;
			for (int dc = -1; dc <= +1; dc++) {
				BreakthroughMove mv(r, c, r + rowDelta, c + dc);
				if (state.moveOK(mv)) {
					mvArray.push_back(BreakthroughMove(mv));
				}
			}
		}
	}
	return new BreakthroughMove(mvArray[rand() % mvArray.size()]);
}
