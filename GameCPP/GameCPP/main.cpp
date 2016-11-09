//
//  main.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/19/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//
#include "RandomBreakthroughPlayer.h"
#include "AlphaBetaBreakthroughPlayer.h"
#include "main.h"

std::string readFile(std::string fname) {
	try {
		std::fstream input(fname);
		std::string boardStr = "";
		while (!input.fail()) {
			const int N = 100;
			char buf[100];
			input.getline(buf, N);
			boardStr += buf;
		}
		input.close();
		return boardStr;
	}
	catch (...) {
		std::cerr << "Problem reading puzzle " << std::endl;
		exit(0);
	}
}

GameState *readBoard(std::string fname) {
	std::string brdStr = readFile(fname);
	GameState *st = new BreakthroughState();
	st->parseMsg(brdStr);
	return st;
}

void sometests() {
	GameState *state = readBoard("bt4.txt");
	BreakthroughState st = static_cast<BreakthroughState&>(*state);
	for (int r = 0; r < st.ROWS; r++) {
		for (int c = 0; c < st.COLS; c++) {
			int rowDelta = state->getWho() == Who::HOME ? +1 : -1;
			for (int dc = -1; dc <= +1; dc++) {
				BreakthroughMove mv(r, c, r + rowDelta, c + dc);
				if (state->moveOK(mv)) {
					BreakthroughState newState(st);
					newState.makeMove(mv);
					std::cout << (int)newState.getStatus() << ' ';
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	AlphaBetaBreakthroughPlayer p("ZoneControl");
	//p.solvePuzzles({ "bt1.txt", "bt2.txt", "bt3.txt", "bt4.txt" });
    p.compete(argc, argv);   // Compete in tournament
	system("Pause");
    return 0;
}