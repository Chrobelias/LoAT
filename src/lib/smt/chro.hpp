#pragma once

#include "smt.hpp"
#include "chrocontext.hpp"
#include "theory.hpp"

class Chro : public Smt {

public:

    void add(const Bools::Expr e) override;
    void push() override;
    void pop() override;
    SmtResult check() override;
    Model model(const std::optional<const VarSet> &vars = std::nullopt) override;
    void enableModels() override;
    void resetSolver() override;
    ~Chro() override;
    std::ostream& print(std::ostream& os) const override;
    void randomize(unsigned seed) override;
    Chro();

private:
    std::vector<std::stringstream> buffer;
    ChroContext ctx;


    int subprocess() const;
    // Rational getRealFromModel(const z3::model &model, const z3::expr &symbol);

};
