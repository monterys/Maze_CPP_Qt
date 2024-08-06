#ifndef A1_MAZE_CPP_1_MAZE_H
#define A1_MAZE_CPP_1_MAZE_H

#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <vector>

namespace s21 {

class Eller;

class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other) noexcept;
  ~Matrix();

  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other) noexcept;
  int& operator()(int rows, int cols);
  int operator()(int rows, int cols) const;

  int Rows() const;
  int Cols() const;
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  int rows_, cols_;
  int* matrix_;
};

class Maze {
 public:
  Maze();
  Maze(int rows, int cols);
  Maze(std::string filename);
  enum class Vh { kVertical, kHorizontal };
  int& operator()(Vh matrix_type, int i, int j);
  int operator()(Vh matrix_type, int i, int j) const;

  int Rows() const;
  int Cols() const;

  void ReadMaze(std::string path);
  void WriteMaze(std::string path) const;
  Maze Generate(int rows, int cols);

#ifdef DEBUG
  void PrintMaze() const;
#endif  // DEBUG

 private:
  void swap(Maze& other);

  int rows_, cols_;
  Matrix matrix_vertical_;
  Matrix matrix_horizontal_;
};

class Eller {
 public:
  Eller(int rows, int cols);

  void Generate();
  Maze GetMaze();

 private:
  void FirstRowEmptyVallue();
  void AssignUniqueSet(int row);
  void AddVerticalWalls(int row);
  void AddHorizontalWalls(int row);
  int CalculateUniqueSet(int set, int row);
  void CheckHorizontalWalls(int row);
  int CalculateHorizontalWalls(int row, int set);
  void NextLineFilling(int row);
  void LastRow();
  void LastRowVerticalWallsCheck();
  void MergeSet(int row, int set, int change);

  int unique_set_;
  Maze maze_;
  int rows_;
  int cols_;
  Matrix set_matrix_;
};

struct Point {
  Point(int x, int y, int wave) : x_(x), y_(y), wave_(wave) {}
  int x_, y_, wave_;
};

class Path {
 public:
  Path(Maze maze);
  void GeneratePath(int x_begin, int y_begin, int x_target, int y_target);
  void Print();
  std::vector<int> GetWay();

 private:
  bool TargetCheck(Point p, int x_target, int y_target);
  void DirectionCheck(Point p);
  void WaveMatrixAdd(Point p);
  void StartPointAdd(int x_begin, int y_begin);
  void LeftCheck(Point p);
  void RightCheck(Point p);
  void UpCheck(Point p);
  void DownCheck(Point p);
  void Clear();

  void WayBack(int x_target, int y_target);

  Maze maze_;
  int rows_;
  int cols_;
  Matrix waves_matrix_;
  std::vector<int> path_;
  std::queue<Point> que_;
};

class Facade {
 public:
  Facade() = default;
  Facade(std::string path);

  int& operator()(Maze::Vh matrix_type, int i, int j);
  int operator()(Maze::Vh matrix_type, int i, int j) const;

  int Rows() const;
  int Cols() const;

  void ReadMaze(std::string path);
  void WriteMaze(std::string path);
  void GenerateMaze(int rows, int cols);
  void GeneratePath(int x_begin, int y_begin, int x_target, int y_target);
  std::vector<int> GetPath();
  void ResetPath();
  bool IsEmptyPath();

 private:
  Maze maze_;
  std::vector<int> path_;
};

}  // namespace s21

#endif  // A1_MAZE_CPP_1_MAZE_H
