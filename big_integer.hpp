#pragma once
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <type_traits>
#include <vector>

class BigInt {
 private:
  std::vector<int64_t> digits_;
  bool is_zero_ = false;
  char sign_ = '+';

 public:
  // Constructors
  BigInt() = default;
  BigInt(int64_t number);
  BigInt(std::string number);
  BigInt(const BigInt& number) = default;  //

  // Operators
  BigInt& operator=(const BigInt& number);

  BigInt& operator-();

  BigInt operator+(const BigInt& number) const;
  BigInt& operator+=(const BigInt& number);
  BigInt operator-(const BigInt& number);
  BigInt& operator-=(const BigInt& number);
  BigInt operator*(const BigInt& number) const;
  BigInt& operator*=(const BigInt& number);
  BigInt operator/(const BigInt& number);
  BigInt& operator/=(const BigInt& number);
  BigInt operator%(const BigInt& number);
  BigInt& operator%=(const BigInt& number);

  bool operator==(const BigInt& number) const;
  bool operator!=(const BigInt& number) const;
  bool operator>(const BigInt& number);
  bool operator<(const BigInt& number);
  bool operator>=(const BigInt& number);
  bool operator<=(const BigInt& number);

  BigInt operator++(int);
  BigInt operator--(int);
  BigInt& operator++();
  BigInt& operator--();

  // istream & ostream
  friend std::istream& operator>>(std::istream& istream, BigInt& number);
  friend std::ostream& operator<<(std::ostream& ostream, const BigInt& number);

  // Methods
  BigInt SameSignPlus(BigInt number) const;
  BigInt DiffSignPlus(BigInt number) const;
  BigInt& DeleteZeros();
};
