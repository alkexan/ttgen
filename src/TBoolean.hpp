#ifndef SRC__TBOOLEAN__HPP
#define SRC__TBOOLEAN__HPP

#include <string>

/**
 * @brief Ternary logic namespace.
 */
namespace thl {
/**
 * @brief Ternary logic class.
 */
class TBoolean {
public:
  /**
   * @brief Ternary False or -1.
   */
  static const signed char FALSE = -1;

  /**
   * @brief Ternary Unknown or 0.
   */
  static const signed char UNKNOWN = 0;

  /**
   * @brief Ternary True or 1.
   */
  static const signed char TRUE = 1;

  TBoolean();

  template <typename N> TBoolean(N y) {
    if (y < 0) {
      m_value = FALSE;
    } else if (y == 0) {
      m_value = UNKNOWN;
    } else {
      m_value = TRUE;
    }
  }

  ~TBoolean();

  signed char getValue() const;

  template <typename N> TBoolean &operator=(N y) {
    if (y < 0) {
      m_value = FALSE;
    } else if (y == 0) {
      m_value = UNKNOWN;
    } else {
      m_value = TRUE;
    }
    return *this;
  }

  template <typename N> bool operator==(N n) { return m_value == n; }

  template <typename N> operator N() { return (N)(m_value); }

  operator std::string();

  TBoolean &operator=(TBoolean y);

  TBoolean operator-();

  TBoolean operator+();

  /**
   * @brief Unary function for ternary logic y = -sqrt(1 - x).
   *
   * Truth table:
   *
   * |  x  |  f  |
   * |:---:|:---:|
   * |  $  |  0  |
   * |  0  |  $  |
   * |  1  |  0  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # f - function result;
   *
   * x unary operand.
   * @return result of the operation.
   */
  TBoolean zneg();

  /**
   * @brief Unary function for ternary logic y = sqrt(1 - x).
   *
   * Truth table:
   *
   * |  x  |  f  |
   * |:---:|:---:|
   * |  $  |  0  |
   * |  0  |  1  |
   * |  1  |  0  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # f - function result;
   *
   * x unary operand.
   * @return result of the operation.
   */
  TBoolean zpos();

  /**
   * @brief The "Not" unary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  f  |
   * |:---:|:---:|
   * |  $  |  1  |
   * |  0  |  0  |
   * |  1  |  $  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # f - function result;
   *
   * @param x unary operand.
   * @return result of the operation.
   */
  TBoolean operator~();

  /**
   * @brief The "Decrement" unary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  f  |
   * |:---:|:---:|
   * |  $  |  1  |
   * |  0  |  $  |
   * |  1  |  0  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # f - function result;
   *
   * @param x unary operand.
   * @return result of the operation.
   */
  TBoolean &operator--();
  TBoolean operator--(int);

  /**
   * @brief The "Increment" unary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  f  |
   * |:---:|:---:|
   * |  $  |  0  |
   * |  0  |  1  |
   * |  1  |  $  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # f - function result;
   *
   * @param x unary operand.
   * @return result of the operation.
   */
  TBoolean &operator++();
  TBoolean operator++(int);

  /**
   * @brief The "Or" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  $  |
   * |  $  |  0  |  0  |
   * |  $  |  1  |  1  |
   * |  0  |  $  |  0  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  1  |
   * |  1  |  $  |  1  |
   * |  1  |  0  |  1  |
   * |  1  |  1  |  1  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean operator|(TBoolean y);

  /**
   * @brief The "And" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  $  |
   * |  $  |  0  |  $  |
   * |  $  |  1  |  $  |
   * |  0  |  $  |  $  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  0  |
   * |  1  |  $  |  $  |
   * |  1  |  0  |  0  |
   * |  1  |  1  |  1  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean operator&(TBoolean y);

  /**
   * @brief The "Diffirential" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  $  |
   * |  $  |  0  |  0  |
   * |  $  |  1  |  $  |
   * |  0  |  $  |  0  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  $  |
   * |  1  |  $  |  1  |
   * |  1  |  0  |  0  |
   * |  1  |  1  |  $  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean operator/(TBoolean y);

  /**
   * @brief The "Xor" (Simmetric Diffirential) binary function for ternary
   * logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  $  |
   * |  $  |  0  |  0  |
   * |  $  |  1  |  1  |
   * |  0  |  $  |  0  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  0  |
   * |  1  |  $  |  1  |
   * |  1  |  0  |  0  |
   * |  1  |  1  |  $  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean operator^(TBoolean y);

  /**
   * @brief The "Addition mod 3" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  1  |
   * |  $  |  0  |  $  |
   * |  $  |  1  |  0  |
   * |  0  |  $  |  $  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  1  |
   * |  1  |  $  |  0  |
   * |  1  |  0  |  1  |
   * |  1  |  1  |  $  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean operator%(TBoolean y);

  /**
   * @brief The "Summ" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  $  |
   * |  $  |  0  |  $  |
   * |  $  |  1  |  0  |
   * |  0  |  $  |  $  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  1  |
   * |  1  |  $  |  $  |
   * |  1  |  0  |  1  |
   * |  1  |  1  |  1  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean operator+(TBoolean y);

  /**
   * @brief The "Mul" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  1  |
   * |  $  |  0  |  0  |
   * |  $  |  1  |  $  |
   * |  0  |  $  |  0  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  0  |
   * |  1  |  $  |  $  |
   * |  1  |  0  |  0  |
   * |  1  |  1  |  1  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean operator*(TBoolean y);

  /**
   * @brief The "Substract" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  0  |
   * |  $  |  0  |  $  |
   * |  $  |  1  |  $  |
   * |  0  |  $  |  1  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  $  |
   * |  1  |  $  |  1  |
   * |  1  |  0  |  1  |
   * |  1  |  1  |  0  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean operator-(TBoolean y);

  /**
   * @brief The "Comparator" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  0  |
   * |  $  |  0  |  1  |
   * |  $  |  1  |  1  |
   * |  0  |  $  |  $  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  1  |
   * |  1  |  $  |  $  |
   * |  1  |  0  |  $  |
   * |  1  |  1  |  0  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean comp(TBoolean y);

  /**
   * @brief The "Sheffer Stroke" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  1  |
   * |  $  |  0  |  1  |
   * |  $  |  1  |  1  |
   * |  0  |  $  |  1  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  0  |
   * |  1  |  $  |  1  |
   * |  1  |  0  |  0  |
   * |  1  |  1  |  $  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean nand(TBoolean y);

  /**
   * @brief The "Peirce arrow" binary function for ternary logic.
   *
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  1  |
   * |  $  |  0  |  0  |
   * |  $  |  1  |  $  |
   * |  0  |  $  |  0  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  $  |
   * |  1  |  $  |  $  |
   * |  1  |  0  |  $  |
   * |  1  |  1  |  $  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean nor(TBoolean y);

  /**
   * @brief The Classic "Implication" binary function for ternary logic.
   *
   * This function works like an operation `not A or B`.
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  0  |
   * |  $  |  0  |  $  |
   * |  $  |  1  |  $  |
   * |  0  |  $  |  1  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  $  |
   * |  1  |  $  |  1  |
   * |  1  |  0  |  1  |
   * |  1  |  1  |  0  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean impl(TBoolean y);

  /**
   * @brief The Brusentsov "Implication" binary function for ternary logic.
   *
   * This function was taken from the site
   * Truth table:
   *
   * |  x  |  y  |  f  |
   * |:---:|:---:|:---:|
   * |  $  |  $  |  1  |
   * |  $  |  0  |  0  |
   * |  $  |  1  |  0  |
   * |  0  |  $  |  0  |
   * |  0  |  0  |  0  |
   * |  0  |  1  |  0  |
   * |  1  |  $  |  $  |
   * |  1  |  0  |  0  |
   * |  1  |  1  |  1  |
   *
   * # $ - -1 or false;
   * # x - operand;
   * # y - operand;
   * # f - function result.
   *
   * @param x first binary operand.
   * @param y second binary operand.
   * @return result of the operation.
   */
  TBoolean implb(TBoolean y);

private:
  signed char m_value;
};
} // namespace thl

#endif // SRC__TBOOLEAN__HPP
