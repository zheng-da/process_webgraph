all:
	g++ -O2 merge_deduplicate.cc -o merge_deduplicate -fopenmp -D_GLIBCXX_PARALLEL
