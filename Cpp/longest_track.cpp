#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum Point : size_t {};

struct Path {
  Point from, to;
  unsigned length;

  /**
   * All arguments constructor.
   * Initializes a Path object with given parameters.
   * 
   * @param f Starting point of the path
   * @param t Ending point of the path
   * @param l Length of path
  */
  Path(size_t f, size_t t, unsigned l) : from{f}, to{t}, length{l} {}

  /**
   * Overloads the equality operator for comparing two Path objects.
   * 
   * @param a First Path object to be compared
   * @param b Second Path object to be compared
   * @return True if both Path objects are equal, otherwise False
  */
  friend bool operator == (const Path& a, const Path& b) {
    return std::tie(a.from, a.to, a.length) == std::tie(b.from, b.to, b.length);
  }
  
  /**
   * Overloads the inequality operator for comparing two Path objects.
   * 
   * @param a First Path object to be compared
   * @param b Second Path object to be compared
   * @return True if both Path objects aren't equal, otherwise False
  */
  friend bool operator != (const Path& a, const Path& b) { return !(a == b); }
};

/**
 * Performs topological sort on a directec acyclic graph (DAG).
 * 
 * @param adjList A graph represented by a adjecency list
 * @param inDegree Map storing the in-degree of each vertex
 * @return A vector containing the vertices of the input graph in topological order 
 * 
*/
std::vector<Point> top_sort ( const std::vector<std::vector<std::pair<Point, size_t>>> & adjList, std::map<Point, size_t> & inDegree ){
  std::queue<Point> q;
  std::vector<Point> res;

  for ( const auto & vertex : inDegree ){
    if ( vertex.second == 0 ){
      q.push ( vertex.first );
    }
  }

  while ( !q.empty() ){
    auto curr = q.front();
    q.pop();
    res.push_back ( curr );
    for ( const auto & neighbour : adjList[curr] ){
      inDegree[neighbour.first]--;
      if ( inDegree[neighbour.first] == 0 ){
        q.push ( neighbour.first );
      }
    }
  }

  return res;
}

/**
 * Reconstructs the longest path from the parent map, source nodes, and distances.
 * 
 * @param parent A map containing the parent node for each node in the graph 
 * @param sourceNodes A vector containing all source nodes of the graph
 * @param end End node
 * @param distances A vector of distances
 * @return A vector containing the reconstructed longest path
*/
std::vector<Path> reconstruct_longest_path ( const std::map<Point, Point> & parent, const std::vector<Point> & sourceNodes, const int end, const std::vector<int> & distances ){
  std::vector<Path> res;
  size_t curr = end;


  auto it = std::find (sourceNodes.begin(), sourceNodes.end(), Point {curr});
  while ( it == sourceNodes.end() ){
    Path tmp_path ( (parent.find( Point {curr} )) -> second, curr, unsigned(- (distances[curr] - distances[(parent.find( Point {curr} )) -> second])) );
    res.push_back( tmp_path );
    curr = (parent.find( Point {curr} )) -> second;
    it = std::find (sourceNodes.begin(), sourceNodes.end(), Point {curr});
  }

  std::reverse ( res.begin(), res.end() );

  return res;
}

/**
 * Runs the Bellman-Ford algorithm on the graph.
 * 
 * @param adjList The graph on which the Bellman-Ford algorithm will run represented by an adjacency list 
 * @param tOrder The topological order of the graph
 * @param srcNodes A vector of source nodes
 * @return A vector containing the longest path
*/
std::vector<Path> Bellman_Ford ( const std::vector<std::vector<std::pair<Point, size_t>>> & adjList, const std::vector<Point> tOrder, const std::vector<Point> srcNodes ){
  std::vector<Path> res;
  std::map<Point, Point> parent;
  std::vector<int> dist(adjList.size(), std::numeric_limits<int>::max());

  for ( const auto & srcNode : srcNodes ){
    dist[srcNode] = 0;
  }
  
  for ( const auto & vertex : tOrder ){
    for ( const auto & neigh : adjList[vertex] ){
      if ( dist[vertex] - (int)neigh.second < dist[neigh.first] ){
        dist[neigh.first] = dist[vertex] - (int)neigh.second;
        parent[neigh.first] = vertex;
      }
    }
  }

  auto minDistance = std::min_element(dist.begin(), dist.end());
  int minIndex = std::distance(dist.begin(), minDistance);

  std::vector<Path> result = reconstruct_longest_path ( parent, srcNodes, minIndex, dist );

  return result;
}

/**
 * Finds the longest track.
 * 
 * @param points The total number of points in the track
 * @param all_paths A vector containing all paths between points
 * @return The vector of Path objects representing the longest pathm in the graph
*/
std::vector<Path> longest_track(size_t points, const std::vector<Path>& all_paths){
  std::vector<std::vector<std::pair<Point, size_t>>> adjList(points);
  std::set<Point> verteces;
  std::vector<Point> sourceNodes;
  size_t neighListSize = 0;

  for ( const auto & Edge : all_paths ){
    adjList[Edge.from].push_back( std::make_pair( Edge.to, Edge.length ) );
    verteces.emplace( Edge.from );
    verteces.emplace( Edge.to );
  }

  std::map<Point, size_t> vertexDegIn;

  for ( const auto & vertex : verteces ){
    vertexDegIn[vertex] = 0;
  }

  for ( const auto & vertex : verteces ){
    neighListSize = adjList[vertex].size();
    for ( size_t j = 0; j < neighListSize; j++ ){
      vertexDegIn[adjList[vertex][j].first] += 1;
    }
  }

  for ( const auto & vertex : vertexDegIn ){
    if ( vertex.second == 0 ){
      sourceNodes.push_back( vertex.first );
    }
  }

  std::vector<Point> topologicalOrderOfGraph = top_sort ( adjList, vertexDegIn );

  std::vector<Path> result = Bellman_Ford ( adjList, topologicalOrderOfGraph, sourceNodes );

  return result;
}



struct Test {
  unsigned longest_track;
  size_t points;
  std::vector<Path> all_paths;
};

inline const Test TESTS[] = {
  {13, 5, { {3,2,10}, {3,0,9}, {0,2,3}, {2,4,1} } },
  {11, 5, { {3,2,10}, {3,1,4}, {1,2,3}, {2,4,1} } },
  {16, 8, { {3,2,10}, {3,1,1}, {1,2,3}, {1,4,15} } },
};

#define CHECK(cond, ...) do { \
    if (cond) break; \
    printf("Fail: " __VA_ARGS__); \
    printf("\n"); \
    return false; \
  } while (0)

bool run_test(const Test& t) {
  auto sol = longest_track(t.points, t.all_paths);

  unsigned length = 0;
  for (auto [ _, __, l ] : sol) length += l;

  CHECK(t.longest_track == length,
    "Wrong length: got %u but expected %u", length, t.longest_track);

  for (size_t i = 0; i < sol.size(); i++) {
    CHECK(std::count(t.all_paths.begin(), t.all_paths.end(), sol[i]),
      "Solution contains non-existent path: %zu -> %zu (%u)",
      sol[i].from, sol[i].to, sol[i].length);

    if (i > 0) CHECK(sol[i].from == sol[i-1].to,
      "Paths are not consecutive: %zu != %zu", sol[i-1].to, sol[i].from);
  }

  return true;
}
#undef CHECK

int main() {
  int ok = 0, fail = 0;

  for (auto&& t : TESTS) (run_test(t) ? ok : fail)++;
  
  if (!fail) printf("Passed all %i tests!\n", ok);
  else printf("Failed %u of %u tests.\n", fail, fail + ok);
}

