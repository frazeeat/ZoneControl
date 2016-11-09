
struct HashValue {
	long long zobrist;
	int depth;
	double score;
	bool ancient;
	int type;
		// 1 = exact score
		// 2 = alpha, value is at MOST = to score
		// 3 = beta, value is at LEAST = to score
};