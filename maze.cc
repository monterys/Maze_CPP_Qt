#include "maze.h"

namespace s21 {

Maze::Maze() : rows_(0), cols_(0), matrix_vertical_(), matrix_horizontal_() {}

Maze::Maze(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::out_of_range(
        "Incorrect input, rows and cols of maze values must be > 0");
  }
  matrix_vertical_ = Matrix(rows_, cols_);
  matrix_horizontal_ = Matrix(rows_, cols_);
}

Maze::Maze(std::string filename) { ReadMaze(filename); }

int& Maze::operator()(Vh matrix_type, int i, int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }

  if (matrix_type == Maze::Vh::kVertical) {
    return matrix_vertical_(i, j);
  } else {
    return matrix_horizontal_(i, j);
  }
}

int Maze::operator()(Vh matrix_type, int i, int j) const {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }

  if (matrix_type == Maze::Vh::kVertical) {
    return matrix_vertical_(i, j);
  } else {
    return matrix_horizontal_(i, j);
  }
}

int Maze::Rows() const { return rows_; }
int Maze::Cols() const { return cols_; }

void Maze::ReadMaze(std::string path) {
  std::ifstream maze_file(path);
  if (!maze_file.is_open()) throw("File not found");

  maze_file >> rows_ >> cols_;

  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range(
        "Incorrect file, rows and cols  values must be > 0");
  }

  matrix_vertical_.SetRows(rows_);
  matrix_vertical_.SetCols(cols_);
  matrix_horizontal_.SetRows(rows_);
  matrix_horizontal_.SetCols(cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      maze_file >> matrix_vertical_(i, j);
    }
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      maze_file >> matrix_horizontal_(i, j);
    }
  }
}

void Maze::WriteMaze(std::string path) const {
  std::ofstream maze_file(path);
  if (!maze_file.is_open()) throw("Writing error");

  maze_file << rows_ << ' ' << cols_ << '\n';

  if (rows_ <= 0 || cols_ <= 0) return;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      maze_file << matrix_vertical_(i, j) << ' ';
    }
    maze_file << '\n';
  }

  maze_file << '\n';
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      maze_file << matrix_horizontal_(i, j) << ' ';
    }
    maze_file << '\n';
  }
}

Maze Maze::Generate(int rows, int cols) {
  std::cout << rows << cols << std::endl;
  Eller eller(rows, cols);
  eller.Generate();
  return eller.GetMaze();
}

//////////////////////////////////////////////////////////////// PATH
std::vector<int> Path::GetWay() { return path_; }

void Path::GeneratePath(int x_begin, int y_begin, int x_target, int y_target) {
  Clear();
  StartPointAdd(x_begin, y_begin);
  bool no_finish = true;
  while (no_finish) {
    no_finish = TargetCheck(que_.front(), x_target, y_target);
    if (no_finish) {
      DirectionCheck(que_.front());
      que_.pop();
      if (que_.empty()) {
        throw std::out_of_range("No path");
      }
    }
  }
  WayBack(x_target, y_target);
}

void Path::Clear() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      waves_matrix_(i, j) = 0;
    }
  }
  while (!que_.empty()) {
    que_.pop();
  }
  path_.clear();
}

void Path::WayBack(int x_target, int y_target) {
  int wave = waves_matrix_(y_target, x_target);
  int x = x_target;
  int y = y_target;
  path_.push_back(x);
  path_.push_back(y);

  wave -= 1;
  while (wave != 0) {
    if (x > 0 && waves_matrix_(y, x - 1) == wave &&
        maze_(Maze::Vh::kVertical, y, x - 1) == 0) {
      wave -= 1;
      x = x - 1;
      path_.push_back(x);
      path_.push_back(y);
    } else if (x < (int)(cols_ - 1) && waves_matrix_(y, x + 1) == wave &&
               maze_(Maze::Vh::kVertical, y, x) == 0) {
      wave -= 1;
      x = x + 1;
      path_.push_back(x);
      path_.push_back(y);
    } else if (y > 0 && waves_matrix_(y - 1, x) == wave &&
               maze_(Maze::Vh::kHorizontal, y - 1, x) == 0) {
      wave -= 1;
      y = y - 1;
      path_.push_back(x);
      path_.push_back(y);
    } else if (y < (int)(rows_ - 1) && waves_matrix_(y + 1, x) == wave &&
               maze_(Maze::Vh::kHorizontal, y, x) == 0) {
      wave -= 1;
      y = y + 1;
      path_.push_back(x);
      path_.push_back(y);
    }
  }
}

void Path::DirectionCheck(Point p) {
  LeftCheck(p);
  RightCheck(p);
  UpCheck(p);
  DownCheck(p);
}

void Path::DownCheck(Point p) {
  if (maze_(Maze::Vh::kHorizontal, p.y_, p.x_) == 0 &&
      waves_matrix_(p.y_ + 1, p.x_) == 0) {
    Point next(p.x_, p.y_ + 1, p.wave_ + 1);
    que_.push(next);
    WaveMatrixAdd(next);
  }
}

void Path::UpCheck(Point p) {
  if (p.y_ > 0) {
    if (maze_(Maze::Vh::kHorizontal, p.y_ - 1, p.x_) == 0 &&
        waves_matrix_(p.y_ - 1, p.x_) == 0) {
      Point next(p.x_, p.y_ - 1, p.wave_ + 1);
      que_.push(next);
      WaveMatrixAdd(next);
    }
  }
}

void Path::RightCheck(Point p) {
  if (maze_(Maze::Vh::kVertical, p.y_, p.x_) == 0 && p.x_ != (int)cols_ - 1) {
    if (waves_matrix_(p.y_, p.x_ + 1) == 0) {
      Point next(p.x_ + 1, p.y_, p.wave_ + 1);
      que_.push(next);
      WaveMatrixAdd(next);
    }
  }
}

void Path::LeftCheck(Point p) {
  if (p.x_ > 0) {
    if (maze_(Maze::Vh::kVertical, p.y_, p.x_ - 1) == 0 &&
        waves_matrix_(p.y_, p.x_ - 1) == 0) {
      Point next(p.x_ - 1, p.y_, p.wave_ + 1);
      que_.push(next);
      WaveMatrixAdd(next);
    }
  }
}

void Path::StartPointAdd(int x_begin, int y_begin) {
  Point begin(x_begin, y_begin, 1);
  que_.push(begin);
  WaveMatrixAdd(begin);
}

void Path::WaveMatrixAdd(Point p) { waves_matrix_(p.y_, p.x_) = p.wave_; }

bool Path::TargetCheck(Point p, int x_target, int y_target) {
  bool no_finish = true;
  if (p.x_ == x_target && p.y_ == y_target) {
    no_finish = false;
  }
  return no_finish;
}

Path::Path(Maze maze)
    : maze_(maze),
      rows_(maze.Rows()),
      cols_(maze.Cols()),
      waves_matrix_(rows_, cols_) {}

//////////////////////////////////////////////////////////////// FACADE
Facade::Facade(std::string path) { maze_.ReadMaze(path); }

int& Facade::operator()(Maze::Vh matrix_type, int i, int j) {
  return maze_(matrix_type, i, j);
}

int Facade::operator()(Maze::Vh matrix_type, int i, int j) const {
  return maze_(matrix_type, i, j);
}

int Facade::Rows() const { return maze_.Rows(); }
int Facade::Cols() const { return maze_.Cols(); }

void Facade::ReadMaze(std::string path) { maze_.ReadMaze(path); }
void Facade::WriteMaze(std::string path) { maze_.WriteMaze(path); }

void Facade::GenerateMaze(int rows, int cols) {
  Eller eller(rows, cols);
  eller.Generate();
  maze_ = eller.GetMaze();
}

void Facade::GeneratePath(int x_begin, int y_begin, int x_target,
                          int y_target) {
  Path path(maze_);
  path.GeneratePath(x_begin, y_begin, x_target, y_target);
  path_ = path.GetWay();
}

std::vector<int> Facade::GetPath() { return path_; }

void Facade::ResetPath() { path_.clear(); }

bool Facade::IsEmptyPath() { return path_.empty(); }

//////////////////////////////////////////////////////////////// MATRIX
Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw std::out_of_range(
        "Incorrect input, rows and cols of matrix values must be > 0");
  matrix_ = new int[rows_ * cols_]();
}
Matrix::Matrix(const Matrix& other) : Matrix(other.rows_, other.cols_) {
  delete[] matrix_;
  matrix_ = new int[rows_ * cols_]();
  memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(int));
}
Matrix::Matrix(Matrix&& other) noexcept {
  matrix_ = nullptr;
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}
Matrix::~Matrix() { delete[] matrix_; }

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;

    delete[] matrix_;
    matrix_ = new int[rows_ * cols_]();
    memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(int));
  }

  return *this;
}
Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }

  return *this;
}
int& Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw std::out_of_range("Incorrect input, index of matrix is out of range");
  }
  return matrix_[i * cols_ + j];
}

int Matrix::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_) {
    throw std::out_of_range("Incorrect input, index of matrix is out of range");
  }
  return matrix_[i * cols_ + j];
}

int Matrix::Rows() const { return rows_; }
int Matrix::Cols() const { return cols_; }
void Matrix::SetRows(int rows) {
  if (rows == rows_) return;
  if (rows <= 0) {
    throw std::out_of_range("Incorrect input, rows value must be > 0");
  }

  int* matrix_old = matrix_;
  int min_rows = rows < rows_ ? rows : rows_;

  matrix_ = new int[rows * cols_]();
  memcpy(matrix_, matrix_old, min_rows * cols_ * sizeof(int));
  rows_ = rows;
  delete[] matrix_old;
}
void Matrix::SetCols(int cols) {
  if (cols == cols_) return;
  if (cols <= 0) {
    throw std::out_of_range("Incorrect input, cols value must be > 0");
  }

  int* matrix_old = matrix_;
  int min_cols = cols < cols_ ? cols : cols_;
  matrix_ = new int[rows_ * cols]();
  for (int i = 0; i < rows_; ++i) {
    int* dest = matrix_ + i * cols;
    int* src = matrix_old + i * cols_;
    memcpy(dest, src, min_cols * sizeof(int));
  }
  cols_ = cols;
  delete[] matrix_old;
}

//////////////////////////////////////////////////////////////// ELLER
Maze Eller::GetMaze() { return maze_; }

Eller::Eller(int rows, int cols)
    : unique_set_(0),
      maze_(rows, cols),
      rows_(rows),
      cols_(cols),
      set_matrix_(rows, cols) {}

void Eller::Generate() {
  srand(time(0));
  FirstRowEmptyVallue();
  for (int i = 0; i < rows_ - 1; i++) {
    AssignUniqueSet(i);
    AddVerticalWalls(i);
    AddHorizontalWalls(i);
    CheckHorizontalWalls(i);
    NextLineFilling(i);
  }
  LastRow();
}

void Eller::LastRow() {
  for (int i = 0; i < cols_; i++) {
    maze_(Maze::Vh::kHorizontal, rows_ - 1, i) = true;
  }
  AssignUniqueSet(rows_ - 1);
  AddVerticalWalls(rows_ - 1);
  LastRowVerticalWallsCheck();
}

void Eller::LastRowVerticalWallsCheck() {
  for (int i = 0; i < cols_ - 1; i++) {
    if (set_matrix_(rows_ - 1, i) != set_matrix_(rows_ - 1, i + 1)) {
      maze_(Maze::Vh::kVertical, rows_ - 1, i) = false;
      MergeSet(rows_ - 1, set_matrix_(rows_ - 1, i),
               set_matrix_(rows_ - 1, i + 1));
    }
  }
}

void Eller::MergeSet(int row, int set, int change) {
  for (int i = 0; i < cols_; i++) {
    if (set_matrix_(row, i) == change) {
      set_matrix_(row, i) = set;
    }
  }
}

void Eller::NextLineFilling(int row) {
  for (int i = 0; i < cols_; i++) {
    if (maze_(Maze::Vh::kHorizontal, row, i) == true) {
      set_matrix_(row + 1, i) = 0;
    } else {
      set_matrix_(row + 1, i) = set_matrix_(row, i);
    }
  }
}

void Eller::CheckHorizontalWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    if (CalculateHorizontalWalls(row, set_matrix_(row, i)) == 0) {
      maze_(Maze::Vh::kHorizontal, row, i) = false;
    }
  }
}

int Eller::CalculateHorizontalWalls(int row, int set) {
  int count = 0;
  for (int i = 0; i < cols_; i++) {
    if (set_matrix_(row, i) == set &&
        maze_(Maze::Vh::kHorizontal, row, i) == false) {
      count++;
    }
  }
  return count;
}

void Eller::AddHorizontalWalls(int row) {
  for (int i = 0; i < cols_; i++) {
    bool wall = rand() % 2;
    if (wall == true && CalculateUniqueSet(set_matrix_(row, i), row) != 1) {
      maze_(Maze::Vh::kHorizontal, row, i) = true;
    }
  }
}

int Eller::CalculateUniqueSet(int set, int row) {
  int count = 0;
  for (int i = 0; i < cols_; i++) {
    if (set_matrix_(row, i) == set) count++;
  }
  return count;
}

void Eller::AddVerticalWalls(int row) {
  for (int i = 0; i < cols_ - 1; i++) {
    bool wall = rand() % 2;
    if (wall == true || set_matrix_(row, i) == set_matrix_(row, i + 1)) {
      maze_(Maze::Vh::kVertical, row, i) = true;
    } else {
      MergeSet(row, set_matrix_(row, i), set_matrix_(row, i + 1));
    }
  }
  maze_(Maze::Vh::kVertical, row, cols_ - 1) = true;
}

void Eller::AssignUniqueSet(int row) {
  for (int i = 0; i < cols_; i++) {
    if (set_matrix_(row, i) == 0) {
      unique_set_++;
      set_matrix_(row, i) = unique_set_;
    }
  }
}

void Eller::FirstRowEmptyVallue() {
  for (int i = 0; i < cols_; i++) {
    set_matrix_(0, i) = 0;
  }
}

}  // namespace s21
