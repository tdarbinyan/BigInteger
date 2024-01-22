### Класс BigInt

Класс `BigInt` представляет собой реализацию больших целых чисел.

### Поля

1. **digits_ : vector<int64_t>**
   - Вектор, содержащий цифры большого целого числа.

2. **is_zero_ : bool**
   - Флаг, указывающий, является ли число нулем.

3. **sign_ : char**
   - Знак числа (`'+'` - положительное, `'-'` - отрицательное).

### Конструкторы

1. **BigInt()**
   - Конструктор по умолчанию, создающий объект BigInt равный нулю.

```cpp
BigInt();
```

2. **BigInt(number)**
   - Конструктор, принимающий целое число типа `int64_t` и создающий BigInt с тем же значением.

```cpp
BigInt(int64_t number);
```

3. **BigInt(number)**
   - Конструктор, принимающий строку и создающий BigInt с соответствующим значением.

```cpp
BigInt(std::string number);
```

4. **BigInt(number)**
   - Конструктор копирования.

```cpp
BigInt(const BigInt& number);
```

### Операторы

1. **operator=()**
   - Оператор присваивания.

```cpp
BigInt& operator=(const BigInt& number);
```

2. **operator-()**
   - Унарный минус, меняющий знак числа.

```cpp
BigInt& operator-();
```

3. **operator+()**
   - Оператор сложения.

```cpp
BigInt operator+(const BigInt& number) const;
```

4. **operator+=()**
   - Оператор сложения с присваиванием.

```cpp
BigInt& operator+=(const BigInt& number);
```

5. **operator-()**
   - Оператор вычитания.

```cpp
BigInt operator-(const BigInt& number);
```

6. **operator-=()**
   - Оператор вычитания с присваиванием.

```cpp
BigInt& operator-=(const BigInt& number);
```

7. **operator*()**
   - Оператор умножения.

```cpp
BigInt operator*(const BigInt& number) const;
```

8. **operator*=()**
   - Оператор умножения с присваиванием.

```cpp
BigInt& operator*=(const BigInt& number);
```

9. **operator/()**
   - Оператор деления.

```cpp
BigInt operator/(const BigInt& number);
```

10. **operator/=()**
    - Оператор деления с присваиванием.

```cpp
BigInt& operator/=(const BigInt& number);
```

11. **operator%()**
    - Оператор взятия остатка от деления.

```cpp
BigInt operator%(const BigInt& number);
```

12. **operator%=()**
    - Оператор взятия остатка от деления с присваиванием.

```cpp
BigInt& operator%=(const BigInt& number);
```

13. **operator==()**
    - Оператор сравнения на равенство.

```cpp
bool operator==(const BigInt& number) const;
```

14. **operator!=()**
    - Оператор сравнения на неравенство.

```cpp
bool operator!=(const BigInt& number) const;
```

15. **operator>()**
    - Оператор сравнения на больше.

```cpp
bool operator>(const BigInt& number);
```

16. **operator<()**
    - Оператор сравнения на меньше.

```cpp
bool operator<(const BigInt& number);
```

17. **operator>=()**
    - Оператор сравнения на больше или равно.

```cpp
bool operator>=(const BigInt& number);
```

18. **operator<=()**
    - Оператор сравнения на меньше или равно.

```cpp
bool operator<=(const BigInt& number);
```

19. **operator++()**
    - Префиксный оператор инкремента.

```cpp
BigInt& operator++();
```

20. **operator--()**
    - Префиксный оператор декремента.

```cpp
BigInt& operator--();
```

21. **operator++(int)**
    - Постфиксный оператор инкремента.

```cpp
BigInt operator++(int);
```

22. **operator--(int)**
    - Постфиксный оператор декремента.

```cpp
BigInt operator--(int);
```

### Ввод и вывод

1. **operator>>()**
   - Оператор ввода из потока.

```cpp
friend std::istream& operator>>(std::istream& istream, BigInt& number);
```

2. **operator<<()**
   - Оператор вывода в поток.

```cpp
friend std::ostream& operator<<(std::ostream& ostream, const BigInt& number);
```

### Вспомогательные утилиты

1. **SameSignPlus()**
   - Возвращает результат сложения двух чисел с одинаковыми знаками.

```cpp
BigInt SameSignPlus(BigInt number) const;
```

2. **DiffSignPlus()**
   - Возвращает результат сложения двух чисел с разными знаками.

```cpp
BigInt DiffSignPlus(BigInt number) const;
```

3. **DeleteZeros()**
   - Удаляет ведущие нули в числе.

```cpp
BigInt& DeleteZeros();
```
