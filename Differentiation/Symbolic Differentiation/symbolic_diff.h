#ifndef SYMBOLIC_DIFF_H
#define SYMBOLIC_DIFF_H

#include <memory>
#include <string>
#include <cmath>

namespace symbolic {

class Expression {
public:
    virtual ~Expression() = default;
    virtual std::string to_string() const = 0;
    virtual std::shared_ptr<Expression> derivative(const std::string& var) const = 0;
    virtual std::shared_ptr<Expression> simplify() const = 0;
};

class Constant : public Expression {
    double value_;
public:
    explicit Constant(double value) : value_(value) {}
    std::string to_string() const override;
    std::shared_ptr<Expression> derivative(const std::string& var) const override;
    std::shared_ptr<Expression> simplify() const override;
};

class Variable : public Expression {
    std::string name_;
public:
    explicit Variable(const std::string& name) : name_(name) {}
    std::string to_string() const override;
    std::shared_ptr<Expression> derivative(const std::string& var) const override;
    std::shared_ptr<Expression> simplify() const override;
};

class Sum : public Expression {
    std::shared_ptr<Expression> left_, right_;
public:
    Sum(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left_(left), right_(right) {}
    std::string to_string() const override;
    std::shared_ptr<Expression> derivative(const std::string& var) const override;
    std::shared_ptr<Expression> simplify() const override;
};

class Product : public Expression {
    std::shared_ptr<Expression> left_, right_;
public:
    Product(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left_(left), right_(right) {}
    std::string to_string() const override;
    std::shared_ptr<Expression> derivative(const std::string& var) const override;
    std::shared_ptr<Expression> simplify() const override;
};

class Sine : public Expression {
    std::shared_ptr<Expression> arg_;
public:
    explicit Sine(std::shared_ptr<Expression> arg) : arg_(arg) {}
    std::string to_string() const override;
    std::shared_ptr<Expression> derivative(const std::string& var) const override;
    std::shared_ptr<Expression> simplify() const override;
};

std::shared_ptr<Expression> make_constant(double value);
std::shared_ptr<Expression> make_variable(const std::string& name);
std::shared_ptr<Expression> operator+(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
std::shared_ptr<Expression> operator*(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
std::shared_ptr<Expression> sin(std::shared_ptr<Expression> arg);

} 

#endif // SYMBOLIC_DIFF_H