#include <check.h>
#include <limits.h>
#include <math.h>

#include "../viewModel/affine/affine.h"
#include "../viewModel/affine/matrix/matrix.h"
#include "../viewModel/parser.h"

#define TEST_CASES                                                  \
  analyzeFileSuite(), coolGetLineSuite(), parseVertexesSuite(),     \
      countVertexesSuite(), parseFacesSuite(), readModelSuite(),    \
      matrixTestSuite(), translatefTestSuite(), rotatefTestSuite(), \
      scaleTestSuite()

Suite *analyzeFileSuite();
Suite *coolGetLineSuite();
Suite *parseVertexesSuite();
Suite *parseFacesSuite();
Suite *countVertexesSuite();
Suite *readModelSuite();
Suite *matrixTestSuite();
Suite *translatefTestSuite();
Suite *rotatefTestSuite();
Suite *scaleTestSuite();

typedef enum {
  errorCodeNoError = 0,
  errorCodeToLargeOrInfinity = 1,
  errorCodeTooSmallOrNegativeInfinity = 2,
  errorCodeDivisionByZero = 3,
} errorCodes;

static const float epsilon = 1e-6;

#define ASSERT_MATRIX_EQ(RESULT, EXPECTED)                                    \
  for (int i = 0; i < 16; i++) {                                              \
    ck_assert_msg(fabs(RESULT[i] - (EXPECTED[i])) < epsilon, "[%d] %f != %f", \
                  i, RESULT[i], EXPECTED[i]);                                 \
  }
