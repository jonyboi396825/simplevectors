#include "simplevectors/vectors.hpp"

#include <array>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 M_PI / 2
#endif

#ifndef M_PI_4
#define M_PI_4 M_PI / 4
#endif

#include <gtest/gtest.h>

TEST(MakeVectorTestUtil, MakeVectorArray) {
  std::array<double, 5> arr = {{1, 2, 3, 5, 2}};
  svector::Vector<5> vec = svector::makeVector(arr);
  svector::Vector<5> control = {1, 2, 3, 5, 2};
  EXPECT_EQ(vec, control);

  std::array<double, 2> arr2 = {{1, 5}};
  svector::Vector2D vec2 = svector::makeVector(arr2);
  svector::Vector2D control2 = {1, 5};
  EXPECT_EQ(vec2, control2);
}

TEST(MakeVectorTestUtil, MakeVectorVector) {
  std::vector<double> arr = {{1, 2, 3, 5, 2}};
  svector::Vector<3> vec = svector::makeVector<3>(arr);
  svector::Vector<3> control = {1, 2, 3};
  EXPECT_EQ(vec, control);

  std::vector<double> arr2 = {1};
  svector::Vector2D vec2 = svector::makeVector<2>(arr2);
  svector::Vector2D control2 = {1, 0};
  EXPECT_EQ(vec2, control2);
}

TEST(MakeVectorTestUtil, MakeVectorInitializerList) {
  svector::Vector<5> v = svector::makeVector<5, double>({3, 5, 2, 3.5, 6});
  EXPECT_EQ(v[0], 3);
  EXPECT_EQ(v[1], 5);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3.5);
  EXPECT_EQ(v[4], 6);
}

TEST(MakeVectorTestUtil, MakeVectorInitializerListTooFew) {
  svector::Vector<5> v2 = svector::makeVector<5, double>({3, 5, 2});
  EXPECT_EQ(v2[0], 3);
  EXPECT_EQ(v2[1], 5);
  EXPECT_EQ(v2[2], 2);
  EXPECT_EQ(v2[3], 0);
  EXPECT_EQ(v2[4], 0);
}

TEST(MakeVectorTestUtil, MakeVectorInitializerListTooMany) {
  svector::Vector<5> v3 =
      svector::makeVector<5, double>({3, 5, 2, 3.5, 6, 39, 2, 6});
  EXPECT_EQ(v3[0], 3);
  EXPECT_EQ(v3[1], 5);
  EXPECT_EQ(v3[2], 2);
  EXPECT_EQ(v3[3], 3.5);
  EXPECT_EQ(v3[4], 6);
}

TEST(OperatorTestUtil, DotTest2D) {
  svector::Vector2D lhs(2, 5);
  svector::Vector2D rhs(-3, -4);

  double product = svector::dot(lhs, rhs);
  double product2 = svector::dot(rhs, lhs);
  EXPECT_EQ(product, -26);
  EXPECT_EQ(product2, product);
}

TEST(OperatorTestUtil, DotTest3D) {
  svector::Vector3D lhs(2, 5, 6);
  svector::Vector3D rhs(-3, -4, 2);

  double product = svector::dot(lhs, rhs);
  double product2 = svector::dot(rhs, lhs);
  EXPECT_EQ(product, -14);
  EXPECT_EQ(product, product2);
}

TEST(OperatorTestUtil, CrossProduct) {
  svector::Vector3D v1(2, 3, 5);
  svector::Vector3D v2(1, 2, 3);
  svector::Vector3D res(-1, -1, 1);

  EXPECT_EQ(svector::cross(v1, v2), res);
  EXPECT_EQ(svector::cross(v2, v1), -res);
}

TEST(XYMagnitudeTestUtil, TestMagnitudeGivenXY) {
  svector::Vector2D vector(4.612, -3.322);
  double magn = svector::magn(vector);
  double magn_r = std::round(magn * 1000.0) / 1000.0;

  EXPECT_EQ(magn_r, 5.684);
}

TEST(XYMagnitudeTestUtil, TestMagnitudeGivenXYZ) {
  svector::Vector3D vector(4.612, -3.322, 2.552);
  double magn = svector::magn(vector);
  double magn_r = std::round(magn * 1000.0) / 1000.0;

  EXPECT_EQ(magn_r, 6.230);
}

TEST(NormalizeTestUtil, TestNormalize2D) {
  svector::Vector2D vector(3, 4);
  vector = svector::normalize(vector);

  EXPECT_EQ(vector, svector::Vector2D(0.6, 0.8));
}

TEST(NormalizeTestUtil, TestNormalize3D) {
  svector::Vector3D vector(2, -3, -6);
  vector = svector::normalize(vector);

  EXPECT_EQ(vector, svector::Vector3D(2 / 7.0, -3 / 7.0, -6 / 7.0));
}

TEST(XYZTestUtil, GetTest2D) {
  svector::Vector2D v(3, 5);
  EXPECT_EQ(svector::x(v), 3);
  EXPECT_EQ(svector::y(v), 5);
}

TEST(XYZTestUtil, SetTest2D) {
  svector::Vector2D v;

  svector::x(v, 3);
  svector::y(v, 5);

  EXPECT_EQ(svector::x(v), 3);
  EXPECT_EQ(svector::y(v), 5);
}

TEST(XYZTestUtil, GetTest3D) {
  svector::Vector3D v(3, 5, 6);
  EXPECT_EQ(svector::x(v), 3);
  EXPECT_EQ(svector::y(v), 5);
  EXPECT_EQ(svector::z(v), 6);
}

TEST(XYZTestUtil, SetTest3D) {
  svector::Vector3D v;

  svector::x(v, 3);
  svector::y(v, 5);
  svector::z(v, 6);

  EXPECT_EQ(svector::x(v), 3);
  EXPECT_EQ(svector::y(v), 5);
  EXPECT_EQ(svector::z(v), 6);
}

TEST(AngleTestUtil, AngleTest2D) {
  std::vector<std::vector<double>> tests{
      {4.5, 2.3, 0.472},
      {-3.4, 5.44, 2.129},
      {-0.35, -4.44, -1.649},
      {6.2, -3, -0.451},
  };

  for (const auto &testcase : tests) {
    svector::Vector2D vector(testcase[0], testcase[1]);
    double ang = svector::angle(vector);
    double ang_r = std::round(ang * 1000.0) / 1000.0;

    EXPECT_EQ(ang_r, testcase[2]);
  }
}

TEST(AngleTestUtil, AlphaTest) {
  svector::Vector3D vector(-3, 2, -6);
  double ang = svector::alpha(vector);
  double ang_r = std::round(ang * 1000.0) / 1000.0;

  EXPECT_EQ(ang_r, 2.014);
}

TEST(AngleTestUtil, BetaTest) {
  svector::Vector3D vector(-3, 2, -6);
  double ang = svector::beta(vector);
  double ang_r = std::round(ang * 1000.0) / 1000.0;

  EXPECT_EQ(ang_r, 1.281);
}

TEST(AngleTestUtil, GammaTest) {
  svector::Vector3D vector(-3, 2, -6);
  double ang = svector::gamma(vector);
  double ang_r = std::round(ang * 1000.0) / 1000.0;

  EXPECT_EQ(ang_r, 2.600);
}

TEST(RotationTestUtil, RotateTest2D) {
  std::vector<std::vector<double>> tests{
      {1, 0, M_PI / 6, 0.866, 0.5},     {1, 1, M_PI / 4, 0, 1.414},
      {1.732, 1, M_PI / 3, 0, 2},       {0, 1, M_PI / 4, -0.707, 0.707},
      {-1, 0, M_PI / 3, -0.5, -0.866},  {-0.5, -0.866, M_PI / 6, 0, -1},
      {0, -1, M_PI / 4, 0.707, -0.707}, {0.707, -0.707, M_PI / 4, 1, 0},
  };

  for (const auto &testcase : tests) {
    svector::Vector2D vector(testcase[0], testcase[1]);
    svector::Vector2D vectorp(testcase[3], testcase[4]);

    svector::Vector2D rotated = svector::rotate(vector, testcase[2]);

    EXPECT_EQ(std::round(vectorp.x() * 1000) / 1000,
              std::round(rotated.x() * 1000) / 1000);
    EXPECT_EQ(std::round(vectorp.y() * 1000) / 1000,
              std::round(rotated.y() * 1000) / 1000);
  }
}

TEST(RotationTestUtil, AlphaRotation) {
  std::vector<std::vector<double>> tests{
      {3, 4, 0, M_PI / 2, 3, 0, 4},
      {3, 4, 0, -M_PI / 2, 3, 0, -4},
      {3, 2.8284, 2.8284, M_PI / 4, 3, 0, 4},
      {3, 2.8284, 2.8284, -M_PI / 4, 3, 4, 0}};

  for (const auto &testcase : tests) {
    svector::Vector3D vector(testcase[0], testcase[1], testcase[2]);
    svector::Vector3D vectorp(testcase[4], testcase[5], testcase[6]);

    svector::Vector3D rotated = svector::rotateAlpha(vector, testcase[3]);

    EXPECT_EQ(std::round(vectorp.x() * 1000) / 1000,
              std::round(rotated.x() * 1000) / 1000);
    EXPECT_EQ(std::round(vectorp.y() * 1000) / 1000,
              std::round(rotated.y() * 1000) / 1000);
    EXPECT_EQ(std::round(vectorp.z() * 1000) / 1000,
              std::round(rotated.z() * 1000) / 1000);
  }
}

TEST(RotationTestUtil, BetaRotation) {
  std::vector<std::vector<double>> tests{
      {4, 3, 0, M_PI / 2, 0, 3, -4},
      {4, 3, 0, -M_PI / 2, 0, 3, 4},
      {2.8284, 3, 2.8284, M_PI / 4, 4, 3, 0},
      {2.8284, 3, 2.8284, -M_PI / 4, 0, 3, 4}};

  for (const auto &testcase : tests) {
    svector::Vector3D vector(testcase[0], testcase[1], testcase[2]);
    svector::Vector3D vectorp(testcase[4], testcase[5], testcase[6]);

    svector::Vector3D rotated = svector::rotateBeta(vector, testcase[3]);

    EXPECT_EQ(std::round(vectorp.x() * 1000) / 1000,
              std::round(rotated.x() * 1000) / 1000);
    EXPECT_EQ(std::round(vectorp.y() * 1000) / 1000,
              std::round(rotated.y() * 1000) / 1000);
    EXPECT_EQ(std::round(vectorp.z() * 1000) / 1000,
              std::round(rotated.z() * 1000) / 1000);
  }
}

TEST(RotationTestUtil, GammaRotation) {
  std::vector<std::vector<double>> tests{
      {1, 0, 3, M_PI / 6, 0.866, 0.5, 3},
      {1, 1, 3, M_PI / 4, 0, 1.414, 3},
      {1.732, 1, 3, M_PI / 3, 0, 2, 3},
      {0, 1, 3, M_PI / 4, -0.707, 0.707, 3},
      {-1, 0, 3, M_PI / 3, -0.5, -0.866, 3},
      {-0.5, -0.866, 3, M_PI / 6, 0, -1, 3},
      {0, -1, 3, M_PI / 4, 0.707, -0.707, 3},
      {0.707, -0.707, 3, M_PI / 4, 1, 0, 3},
  };

  for (const auto &testcase : tests) {
    svector::Vector3D vector(testcase[0], testcase[1], testcase[2]);
    svector::Vector3D vectorp(testcase[4], testcase[5], testcase[6]);

    svector::Vector3D rotated = svector::rotateGamma(vector, testcase[3]);

    EXPECT_EQ(std::round(vectorp.x() * 1000) / 1000,
              std::round(rotated.x() * 1000) / 1000);
    EXPECT_EQ(std::round(vectorp.y() * 1000) / 1000,
              std::round(rotated.y() * 1000) / 1000);
    EXPECT_EQ(std::round(vectorp.z() * 1000) / 1000,
              std::round(rotated.z() * 1000) / 1000);
  }
}

TEST(IsZeroTestUtil, IsZeroTestNonZeroDimensionVector) {
  svector::Vector<5> v{2, 5, 3};
  EXPECT_TRUE(!svector::isZero(v));

  svector::Vector<5> v2{0};
  EXPECT_TRUE(svector::isZero(v2));
}

TEST(IsZeroTestUtil, IsZeroTestZeroDimensionVector) {
  svector::Vector<0> v;
  EXPECT_TRUE(svector::isZero(v));
}
