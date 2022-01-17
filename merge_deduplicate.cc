#include <assert.h>

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>

char sep = '\t';

std::vector<uint64_t> get_row_col(std::string str, char sep) {
  std::istringstream input;
  input.str(str);
  std::vector<uint64_t> vals;
  for (std::string comp; std::getline(input, comp, sep); ) {
    vals.push_back(std::stol(comp));
  }
  return vals;
}

struct edge {
  uint32_t row;
  uint32_t col;
  edge() {
    row = col = 0;
  }

  edge(uint32_t row, uint32_t col) {
    this->row = row;
    this->col = col;
  }

  bool operator==(const edge b) const {
    return row == b.row && col == b.col;
  }

  bool operator<(const edge b) const {
    if (row < b.row)
      return true;
    else if (row > b.row)
      return false;
    else
      return col < b.col;
  }
};

int main(int argc, char *argv[]) {
  assert(argc >= 3);
  std::string output_file = argv[1];
  long max_len = std::stol(argv[2]);
  printf("write results to %s\n", output_file.c_str());
  std::vector<edge> edges(max_len);
  printf("edge size: %ld, max len: %ld\n", sizeof(edge), max_len);

  // Get all edges.
  auto start = std::chrono::system_clock::now();
  size_t idx = 0;
  size_t num_self_loops = 0;
  for (std::string line; std::getline(std::cin, line); ) {
    std::vector<uint64_t> vals = get_row_col(line, '\t');
    assert(vals.size() == 2);
    // Remove self loop
    if (vals[0] == vals[1]) {
      num_self_loops++;
      continue;
    }
    // Convert the graph into an undirected graph.
    assert(idx + 2 < edges.size());
    edges[idx] = edge(vals[0], vals[1]);
    edges[idx + 1] = edge(vals[1], vals[0]);
    idx += 2;
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  printf("There are %ld edges, %ld self-loops, elapsed time: %f seconds\n",
         idx, num_self_loops, elapsed_seconds.count());

  // Sort edges
  size_t num_edges = idx;
  start = std::chrono::system_clock::now();
  std::sort(edges.begin(), edges.begin() + num_edges);
  auto it = std::unique(edges.begin(), edges.begin() + num_edges);
  num_edges = it - edges.begin();
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  printf("there are %ld unique edges, elapsed time: %f seconds\n",
         num_edges, elapsed_seconds.count());
  
  start = std::chrono::system_clock::now();
  FILE *out = fopen(output_file.c_str(), "w");
  for (size_t i = 0; i < num_edges; i++) {
    fprintf(out, "%d %d %ld 0\n",
            edges[i].row, // src_id
            edges[i].col, // dst_id
            i // type_edge_id
    );
  }
  fclose(out);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  printf("writing data taking %f seconds\n", elapsed_seconds.count());
}
