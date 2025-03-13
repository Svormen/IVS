//======== Copyright (c) 2020, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Slavomir Svorada <xsvora02@stud.fit.vutbr.cz>
// $Date:       $2020-03-03
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Slavomir Svorada
 *
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"
#include <math.h>
#include <vector>

//============================================================================//
// ** ZDE DOPLNTE TESTY **
namespace white_box_testing
{
  using namespace ::testing;

  class TestMatrix : public Test
  {
  protected:
    Matrix matrix;

    Matrix get1x1Matrix()
    {
      return Matrix();
    }

    void set1x1Matrix()
    {
      matrix = get1x1Matrix();
    }

    Matrix get4x4Matrix()
    {
      Matrix matrix = Matrix(4,4);
      matrix.set(std::vector<std::vector<double>> {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {-1, -2, -3, -4},
        {-5, -6, -7, -8},
      });
      return matrix;
    }

    void set4x4Matrix()
    {
      matrix = get4x4Matrix();
    }

    Matrix get4x2Matrix()
    {
      Matrix matrix = Matrix(4,2);
      matrix.set(std::vector<std::vector<double>> {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8},
      });
      return matrix;
    }

    void set4x2Matrix()
    {
      matrix = get4x2Matrix();
    }

    Matrix get2x4Matrix()
    {
      Matrix matrix = Matrix(2,4);
      matrix.set(std::vector<std::vector<double>> {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
      });
      return matrix;
    }

    void set2x4Matrix()
    {
      matrix = get2x4Matrix();
    }
  };

  TEST_F(TestMatrix, Conctruct)
  {
    EXPECT_NO_THROW(Matrix());
    EXPECT_NO_THROW(Matrix(1,2));
    EXPECT_NO_THROW(Matrix(23,48));
    EXPECT_NO_THROW(Matrix(180,250));

    EXPECT_ANY_THROW(Matrix(0,0));
    EXPECT_ANY_THROW(Matrix(23,0));
    EXPECT_ANY_THROW(Matrix(0,23));

  }

  TEST_F(TestMatrix, set1x1Matrix)
  {
    set1x1Matrix();

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{0}}));
    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{3}}));
    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{2.3}}));
    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{-123}}));
    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {{1234}}));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {{}}));
    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {{0,0}}));
    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {{2,3}}));
    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {{23,23}}));
  }

  TEST_F(TestMatrix, set4x4Matrix)
  {
    set4x4Matrix();

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
      {2, 3.5, 30, 4.2},
      {5600, 600, 7.8, 8.2},
      {-100, -2.5, -30, -4},
      {-5.5, -66, -77, -8.8},
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
      {2, 3.5, 30, 4.2,5},
      {5600, 600, 7.8, 8.2},
      {-100, -2.5, -30, -4},
      {-5.5, -66, -77, -8.8},
    }));
  }

  TEST_F(TestMatrix, set2x4Matrix)
  {
    set2x4Matrix();

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>>{
      {
        {1.8, 2.65, 300, 4425},
        {5.008, 600, 778, -888},
      }
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>>{
      {
        {1.8, 2.65, 300, 4425},
        {5.008, 600, 778, 598, 8},
        {5, 85, 23, 88},
      }
    }));
  }

  TEST_F(TestMatrix, set4x2Matrix)
  {
    set4x2Matrix();

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
      {
        {1.2, -800},
        {258, 259},
        {0.9, 999},
        {635, -23},
      }
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
      {
        {1.2, -800},
        {258, 259},
        {0.9, 999},
        {635, -23},
        {23, 87},
      }
    }));
  }

  TEST_F(TestMatrix, Equal)
  {
    Matrix matrix1x1 = get1x1Matrix();
    Matrix matrix4x4 = get4x4Matrix();
    Matrix matrix4x2 = get4x2Matrix();
    Matrix matrix2x4 = get2x4Matrix();

    Matrix newmatrix4x4 = Matrix(4,4);
    newmatrix4x4.set(std::vector<std::vector<double>> {
      {-1, -2, -3, -4},
      {-5, -6, -7, -8},
      {1, 2, 3, 4},
      {5, 6, 7, 8},
    });
    Matrix newmatrix2x4 = Matrix(2,4);
    newmatrix2x4.set(std::vector<std::vector<double>> {
      {-1, -2, -3, -4},
      {-5, -6, -7, -8},
    });

    EXPECT_ANY_THROW(matrix1x1 == matrix4x4);
    EXPECT_ANY_THROW(matrix2x4 == matrix4x2);

    EXPECT_TRUE(matrix1x1 == matrix1x1);
    EXPECT_TRUE(matrix2x4 == matrix2x4);
    EXPECT_TRUE(matrix4x4 == matrix4x4);

    EXPECT_FALSE(newmatrix4x4 == matrix4x4);
    EXPECT_FALSE(newmatrix2x4 == matrix2x4);
  }

  TEST_F(TestMatrix, Plus)
  {
    Matrix matrix1x1 = get1x1Matrix();
    Matrix matrix4x4 = get4x4Matrix();
    Matrix matrix4x2 = get4x2Matrix();
    Matrix matrix2x4 = get2x4Matrix();

    matrix1x1 = matrix1x1 + matrix1x1;
    matrix4x4 = matrix4x4 + matrix4x4;
    matrix2x4 = matrix2x4 + matrix2x4;
    matrix4x2 = matrix4x2 + matrix4x2;

    Matrix newmatrix4x4 = Matrix(4,4);
    newmatrix4x4.set(std::vector<std::vector<double>> {
      {2, 4, 6, 8},
      {10, 12, 14, 16},
      {-2, -4, -6, -8},
      {-10, -12, -14, -16},
    });

    Matrix newmatrix2x4 = Matrix(2,4);
    newmatrix2x4.set(std::vector<std::vector<double>> {
      {2, 4, 6, 8},
      {10, 12, 14, 16},
    });

    Matrix newmatrix4x2 = Matrix(4,2);
    newmatrix4x2.set(std::vector<std::vector<double>> {
      {-1, -2},
      {-3, -4},
      {-5, -6},
      {-7, -8},
    });

    EXPECT_ANY_THROW(matrix1x1 + matrix4x4);
    EXPECT_ANY_THROW(matrix2x4 + matrix4x2);

    EXPECT_TRUE(newmatrix4x4 == matrix4x4);
    EXPECT_TRUE(newmatrix2x4 == matrix2x4);

    EXPECT_FALSE(newmatrix4x2 == matrix4x2);
  }

  TEST_F(TestMatrix, Multiple)
  {
    Matrix matrix1x1 = get1x1Matrix();
    Matrix matrix4x4 = get4x4Matrix();
    Matrix matrix4x2 = get4x2Matrix();
    Matrix matrix2x4 = get2x4Matrix();
    Matrix matrix2x4_4x2;
    Matrix matrix4x2_2x4;

    matrix1x1 = (matrix1x1 * matrix1x1);
    matrix4x4 = (matrix4x4 * matrix4x4);
    matrix2x4_4x2 = (matrix2x4 * matrix4x2);
    matrix4x2_2x4 = (matrix4x2 * matrix2x4);

    Matrix newmatrix4x4 = Matrix(4,4);
    newmatrix4x4.set(std::vector<std::vector<double>> {
      {-12, -16, -20, -24},
      {-12, -16, -20, -24},
      {12, 16, 20, 24},
      {12, 16, 20, 24},
    });

    Matrix newmatrix2x4_4x2 = Matrix(2,2);
    newmatrix2x4_4x2.set(std::vector<std::vector<double>> {
      {50, 60},
      {114, 140},
    });

    Matrix newmatrix4x2_2x4 = Matrix(4,4);
    newmatrix4x2_2x4.set(std::vector<std::vector<double>> {
      {-11, -14, -17, -20},
      {23, 30, 37, 44},
      {35, 46, 57, 68},
      {47, 62, 77, 92},
    });

    EXPECT_ANY_THROW(matrix4x2 * matrix4x4);
    EXPECT_ANY_THROW(matrix1x1 * matrix2x4);

    EXPECT_TRUE(newmatrix4x4 == matrix4x4);
    EXPECT_TRUE(newmatrix2x4_4x2 == matrix2x4_4x2);

    EXPECT_FALSE(newmatrix4x2_2x4 == matrix4x2_2x4);
  }

  TEST_F(TestMatrix, MultipleConst)
  {
    Matrix matrix1x1 = get1x1Matrix();
    Matrix matrix4x4 = get4x4Matrix();
    Matrix matrix4x2 = get4x2Matrix();
    Matrix matrix2x4 = get2x4Matrix();

    matrix1x1 = matrix1x1 * 10;
    matrix4x4 = matrix4x4 * 10;
    matrix2x4 = matrix2x4 * 10;
    matrix4x2 = matrix4x2 * 10;

    Matrix newmatrix4x4 = Matrix(4,4);
    newmatrix4x4.set(std::vector<std::vector<double>> {
      {10, 20, 30, 40},
      {50, 60, 70, 80},
      {-10, -20, -30, -40},
      {-50, -60, -70, -80},
    });

    Matrix newmatrix2x4 = Matrix(2,4);
    newmatrix2x4.set(std::vector<std::vector<double>> {
      {10, 20, 30, 40},
      {50, 60, 70, 80},
    });

    Matrix newmatrix4x2 = Matrix(4,2);
    newmatrix4x2.set(std::vector<std::vector<double>> {
      {-10, -20},
      {-30, -40},
      {-50, -60},
      {-70, -80},
    });

    EXPECT_TRUE(newmatrix4x4 == matrix4x4);
    EXPECT_TRUE(newmatrix2x4 == matrix2x4);

    EXPECT_FALSE(newmatrix4x2 == matrix4x2);
  }

  TEST_F(TestMatrix, Equation)
  {
    set4x4Matrix();

    Matrix newmatrix4x4 = Matrix(2,2);
    newmatrix4x4.set(std::vector<std::vector<double>> {
      {1, 2},
      {3, 4},
    });

    Matrix singmatrix = Matrix(2,2);
    singmatrix.set(std::vector<std::vector<double>> {
      {1, 5},
      {1, 5},
    });

    EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double> {}));
    EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double> {0,2}));
    EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double> {0,2,4}));

    EXPECT_ANY_THROW(get2x4Matrix().solveEquation(std::vector<double> {3,4,5}));
    EXPECT_ANY_THROW(get4x2Matrix().solveEquation(std::vector<double> {0,1,2}));

    EXPECT_ANY_THROW(singmatrix.solveEquation(std::vector<double> {159, 951}));

    EXPECT_TRUE(newmatrix4x4.solveEquation(std::vector<double> {1, 1}) == (std::vector<double> {-1, 1}));
  }



}
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech
//    matic.
//============================================================================//

/*** Konec souboru white_box_tests.cpp ***/
