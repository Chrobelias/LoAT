#pragma once

#include "boolexpr.hpp"
#include "exprconversioncontext.hpp"

class ChroContext : public ExprConversionContext<ArithExprPtr, Bools::Expr, std::vector<ArithExprPtr>, std::vector<Bools::Expr>> {

public:
    ChroContext();
    ~ChroContext() override;
    ArithExprPtr getInt(const Int &val) override;
    ArithExprPtr getReal(const Int &num, const Int &denom) override;
    ArithExprPtr pow(const ArithExprPtr &base, const ArithExprPtr &exp) override;
    ArithExprPtr plus(const std::vector<ArithExprPtr> &args) override;
    ArithExprPtr times(const std::vector<ArithExprPtr> &args) override;
    ArithExprPtr mod(const ArithExprPtr &x, const ArithExprPtr &y) override;
    ArithExprPtr bwand(const ArithExprPtr &x, const ArithExprPtr &y) override;
    Bools::Expr eq(const ArithExprPtr &x, const ArithExprPtr &y) override;
    Bools::Expr lt(const ArithExprPtr &x, const ArithExprPtr &y) override;
    Bools::Expr le(const ArithExprPtr &x, const ArithExprPtr &y) override;
    Bools::Expr gt(const ArithExprPtr &x, const ArithExprPtr &y) override;
    Bools::Expr ge(const ArithExprPtr &x, const ArithExprPtr &y) override;
    Bools::Expr neq(const ArithExprPtr &x, const ArithExprPtr &y) override;
    Bools::Expr bAnd(std::vector<Bools::Expr> &args) override;
    Bools::Expr bOr(std::vector<Bools::Expr> &args) override;
    Bools::Expr bTrue() const override;
    Bools::Expr bFalse() const override;
    Bools::Expr negate(const Bools::Expr &x) override;
    std::vector<ArithExprPtr> exprVec() override;
    std::vector<Bools::Expr> formulaVec() override;

    void printStderr(const ArithExprPtr &e) const override;

private:

    ArithExprPtr buildVar(const Arith::Var &var) override;
    Bools::Expr buildVar(const Bools::Var &var) override;

};
