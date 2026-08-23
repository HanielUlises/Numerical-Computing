#include "symbolic_diff.h"
#include <sstream>

namespace symbolic {

std::string Constant::to_string() const {
    std::stringstream ss;
    ss << value_;
    return ss.str();
}

std::shared_ptr<Expression> Constant::derivative(const std::string& /*var*/) const {
    return std::make_shared<Constant>(0.0); 
}

std::shared_ptr<Expression> Constant::simplify() const {
    return std::make_shared<Constant>(value_);
}

std::string Variable::to_string() const {
    return name_;
}

std::shared_ptr<Expression> Variable::derivative(const std::string& var) const {
    return std::make_shared<Constant>(name_ == var ? 1.0 : 0.0);
}

std::shared_ptr<Expression> Variable::simplify() const {
    return std::make_shared<Variable>(name_);
}

std::string Sum::to_string() const {
    return "(" + left_->to_string() + " + " + right_->to_string() + ")";
}

std::shared_ptr<Expression> Sum::derivative(const std::string& var) const {
    return std::make_shared<Sum>(left_->derivative(var), right_->derivative(var)); // (f + g)' = f' + g'
}

std::shared_ptr<Expression> Sum::simplify() const {
    auto left_simp = left_->simplify();
    auto right_simp = right_->simplify();
    if (auto left_const = std::dynamic_pointer_cast<Constant>(left_simp)) {
        if (auto right_const = std::dynamic_pointer_cast<Constant>(right_simp)) {
            return std::make_shared<Constant>(left_const->to_string() == "0" ? right_const->to_string() == "0" ? 0.0 : right_const->to_string() == "0" ? left_const->to_string() : left_const->to_string() == "0" ? right_const->to_string() : std::stod(left_const->to_string()) + std::stod(right_const->to_string()));
        }
    }
    return std::make_shared<Sum>(left_simp, right_simp);
}

std::string Product::to_string() const {
    return "(" + left_->to_string() + " * " + right_->to_string() + ")";
}

std::shared_ptr<Expression> Product::derivative(const std::string& var) const {
    // (f * g)' = f' * g + f * g'
    return std::make_shared<Sum>(
        std::make_shared<Product>(left_->derivative(var), right_),
        std::make_shared<Product>(left_, right_->derivative(var))
    );
}

std::shared_ptr<Expression> Product::simplify() const {
    auto left_simp = left_->simplify();
    auto right_simp = right_->simplify();
    if (auto left_const = std::dynamic_pointer_cast<Constant>(left_simp)) {
        if (left_const->to_string() == "0") {
            return std::make_shared<Constant>(0.0); 
        }
        if (left_const->to_string() == "1") {
            return right_simp; 
        }
    }
    if (auto right_const = std::dynamic_pointer_cast<Constant>(right_simp)) {
        if (right_const->to_string() == "0") {
            return std::make_shared<Constant>(0.0);
        }
        if (right_const->to_string() == "1") {
            return left_simp;
        }
    }
    return std::make_shared<Product>(left_simp, right_simp);
}

std::string Sine::to_string() const {
    return "sin(" + arg_->to_string() + ")";
}

std::shared_ptr<Expression> Sine::derivative(const std::string& var) const {
    // (sin(u))' = cos(u) * u'
    return std::make_shared<Product>(
        std::make_shared<Sine>(arg_),
        arg_->derivative(var)
    );
}

std::shared_ptr<Expression> Sine::simplify() const {
    return std::make_shared<Sine>(arg_->simplify());
}

// Funciones de conveniencia
std::shared_ptr<Expression> make_constant(double value) {
    return std::make_shared<Constant>(value);
}

std::shared_ptr<Expression> make_variable(const std::string& name) {
    return std::make_shared<Variable>(name);
}

std::shared_ptr<Expression> operator+(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
    return std::make_shared<Sum>(left, right);
}

std::shared_ptr<Expression> operator*(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
    return std::make_shared<Product>(left, right);
}

std::shared_ptr<Expression> sin(std::shared_ptr<Expression> arg) {
    return std::make_shared<Sine>(arg);
}

} // namespace symbolic