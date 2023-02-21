#include "big_integer.hpp"

const int kTen = 10;

// Constructors
BigInt::BigInt(int64_t number) {
  std::string string;
  string = std::to_string(number);
  *this = BigInt(string);
}

BigInt::BigInt(std::string number) {
  if (!number.empty()) {
    if (number[0] == '-') {
      this->sign_ = '-';
      number = number.substr(1, number.size() - 1);
    }
    for (size_t i = number.size() - 1; i > 0; i--) {
      this->digits_.push_back(number[i] - '0');
    }
    this->digits_.push_back(number[0] - '0');
    if (this->digits_.size() == 1 && this->digits_[0] == 0) {  //
      this->sign_ = '+';
      this->is_zero_ = true;
    }
  }
}

// Operators

BigInt& BigInt::operator=(const BigInt& number) {
  this->sign_ = number.sign_;
  this->is_zero_ = number.is_zero_;
  this->digits_ = number.digits_;
  return *this;
}

BigInt& BigInt::operator-() {
  if (!this->is_zero_) {
    (this->sign_ == '+') ? this->sign_ = '-' : this->sign_ = '+';
  }
  return *this;
}

bool BigInt::operator==(const BigInt& number) const {
  return (this->sign_ == number.sign_ && this->digits_ == number.digits_);
}

bool BigInt::operator!=(const BigInt& number) const {
  return !(*this == number);
}

bool BigInt::operator>(const BigInt& number) {  //
  if (this->sign_ == number.sign_) {
    if (this->digits_.size() != number.digits_.size()) {
      return (this->digits_.size() > number.digits_.size() &&
              this->sign_ == '+');
    }
    for (int64_t i = this->digits_.size() - 1; i >= 0; i--) {
      if (this->digits_[i] != number.digits_[i]) {
        return this->digits_[i] > number.digits_[i];
      }
    }
    return false;
  }
  return (this->sign_ == '+');
}

bool BigInt::operator>=(const BigInt& number) {
  return (*this > number || *this == number);
}

bool BigInt::operator<(const BigInt& number) { return !(*this >= number); }

bool BigInt::operator<=(const BigInt& number) { return !(*this > number); }

BigInt& BigInt::operator++() {
  (*this == BigInt(-1)) ? * this = BigInt(0) : * this = *this + 1;
  return *this;
}

BigInt BigInt::operator++(int) {
  BigInt result = *this;
  (*this == BigInt(-1)) ? * this = BigInt(0) : * this = *this + 1;
  return result;
}

BigInt& BigInt::operator--() {
  *this = *this - 1;
  return *this;
}

BigInt BigInt::operator--(int) {
  BigInt result = *this;
  *this = *this - 1;
  return result;
}

BigInt BigInt::operator+(const BigInt& number) const {
  BigInt resulting_number;
  (this->sign_ == number.sign_) ? resulting_number = this->SameSignPlus(number)
                                : resulting_number = this->DiffSignPlus(number);
  resulting_number.DeleteZeros();
  return resulting_number;
}

BigInt& BigInt::operator+=(const BigInt& number) {
  *this = *this + number;
  return *this;
}

BigInt BigInt::operator-(const BigInt& number) {
  if (*this == number) {
    return BigInt(0);
  }
  BigInt temp = number;
  BigInt resulting_number = *this;
  (temp.sign_ == '+') ? temp.sign_ = '-' : temp.sign_ = '+';
  resulting_number = resulting_number + temp;
  return resulting_number;
}

BigInt& BigInt::operator-=(const BigInt& number) {
  *this = *this - number;
  return *this;
}
BigInt Min(BigInt first, BigInt second) {
  return (first > second) ? second : first;
}
BigInt Max(BigInt first, BigInt second) {
  return (first > second) ? first : second;
}
BigInt BigInt::operator*(const BigInt& number) const {
  if (*this == BigInt(0) || number == BigInt(0)) {
    return BigInt(0);
  }
  BigInt answer;
  char signum;
  (this->sign_ == number.sign_) ? signum = '+' : signum = '-';
  std::vector<int64_t> result(this->digits_.size() + number.digits_.size(), 0);
  for (size_t i = 0; i < this->digits_.size(); i++) {
    for (size_t j = 0; j < number.digits_.size(); j++) {
      result[i + j] += this->digits_[i] * number.digits_[j];
    }
  }
  int leftover = 0;
  for (size_t i = 0; i < result.size(); ++i) {
    result[i] += leftover;
    leftover = result[i] / kTen;
    result[i] -= leftover * kTen;
  }
  while (leftover > 0) {
    result.push_back(leftover % kTen);
    leftover /= kTen;
  }
  answer.digits_ = result;
  answer.sign_ = signum;
  answer.DeleteZeros();
  return answer;
}

BigInt& BigInt::operator*=(const BigInt& number) {
  (*this) = (*this) * number;
  return *this;
}

BigInt Absolute(BigInt number) { return (number > 0) ? number : number * -1; }

BigInt BigInt::operator/(const BigInt& number) {
  if (number.is_zero_) {
    throw("Division by 0 is prohibited");
  }
  BigInt answer = BigInt(0);
  if (Absolute(*this) < Absolute(number)) {
    return answer;
  }
  if (*this == number) {
    answer = BigInt(1);
    return answer;
  }
  BigInt div = BigInt(0);
  int64_t counter = this->digits_.size() - 1;
  while (counter >= 0) {
    div = div * kTen + BigInt(this->digits_[counter--]);
    int64_t temp = 0;
    while (div >= number * temp) {
      temp++;
    }
    temp--;
    answer = answer * kTen + temp;
    div -= (number * temp);
  }
  answer.DeleteZeros();
  (this->sign_ == number.sign_) ? answer.sign_ = '+' : answer.sign_ = '-';
  return answer;
}

BigInt& BigInt::operator/=(const BigInt& number) {
  *this = *this / number;
  return *this;
}

BigInt BigInt::operator%(const BigInt& number) {
  BigInt temp = Absolute(*this) / Absolute(number);
  temp = Absolute(*this) - Absolute(temp) * Absolute(number);
  temp.sign_ = this->sign_;
  return temp;
}

BigInt& BigInt::operator%=(const BigInt& number) {
  *this = *this % number;
  return *this;
}

// Methods

BigInt BigInt::SameSignPlus(BigInt number) const {
  if (*this == BigInt(0)) {
    return number;
  }
  if (number == BigInt(0)) {
    return *this;
  }
  BigInt result = *this;
  if (this->sign_ == number.sign_) {
    int size_diff = 0;
    while (result.digits_.size() + size_diff < number.digits_.size()) {
      result.digits_.push_back(0);
      ++size_diff;
    }
    int leftover = 0;
    for (size_t i = 0; i < result.digits_.size(); ++i) {
      (i < number.digits_.size())
          ? result.digits_[i] += number.digits_[i] + leftover
          : result.digits_[i] += leftover;
      leftover = result.digits_[i] / kTen;
      result.digits_[i] %= kTen;
    }
    if (leftover != 0) {
      result.digits_.push_back(leftover);
    }
  }
  return result;
}

BigInt BigInt::DiffSignPlus(BigInt number) const {
  if (*this == BigInt(0)) {
    return number;
  }
  if (number == BigInt(0)) {
    return *this;
  }
  BigInt result = *this;
  if (this->sign_ != number.sign_) {
    BigInt temp = number;
    result.sign_ = '+';
    temp.sign_ = '+';
    if (result < temp) {
      std::swap(result.is_zero_, temp.is_zero_);
      std::swap(result.digits_, temp.digits_);
      result.sign_ = number.sign_;
    } else {
      result.sign_ = this->sign_;
    }
    int leftover = 0;
    for (size_t i = 0; i < result.digits_.size(); ++i) {
      (i < temp.digits_.size())
          ? result.digits_[i] -= temp.digits_[i] + leftover
          : result.digits_[i] -= leftover;
      (result.digits_[i] < 0)                             ? leftover = 1,
                                result.digits_[i] += kTen : leftover = 0;
    }
  }
  return result;
}

BigInt& BigInt::DeleteZeros() {
  if (!this->digits_.empty()) {
    while (!this->digits_.empty() &&
           this->digits_[this->digits_.size() - 1] == 0) {
      this->digits_.pop_back();
      if (this->digits_.size() == 1) {
        (this->digits_[0] == 0) ? this->sign_ = '+', this->is_zero_ = true
                                : this->is_zero_ = false;
      }
    }
  }
  return *this;
}

// istream & ostream

std::istream& operator>>(std::istream& istream, BigInt& number) {
  std::string temp;
  istream >> temp;
  number = temp;
  return istream;
}

std::ostream& operator<<(std::ostream& ostream, const BigInt& number) {
  if (number.sign_ == '-') {
    ostream << number.sign_;
  }
  if (!number.digits_.empty()) {
    for (size_t i = number.digits_.size() - 1; i > 0; i--) {
      ostream << number.digits_[i];
    }
    ostream << number.digits_[0];
  }
  return ostream;
}
