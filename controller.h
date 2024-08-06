#ifndef A1_MAZE_CPP_1_CONTROLLER_H
#define A1_MAZE_CPP_1_CONTROLLER_H

#include <QString>

#include "maze.h"

namespace s21 {

class Controller {
 public:
  Controller() = default;
  Controller(QString path) { facade_.ReadMaze(path.toStdString()); }

  int operator()(Maze::Vh matrix_type, int i, int j) {
    return facade_(matrix_type, i, j);
  }

  int Rows() { return facade_.Rows(); }
  int Cols() { return facade_.Cols(); }

  void ReadMaze(QString path) {
    facade_.ResetPath();
    facade_.ReadMaze(path.toStdString());
  }
  void Eller(int rows, int cols) {
    static int counter = 0;
    facade_.ResetPath();
    facade_.GenerateMaze(rows, cols);
    std::string filename = "maze_generated_.mz";
    filename.insert(15, std::to_string(++counter));
    facade_.WriteMaze(filename);
  }
  void GeneratePath(int from_row, int from_col, int to_row, int to_col) {
    facade_.ResetPath();
    facade_.GeneratePath(from_row, from_col, to_row, to_col);
  }
  bool IsEmptyPath() { return facade_.IsEmptyPath(); }
  std::vector<int> GetPath() { return facade_.GetPath(); }

 private:
  Facade facade_;
};

}  // namespace s21

#endif  // A1_MAZE_CPP_1_CONTROLLER_H
