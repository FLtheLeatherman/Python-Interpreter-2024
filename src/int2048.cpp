#include "int2048.h"

int2048::int2048() {
  len = 0, sgn = 1;
}
int2048::int2048(long long number) {
  len = 0, sgn = 1;
  num.clear();
  if (number < 0) {
    sgn = -1;
    number = -number;
  }
  while (number > 0) {
    num.push_back(number % base);
    number /= base;
    len++;
  }
}
int2048::int2048(const std::string &number) {
  len = 0, sgn = 1;
  num.clear();
  int start_pos = 0, end_pos = number.length();
  if (number[0] == '-') {
    sgn = -1;
    start_pos = 1;
  }
  if (end_pos == start_pos + 1 && number[start_pos] == '0') {
    sgn = 1;
    return;
  }
  int now_number;
  while (end_pos - start_pos >= 4) {
    now_number = (number[end_pos - 1] - '0')
    + (number[end_pos - 2] - '0') * 10
    + (number[end_pos - 3] - '0') * 100
    + (number[end_pos - 4] - '0') * 1000;
    num.push_back(now_number);
    len++;
    end_pos -= 4;
  }
  now_number = 0;
  for (int i = start_pos; i < end_pos; ++i) {
    now_number = now_number * 10 + (number[i] - '0');
  }
  if (now_number > 0) {
    num.push_back(now_number);
    len++;
  }
}
int2048::int2048(const int2048 &number) {
  len = number.len, sgn = number.sgn;
  num.clear();
  for (int i = 0; i < len; ++i) {
    num.push_back(number.num[i]);
  }
}
void int2048::read(const std::string &number) {
  (*this) = int2048(number);
}
void int2048::print() {
  if (sgn < 0) {
    std::cout << '-';
  }
  if (len == 0) {
    std::cout << 0;
  }
  else {
    std::cout << num[len - 1];
    for (int i = len - 2; i >= 0; --i) {
      std::cout << num[i] / 1000 << (num[i] / 100 % 10) 
      << (num[i] / 10 % 10) << num[i] % 10;
    }
  }
}
int2048 &int2048::add(const int2048 &number) {
  int2048 result(*this);
  int max_len = std::max(result.len, number.len);
  if (result.sgn == number.sgn) {
    int carry = 0;
    for (int i = 0; i < max_len; ++i) {
      if (i < result.len && i < number.len) {
        result.num[i] = result.num[i] + number.num[i] + carry;
      } else if (i < number.len) {
        result.num.push_back(number.num[i] + carry);
      } else {
        result.num[i] = result.num[i] + carry;
      }
      if (result.num[i] >= base) {
        result.num[i] -= base;
        carry = 1;
      } else {
        carry = 0;
      }
    }
    if (carry) {
      result.num.push_back(1);
      max_len++;
    }
    result.len = max_len;
  }
  else {
    for (int i = 0; i < max_len; ++i) {
      if (i < result.len && i < number.len) {
        result.num[i] = result.sgn * result.num[i] + number.sgn * number.num[i];
      } else if (i < number.len) {
        result.num.push_back(number.sgn * number.num[i]);
      } else {
        result.num[i] = result.sgn * result.num[i];
      }
    }
    while (max_len > 0 && result.num[max_len - 1] == 0) {
      result.num.pop_back();
      max_len--;
    }
    if (!max_len) {
      result.len = 0;
      result.sgn = 1;
      *this = result;
      return *this;
    }
    if (result.num[max_len - 1] < 0) {
      result.sgn = -1;
      for (int i = 0; i < max_len; ++i) {
        result.num[i] = -result.num[i];
      }
    } else {
      result.sgn = 1;
    }
    for (int i = max_len - 2; i >= 0; --i) {
      if(result.num[i] <= 0) {
        result.num[i] += base;
        result.num[i + 1]--;
      }
    }
    int carry = 0;
    for (int i = 0; i < max_len; ++i) {
      result.num[i] += carry;
      if (result.num[i] >= base) {
        result.num[i] -= base;
        carry = 1;
      } else {
        carry = 0;
      }
    }
    while (max_len > 0 && result.num[max_len - 1] <= 0) {
      result.num.pop_back();
      max_len--;
    }
    result.len = max_len;
  }
  *this = result;
  return *this;
}
int2048 add(int2048 number1, const int2048 &number2) {
  return number1.add(number2);
}
int2048 &int2048::minus(const int2048 &number) {
  int2048 result(*this);
  result.sgn = -result.sgn;
  result.add(number);
  if (result.len > 0) {
    result.sgn = -result.sgn;
  }
  *this = result;
  return *this;
}
int2048 minus(int2048 number1, const int2048 &number2) {
  return number1.minus(number2);
}
int2048 int2048::operator+()const{
  return (*this);
}
int2048 int2048::operator-()const{
  if (len == 0) {
    return (*this);
  }
  int2048 result(*this);
  result.sgn = -result.sgn;
  return result;
}
int2048 &int2048::operator=(const int2048 &number) {
  len = number.len, sgn = number.sgn;
  num.clear();
  for (int i = 0; i < len; ++i) {
    num.push_back(number.num[i]);
  }
  return (*this);
}
int2048 &int2048::operator+=(const int2048 &number) {
  (*this).add(number);
  return *this;
}
int2048 operator+(int2048 number1, const int2048 &number2) {
  int2048 result = number1.add(number2);
  return result;
}
int2048 &int2048::operator-=(const int2048 &number) {
  (*this).minus(number);
  return *this;
}
int2048 operator-(int2048 number1, const int2048 &number2) {
  int2048 result = number1.minus(number2);
  return result;
}
const double pi = acos(-1);
void Change(std::vector<std::complex<double>> &x, int len) {
  static std::vector<int> rev(1);
  rev[0] = 0;
  for (int i = 0; i < len; ++i) {
    if (i >= rev.size()) {
      rev.push_back(rev[i >> 1] >> 1);
    } else {
      rev[i] = rev[i >> 1] >> 1;
    }
    if (i & 1) {
      rev[i] |= len >> 1;
    }
    if (i < rev[i]) {
      std::swap(x[i], x[rev[i]]);
    }
  }
}
void FFT(std::vector<std::complex<double>> &x, int len, int opt) {
  Change(x, len);
  for (int h = 2; h <= len; h <<= 1) {
    std::complex<double> wn(cos(2 * pi / h), sin(2 * pi / h));
    for (int j = 0; j < len; j += h) {
      std::complex<double> w(1, 0);
      for (int k = j; k < j + h / 2; ++k) {
        std::complex<double> u = x[k], v = w * x[k + h / 2];
        x[k] = u + v, x[k + h / 2] = u - v;
        w = w * wn;
      }
    }
  }
  if (opt == -1) {
    for (int i = 1; i < len / 2; ++i) {
      std::swap(x[i], x[len - i]);
    }
    for (int i = 0; i < len; ++i) {
      x[i] = std::complex<double>(x[i].real() / len, x[i].imag() / len);
    }
  }
}
int2048 &int2048::operator*=(const int2048 &number) {
  static std::vector<std::complex<double>> vec1;
  vec1.clear();
  for (int i = 0; i < std::max(len, number.len); ++i) {
    if (i < len && i < number.len) {
      vec1.push_back({(double)(num[i] % 100), (double)(number.num[i] % 100)});
      vec1.push_back({(double)(num[i] / 100), (double)(number.num[i] / 100)});
    } else if (i < len) {
      vec1.push_back({(double)(num[i] % 100), 0.0}); 
      vec1.push_back({(double)(num[i] / 100), 0.0});
    } else {
      vec1.push_back({0.0, (double)(number.num[i] % 100)}); 
      vec1.push_back({0.0, (double)(number.num[i] / 100)});
    }
  }
  // std::cout << vec1.size() << std::endl;
  int L = 1;
  while (L < (vec1.size() + vec1.size())) {
    L <<= 1;
  }
  for (int i = vec1.size(); i < L; ++i) {
    vec1.push_back({0.0, 0.0});
  }
  // std::cout << vec1.size() << std::endl;
  FFT(vec1, L, 1); 
  for (int i = 0; i < vec1.size(); ++i) {
    vec1[i] = vec1[i] * vec1[i];
  }
  FFT(vec1, L, -1);
  sgn *= number.sgn;
  // std::cout << sgn << std::endl;
  num.clear();
  long long carry = 0;
  for (int i = 0; i < L; i += 2) {
    long long now = (long long)(vec1[i].imag() / 2.0 + 0.5) 
    + (long long)(vec1[i + 1].imag() / 2.0 + 0.5) * 100 
    + carry;
    // std::cout << now << std::endl;
    carry = now / base;
    if (now >= base) {
      now %= base;
    }
    num.push_back(now);
  }
  while (!num.empty() && num.back() == 0) {
    num.pop_back();
  }
  len = num.size();
  return *this;
}
int2048 operator*(int2048 number1, const int2048 &number2) {
  number1 *= number2;
  return number1;
}
void Shift(int2048 &number, int digit) {
  if (!number.len) {
    return;
  }
  if (digit > 0) {
    for (int i = 0; i < digit; ++i) {
      number.num.push_back(0);
    }
    number.len += digit;
    for (int i = number.len - 1; i >= digit; --i) {
      number.num[i] = number.num[i - digit];
    }
    for (int i = digit - 1; i >= 0; --i) {
      number.num[i] = 0;
    }
  } else {
    if (-digit >= number.len) {
      number.num.clear();
      number.sgn = 1;
      number.len = 0;
      return;
    }
    for (int i = -digit; i < number.len; ++i) {
      number.num[i + digit] = number.num[i];
    }
    for (int i = 0; i < -digit; ++i) number.num.pop_back();
    number.len += digit;
  }
}
void DivBruteForce(const int2048 &p, const int2048 &q, int2048 &ans) {
  ans = int2048(0);
  static std::vector<int2048> pow2_of_q, pow2;
  pow2_of_q.clear(), pow2.clear();
  pow2_of_q.push_back(q), pow2.push_back(1);
  while (pow2.back() < p.base * p.base) {
    pow2_of_q.push_back(pow2_of_q.back() + pow2_of_q.back());
    pow2.push_back(pow2.back() + pow2.back());
  }
  int2048 tmp(0);
  for (int i = p.len - 1; i >= 0; --i) {
    Shift(tmp, 1);
    Shift(ans, 1);
    tmp += p.num[i];
    if (tmp >= q) {
      for (int j = pow2.size() - 1; j >= 0; --j) {
        if (pow2_of_q[j] <= tmp) {
          ans += pow2[j];
          tmp -= pow2_of_q[j];
        }
      }
    }
  }
}
void Newton(int2048 &ans, const int2048 &b) { // ans = \lfloor \frac{10000^{2\cdot b.len}}{b} \rfloor
  if (b.len <= 50) {
    int2048 tmp(1);
    Shift(tmp, b.len * 2);
    DivBruteForce(tmp, b, ans);
    return;
  }
  int m = b.len, k = (m + 1) / 2 + 2;
  int2048 result, b_pri = b;
  int2048 sum(1);
  Shift(sum, 2 * m);
  Shift(b_pri, k - m);
  Newton(result, b_pri);
  int2048 res1, res2;
  res1 = 2 * result; Shift(res1, m - k);
  res2 = b * result * result; Shift(res2, - 2 * k);
  ans = res1 - res2;
}
int2048 &int2048::operator/=(const int2048 &number) {
  int2048 ans, tmp, a, b;
  tmp = number;
  tmp.sgn = 1;
  a = (*this);
  a.sgn = 1;
  if ((*this).len > 2 * number.len) {
    int l = (*this).len - 2 * number.len + 2;
    Shift(tmp, l);
    Shift(a, l);
  }
  b = a;
  Newton(ans, tmp);
  a = a * ans;
  Shift(a, - 2 * tmp.len);
  if (a * tmp + tmp <= b) {
    a += 1;
  } 
  if (a * tmp > b) {
    a -= 1;
  } 
  if ((*this).sgn * number.sgn < 0 && len > 0) {
    a.sgn = -1;
    if (a * number != (*this)) {
      a -= 1;
    }
  }
  (*this) = a;
  return (*this);
}
int2048 operator/(int2048 number1, const int2048 &number2) {
  number1 /= number2;
  return number1;
}
int2048 &int2048::operator%=(const int2048 &number) {
  int2048 tmp = *this;
  *this = tmp - (tmp / number) * number;
  return *this;
}
int2048 operator%(int2048 number1, const int2048 &number2) {
  number1 %= number2;
  return number1;
}
std::istream &operator>>(std::istream &in, int2048 &number) {
  static std::string str;
  in >> str;
  number = int2048(str);
  return in;
}
std::ostream &operator<<(std::ostream &out, const int2048 &number) {
  if (number.sgn < 0) {
    out << '-';
  }
  if (number.len == 0) {
    out << 0;
  }
  else {
    out << number.num[number.len - 1];
    for (int i = number.len - 2; i >= 0; --i) {
      out << number.num[i] / 1000 << (number.num[i] / 100 % 10) 
      << (number.num[i] / 10 % 10) << number.num[i] % 10;
    }
  }
  return out;
}
bool operator==(const int2048 &number1, const int2048 &number2) {
  if (number1.len != number2.len || number1.sgn != number2.sgn) {
    return false;
  }
  for (int i = 0; i < number1.len; ++i) {
    if (number1.num[i] != number2.num[i]) {
      return false;
    }
  }
  return true;
}
bool operator!=(const int2048 &number1, const int2048 &number2) {
  return !(number1 == number2);
}
bool operator<(const int2048 &number1, const int2048 &number2) {
  if (number1.sgn < number2.sgn) {
    return true;
  } else if (number1.sgn > number2.sgn) {
    return false;
  }
  if (number1.sgn < 0) {
    if (number1.len > number2.len) {
      return true;
    } else if (number1.len < number2.len) {
      return false;
    }
    for (int i = number1.len - 1; i >= 0; --i) {
      if (number1.num[i] > number2.num[i]) {
        return true;
      } else if (number1.num[i] < number2.num[i]) {
        return false;
      }
    }
    return false;
  } else {
    if (number1.len < number2.len) {
      return true;
    } else if (number1.len > number2.len) {
      return false;
    }
    for (int i = number1.len - 1; i >= 0; --i) {
      if (number1.num[i] < number2.num[i]) {
        return true;
      } else if (number1.num[i] > number2.num[i]) {
        return false;
      }
    }
    return false;
  }
}
bool operator>(const int2048 &number1, const int2048 &number2) {
  if (number1.sgn < number2.sgn) {
    return false;
  } else if (number1.sgn > number2.sgn) {
    return true;
  }
  if (number1.sgn < 0) {
    if (number1.len > number2.len) {
      return false;
    } else if (number1.len < number2.len) {
      return true;
    }
    for (int i = number1.len - 1; i >= 0; --i) {
      if (number1.num[i] > number2.num[i]) {
        return false;
      } else if (number1.num[i] < number2.num[i]) {
        return true;
      }
    }
    return false;
  } else {
    if (number1.len < number2.len) {
      return false;
    } else if (number1.len > number2.len) {
      return true;
    }
    for (int i = number1.len - 1; i >= 0; --i) {
      if (number1.num[i] < number2.num[i]) {
        return false;
      } else if (number1.num[i] > number2.num[i]) {
        return true;
      }
    }
    return false;
  }
}
bool operator<=(const int2048 &number1, const int2048 &number2) {
  return !(number1>number2);
}
bool operator>=(const int2048 &number1, const int2048 &number2) {
  return !(number1<number2);
}

bool int2048::getBoolean() {
  return len != 0;
}
std::string int2048::getString() {
  if (len == 0) {
    return "0";
  }
  std::string res = "";
  if (sgn < 0) res.append("-");
  for (int i = len - 1; i >= 0; --i) {
    res.append(std::to_string(num[i]));
  }
  return res;
}
double int2048::getDouble() {
  if (len == 0) {
    return 0.0;
  }
  double res = 0;
  for (int i = len - 1; i >= 0; --i) {
    res = res * (double)base + (double)num[i];
  }
  if (sgn < 0) res = -res;
  return res;
}