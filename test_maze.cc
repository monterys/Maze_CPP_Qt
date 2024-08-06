#include "gtest/gtest.h"
#include "maze.h"

TEST(TestReadMaze, Test1) {
  s21::Maze maze;
  EXPECT_EQ(maze.Rows(), 0);
  EXPECT_EQ(maze.Cols(), 0);
  maze.ReadMaze("maze_4x4.txt");
  EXPECT_EQ(maze.Rows(), 4);
  EXPECT_EQ(maze.Cols(), 4);

  int expected_v[4][4] = {
      {0, 0, 0, 1}, {1, 0, 1, 1}, {0, 1, 0, 1}, {0, 0, 0, 1}};
  int expected_h[4][4] = {
      {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 1, 0, 1}, {1, 1, 1, 1}};
  for (int i = 0; i < maze.Rows(); ++i) {
    for (int j = 0; j < maze.Cols(); ++j) {
      EXPECT_EQ(maze(s21::Maze::Vh::kVertical, i, j), expected_v[i][j]);
      EXPECT_EQ(maze(s21::Maze::Vh::kHorizontal, i, j), expected_h[i][j]);
    }
  }
  const s21::Maze maze2 = maze;
  for (int i = 0; i < maze.Rows(); ++i) {
    for (int j = 0; j < maze.Cols(); ++j) {
      EXPECT_EQ(maze2(s21::Maze::Vh::kVertical, i, j), expected_v[i][j]);
      EXPECT_EQ(maze2(s21::Maze::Vh::kHorizontal, i, j), expected_h[i][j]);
    }
  }
  maze(s21::Maze::Vh::kVertical, 0, 0) = 1;
  EXPECT_EQ(maze(s21::Maze::Vh::kVertical, 0, 0), 1);
  maze2.WriteMaze("maze_test_write");
  maze.Generate(5, 6);
  s21::Maze maze_read("maze_test_write");
  EXPECT_THROW(s21::Maze maze(-5, -6), std::out_of_range);
  EXPECT_THROW(maze(s21::Maze::Vh::kVertical, 5, 6), std::out_of_range);
  EXPECT_THROW(maze2(s21::Maze::Vh::kVertical, 5, 6), std::out_of_range);
  EXPECT_THROW(maze.ReadMaze("maze_invalid.txt"), std::out_of_range);
}

TEST(TestReadMaze, Test2) {
  s21::Maze maze;
  maze.ReadMaze("maze_10x10.mz");
  EXPECT_EQ(maze.Rows(), 10);
  EXPECT_EQ(maze.Cols(), 10);

  int expected_v[10][10] = {
      {0, 0, 1, 0, 0, 0, 0, 1, 0, 1}, {0, 1, 1, 1, 0, 0, 0, 1, 1, 1},
      {1, 0, 1, 0, 0, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
      {0, 0, 1, 0, 1, 0, 1, 0, 1, 1}, {1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
      {0, 0, 0, 1, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
      {1, 0, 0, 0, 1, 1, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 1, 0, 0, 0, 1}};
  int expected_h[10][10] = {
      {0, 1, 0, 0, 0, 1, 1, 1, 0, 0}, {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 0, 0, 1, 0},
      {1, 0, 1, 1, 1, 0, 1, 1, 1, 0}, {0, 1, 1, 1, 0, 1, 0, 0, 0, 0},
      {1, 1, 0, 1, 0, 0, 1, 0, 1, 1}, {0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
      {1, 0, 1, 0, 0, 0, 0, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  for (int i = 0; i < maze.Rows(); ++i) {
    for (int j = 0; j < maze.Cols(); ++j) {
      EXPECT_EQ(maze(s21::Maze::Vh::kVertical, i, j), expected_v[i][j]);
      EXPECT_EQ(maze(s21::Maze::Vh::kHorizontal, i, j), expected_h[i][j]);
    }
  }

#ifdef DEBUG
  maze.PrintMaze();
#endif  // DEBUG
}

TEST(TestReadMaze, Test3) {
  s21::Maze maze;
  maze.ReadMaze("maze_20x20.mz");
  EXPECT_EQ(maze.Rows(), 20);
  EXPECT_EQ(maze.Cols(), 20);

  int expected_v[20][20] = {
      {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1},
      {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
      {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
      {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
      {0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
      {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1},
      {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
      {0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
      {0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1},
      {1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
      {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1},
      {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
  int expected_h[20][20] = {
      {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
      {1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
      {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
      {0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1},
      {0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0},
      {1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0},
      {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
      {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
      {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
      {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0},
      {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
      {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  for (int i = 0; i < maze.Rows(); ++i) {
    for (int j = 0; j < maze.Cols(); ++j) {
      EXPECT_EQ(maze(s21::Maze::Vh::kVertical, i, j), expected_v[i][j]);
      EXPECT_EQ(maze(s21::Maze::Vh::kHorizontal, i, j), expected_h[i][j]);
    }
  }
#ifdef DEBUG
  maze.PrintMaze();
#endif  // DEBUG
}

TEST(TestMatrix, Test1) {
  s21::Matrix matrix(4, 4);
  EXPECT_EQ(matrix.Rows(), 4);
  EXPECT_EQ(matrix.Cols(), 4);
  s21::Matrix matrix1 = matrix;
  s21::Matrix matrix2 = std::move(matrix1);
  matrix2 = matrix;
  matrix = std::move(matrix2);
  EXPECT_THROW(s21::Matrix m(-1, -2), std::out_of_range);
  EXPECT_THROW(matrix(-1, -2), std::out_of_range);
  EXPECT_THROW(matrix.SetRows(-2), std::out_of_range);
  EXPECT_THROW(matrix.SetCols(-2), std::out_of_range);
  const s21::Matrix matrix_const = matrix;
  EXPECT_THROW(matrix_const(-1, -2), std::out_of_range);
}

TEST(TestFacade, Test1) {
  s21::Facade facade("maze_4x4.txt");
  EXPECT_EQ(facade.Rows(), 4);
  EXPECT_EQ(facade.Cols(), 4);

  int expected_v[4][4] = {
      {0, 0, 0, 1}, {1, 0, 1, 1}, {0, 1, 0, 1}, {0, 0, 0, 1}};
  int expected_h[4][4] = {
      {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 1, 0, 1}, {1, 1, 1, 1}};
  for (int i = 0; i < facade.Rows(); ++i) {
    for (int j = 0; j < facade.Cols(); ++j) {
      EXPECT_EQ(facade(s21::Maze::Vh::kVertical, i, j), expected_v[i][j])
          << i << j;
      EXPECT_EQ(facade(s21::Maze::Vh::kHorizontal, i, j), expected_h[i][j]);
    }
  }
}

TEST(TestFacade, Test2) {
  s21::Facade facade;
  facade.ReadMaze("maze_10x10.mz");
  EXPECT_EQ(facade.Rows(), 10);
  EXPECT_EQ(facade.Cols(), 10);
  int expected_v[10][10] = {
      {0, 0, 1, 0, 0, 0, 0, 1, 0, 1}, {0, 1, 1, 1, 0, 0, 0, 1, 1, 1},
      {1, 0, 1, 0, 0, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
      {0, 0, 1, 0, 1, 0, 1, 0, 1, 1}, {1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
      {0, 0, 0, 1, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
      {1, 0, 0, 0, 1, 1, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 1, 0, 0, 0, 1}};
  int expected_h[10][10] = {
      {0, 1, 0, 0, 0, 1, 1, 1, 0, 0}, {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 0, 0, 1, 0},
      {1, 0, 1, 1, 1, 0, 1, 1, 1, 0}, {0, 1, 1, 1, 0, 1, 0, 0, 0, 0},
      {1, 1, 0, 1, 0, 0, 1, 0, 1, 1}, {0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
      {1, 0, 1, 0, 0, 0, 0, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  for (int i = 0; i < facade.Rows(); ++i) {
    for (int j = 0; j < facade.Cols(); ++j) {
      EXPECT_EQ(facade(s21::Maze::Vh::kVertical, i, j), expected_v[i][j]);
      EXPECT_EQ(facade(s21::Maze::Vh::kHorizontal, i, j), expected_h[i][j]);
    }
  }
}

TEST(TestFacade, Test3) {
  s21::Facade facade;
  facade.ReadMaze("maze_20x20.mz");
  EXPECT_EQ(facade.Rows(), 20);
  EXPECT_EQ(facade.Cols(), 20);
  int expected_v[20][20] = {
      {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1},
      {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
      {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
      {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
      {0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
      {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1},
      {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
      {0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
      {0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1},
      {1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
      {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1},
      {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
  int expected_h[20][20] = {
      {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
      {1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
      {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
      {0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1},
      {0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0},
      {1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0},
      {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
      {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
      {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
      {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0},
      {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
      {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  for (int i = 0; i < facade.Rows(); ++i) {
    for (int j = 0; j < facade.Cols(); ++j) {
      EXPECT_EQ(facade(s21::Maze::Vh::kVertical, i, j), expected_v[i][j]);
      EXPECT_EQ(facade(s21::Maze::Vh::kHorizontal, i, j), expected_h[i][j]);
    }
  }
}

TEST(TestGenerteMaze, Test1) {
  s21::Facade facade;
  EXPECT_EQ(facade.Rows(), 0);
  EXPECT_EQ(facade.Cols(), 0);

  facade.ReadMaze("maze_20x20.mz");
  EXPECT_EQ(facade.Rows(), 20);
  EXPECT_EQ(facade.Cols(), 20);

  facade.GenerateMaze(4, 4);
  EXPECT_EQ(facade.Rows(), 4);
  EXPECT_EQ(facade.Cols(), 4);
}

TEST(TestPath, Test1) {
  s21::Facade facade;
  EXPECT_EQ(facade.Rows(), 0);
  EXPECT_EQ(facade.Cols(), 0);

  facade.ReadMaze("maze_4x4.txt");
  EXPECT_EQ(facade.Rows(), 4);
  EXPECT_EQ(facade.Cols(), 4);

  facade.GeneratePath(0, 0, 2, 2);
  std::vector<int> path = facade.GetPath();
  int expected_path[] = {2, 2, 3, 2, 3, 1, 3, 0, 2, 0, 1, 0, 0, 0};
  int i = 0;
  for (auto p : path) {
    EXPECT_EQ(p, expected_path[i++]);
  }
}

TEST(TestPath, Test2) {
  s21::Facade facade;
  EXPECT_EQ(facade.Rows(), 0);
  EXPECT_EQ(facade.Cols(), 0);

  facade.ReadMaze("maze_4x4.txt");
  EXPECT_EQ(facade.Rows(), 4);
  EXPECT_EQ(facade.Cols(), 4);

  facade.GeneratePath(3, 3, 0, 0);
  std::vector<int> path = facade.GetPath();
  int expected_path[] = {0, 0, 1, 0, 2, 0, 3, 0, 3, 1, 3, 2, 2, 2, 2, 3, 3, 3};
  int i = 0;
  for (auto p : path) {
    EXPECT_EQ(p, expected_path[i++]);
  }
}

TEST(TestPath, Test3) {
  s21::Facade facade;
  EXPECT_EQ(facade.Rows(), 0);
  EXPECT_EQ(facade.Cols(), 0);

  facade.ReadMaze("maze_10x10.mz");
  EXPECT_EQ(facade.Rows(), 10);
  EXPECT_EQ(facade.Cols(), 10);

  facade.GeneratePath(0, 0, 4, 6);
  std::vector<int> path = facade.GetPath();
  int expected_path[] = {4, 6, 4, 5, 5, 5, 5, 4, 6, 4, 6, 3, 5,
                         3, 4, 3, 4, 4, 3, 4, 3, 3, 2, 3, 1, 3,
                         1, 2, 2, 2, 2, 1, 2, 0, 1, 0, 0, 0};
  int i = 0;
  for (auto p : path) {
    EXPECT_EQ(p, expected_path[i++]);
  }
  EXPECT_FALSE(facade.IsEmptyPath());
  facade.ResetPath();
  EXPECT_TRUE(facade.IsEmptyPath());
}

TEST(TestPath, Test4) {
  s21::Facade facade;
  EXPECT_EQ(facade.Rows(), 0);
  EXPECT_EQ(facade.Cols(), 0);

  facade.ReadMaze("maze_3x4.txt");
  EXPECT_EQ(facade.Rows(), 3);
  EXPECT_EQ(facade.Cols(), 4);
  const s21::Facade facade_const = facade;
  EXPECT_EQ(facade_const(s21::Maze::Vh::kVertical, 0, 0), 1);
  facade.WriteMaze("maze_test_write");
  facade.ReadMaze("maze_test_write");

  EXPECT_THROW(facade.GeneratePath(0, 0, 2, 3), std::out_of_range);
}

TEST(EllerGenerate, Test1) {
  s21::Eller el(5, 5);
  el.Generate();
  s21::Path p(el.GetMaze());
  EXPECT_NO_THROW(for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
          if (i != x && j != y) {
            p.GeneratePath(i, j, x, y);
          }
        }
      }
    }
  });
}

TEST(EllerGenerate, Test2) {
  s21::Eller el(7, 8);
  el.Generate();
  s21::Path p(el.GetMaze());
  EXPECT_NO_THROW(for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
          if (i != x && j != y) {
            p.GeneratePath(i, j, x, y);
          }
        }
      }
    }
  });
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
