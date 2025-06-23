#include "chrocontext.hpp"
#include "theory.hpp"

ChroContext::ChroContext() {}

ChroContext::~ChroContext() { }

ArithExprPtr ChroContext::buildVar(const Arith::Var &var) {
    return var;
}

Bools::Expr ChroContext::buildVar(const Bools::Var &var) {
    return bools::mkAndFromLits({bools::mk(var, false)});
}

ArithExprPtr ChroContext::getInt(const Int &val) {
    return arith::mkConst(val);
}

ArithExprPtr ChroContext::getReal(const Int &num, const Int &denom) {
    return arith::mkConst(((Rational)num) / (Rational)denom);
}

ArithExprPtr ChroContext::pow(const ArithExprPtr &base, const ArithExprPtr &exp) {
    return arith::mkExp(base, exp);
}

ArithExprPtr ChroContext::plus(const std::vector<ArithExprPtr> &args) {
    return arith::mkPlus(std::vector{args});
}

ArithExprPtr ChroContext::times(const std::vector<ArithExprPtr> &args) {
    return arith::mkTimes(std::vector{args});
}

ArithExprPtr ChroContext::mod(const ArithExprPtr &x, const ArithExprPtr &y) {
    return arith::mkMod(x, y);
}

ArithExprPtr ChroContext::bwand(const ArithExprPtr &x, const ArithExprPtr &y) {
    return arith::mkBWAnd(x, y);
}

Bools::Expr ChroContext::eq(const ArithExprPtr &x, const ArithExprPtr &y) {
    return bools::mkLit(arith::mkEq(x, y));
}

Bools::Expr ChroContext::lt(const ArithExprPtr &x, const ArithExprPtr &y) {
    return bools::mkLit(arith::mkLt(x, y));
}

Bools::Expr ChroContext::le(const ArithExprPtr &x, const ArithExprPtr &y) {
    return bools::mkLit(arith::mkLeq(x, y));
}

Bools::Expr ChroContext::gt(const ArithExprPtr &x, const ArithExprPtr &y) {
    return bools::mkLit(arith::mkGt(x, y));
}

Bools::Expr ChroContext::ge(const ArithExprPtr &x, const ArithExprPtr &y) {
    return bools::mkLit(arith::mkGeq(x, y));
}

Bools::Expr ChroContext::neq(const ArithExprPtr &x, const ArithExprPtr &y) {
    return bools::mkLit(arith::mkNeq(x, y));
}

Bools::Expr ChroContext::bAnd(std::vector<Bools::Expr> &args) {
    return bools::mkAnd(args);
}

Bools::Expr ChroContext::bOr(std::vector<Bools::Expr> &args) {
    return bools::mkOr(args);
}

Bools::Expr ChroContext::bTrue() const {
    return top();
}

Bools::Expr ChroContext::bFalse() const {
    return bot();
}

Bools::Expr ChroContext::negate(const Bools::Expr &x) {
    return !x;
}

std::vector<ArithExprPtr> ChroContext::exprVec() {
    throw std::logic_error("TODO");
}

std::vector<Bools::Expr> ChroContext::formulaVec() {
    throw std::logic_error("TODO");
}

void ChroContext::printStderr(const ArithExprPtr &e) const {
    std::cerr << e << std::endl;
}
