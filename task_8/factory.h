#pragma once

#include <cmath>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>

class ExprFactory;

struct Expr {
    virtual double calculate(std::map<std::string, double> const& value) = 0;
    virtual std::string print(std::map<std::string, double> const* value) = 0;
};

struct Const : public Expr {
    Const(double value) : Expr(), _value(value) {}

    double calculate(std::map<std::string, double> const&) override {
      return _value;
    }

    std::string print(std::map<std::string, double> const*) override {
      return std::to_string(_value);
    }

  private:
    const double _value;
};

struct Variable : public Expr {
    Variable(std::string name) : _name(std::move(name)) {}

    double calculate(std::map<std::string, double> const& value) override {
      return value.at(_name);
    }

    std::string print(std::map<std::string, double> const* value = nullptr) override {
      if (value) {
        return std::to_string(value->at(_name));
      }
      return _name;
    }

  private:
    const std::string _name;
};

struct Operate : public Expr {
    Operate(std::shared_ptr<Expr> expr1, std::shared_ptr<Expr> expr2): _expr1(std::move(expr1)), _expr2(std::move(expr2)) {}

  protected:
    std::shared_ptr<Expr> _expr1;
    std::shared_ptr<Expr> _expr2;
};

struct Add : public Operate {
    using Operate::Operate;

    double calculate(std::map<std::string, double> const& value) override {
      return _expr1->calculate(value) + _expr2->calculate(value);
    }

    std::string print(std::map<std::string, double> const* value = nullptr) override {
      return _expr1->print(value) + " + " + _expr2->print(value);
    }
};

struct Multiply : public Operate {
    using Operate::Operate;

    double calculate(std::map<std::string, double> const& value) override {
      return _expr1->calculate(value) * _expr2->calculate(value);
    }

    std::string print(std::map<std::string, double> const* value = nullptr) override {
      return _expr1->print(value) + " * " + _expr2->print(value);
    }
};


class ExprFactory {
  public:
    ExprFactory() {
        for (int i = -5; i <= 256; ++i) {
            _consts[i] = std::make_shared<Const>(i);
        }
    }

    std::shared_ptr<Const> newConstant(double value) {
        if ((value == std::floor(value)) && (value >= -5) && (value <= 256)) {
            return _consts.at(static_cast<int>(value));
        }
        auto sp = std::make_shared<Const>(value);
        auto it = _custom_consts.find(value);
        if (it != _custom_consts.end()) {
            if (auto sp = it->second.lock()) {
                return sp;
            }
            _custom_consts.erase(it);
        }
        _custom_consts[value] = sp;
        return sp;
    }

    std::shared_ptr<Variable> newVariable(std::string name) {
      auto it = _vars.find(name);
          if (it != _vars.end()) {
              if (auto sp = it->second.lock()) {
                  return sp;
              }
            _vars.erase(it);
        }

        auto sp = std::make_shared<Variable>(name);
        _vars[name] = sp;
        return sp;
    }

    void clear_pointers() {
        auto it = _vars.begin();
        while (it != _vars.end()) {
            if (it->second.expired()) {
                it = _vars.erase(it);
            }
            ++it;
        }
        auto it2 = _custom_consts.begin();
        while (it2 != _custom_consts.end()) {
            if (it2->second.expired()) {
                it2 = _custom_consts.erase(it2);
            }
            ++it2;
        }
    }

  private:
    std::unordered_map<int, std::shared_ptr<Const>> _consts;
    std::unordered_map<double, std::weak_ptr<Const>> _custom_consts;
    std::unordered_map<std::string, std::weak_ptr<Variable>> _vars;
};