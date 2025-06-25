#include "chro.hpp"
#include <sys/wait.h>

void Chro::add(const Bools::Expr e) {
    buffer.back() << "(assert " << e->to_smtlib().toString() << ")\n";
}

void Chro::push() {
    buffer.push_back({});
}

void Chro::pop() {
    buffer.pop_back();
}

SmtResult Chro::check() {
    buffer.push_back({});
    buffer.back() << "(check-sat)\n";
    int stdoutfd = subprocess();
    buffer.pop_back();
    constexpr auto size = 6;
    char result[size + 1] = {0};
    if (read(stdoutfd, result, size) == -1) {
        throw std::logic_error("read() failed");
    }
    close(stdoutfd);
    std::cout << result << std::endl;
    if (strcmp(result, "sat\n") == 0) {
        return SmtResult::Sat;
    } else if (strcmp(result, "unsat\n") == 0) {
        return SmtResult::Unsat;
    } else if (strcmp(result, "") == 0) {
        return SmtResult::Unknown;
    } else {
        throw std::logic_error("Unexpected return string");
    }
}

Model Chro::model(const std::optional<const VarSet> &vars) {
    buffer.push_back({});
    buffer.back() << "(get-model)\n";
    int stdoutfd = subprocess();
    buffer.pop_back();
    Arith::Model model{};
    constexpr auto size = 4096;
    char result[size + 1] = {0};
    if (read(stdoutfd, result, size) == -1) {
        throw std::logic_error("read() failed");
    }
    close(stdoutfd);
    std::string str{result};
    std::cout << result << std::endl;
    if (strcmp(result, "no model") == 0) {
        throw std::logic_error("No model");
    }
    size_t i = 0;
    while (i < size && result[i] != '\n') {
        int var;
        if (str[i+1] == 't') {
            i += 2;
            size_t j;
            var = -std::stoi(str.substr(i), &j);
            i += j;
        } else {
            i += 1;
            size_t j;
            var = std::stoi(str.substr(i), &j);
            i += j;
        }
        i += 3;
        size_t j;
        Int val = std::stoi(str.substr(i), &j);
        i += j + 2;
        model.put(theory::mkVar<theory::Type::Int, ArithExpr>(var), val);
    }
    return std::tuple{model, Bools::Model{}};

}

void Chro::enableModels() { }

void Chro::resetSolver() {
    buffer.clear();
    buffer.push_back({});
    buffer.back() << "(set-logic ALL)\n"
                  << "(assert true)\n";
}

Chro::~Chro() {}

std::ostream& Chro::print(std::ostream& os) const {
    for (const auto& buf : buffer) {
        os << buf.str();
    }
    return os;
}

void Chro::randomize(unsigned seed) { }

Chro::Chro(): buffer(), ctx() {
    resetSolver();
    // solver.set("random_seed", 42u);
    // solver.set("rlimit", 10000000u);
}

int Chro::subprocess() const {
    int inputfd[2];
    int stdoutfd[2];
    if (pipe(inputfd) != 0) {
        throw std::logic_error("pipe() failed");
    }
    if (pipe(stdoutfd) != 0) {
        close(stdoutfd[0]);
        close(stdoutfd[1]);
        throw std::logic_error("pipe() failed");
    }
    switch (fork()) {
    case -1: {
        close(inputfd[0]); 
        close(inputfd[1]);
        close(stdoutfd[0]); 
        close(stdoutfd[1]);
        throw std::logic_error("fork() failed");
    }
    case 0: {
        close(inputfd[1]);
        close(stdoutfd[0]);
        dup2(stdoutfd[1], 1);
        std::stringstream s;
        s << "/proc/self/fd/" << inputfd[0];
        auto str = s.str();
        std::string chro = "chro";
        std::array args{chro.data(), str.data(), (char*)0};
        execvp(chro.data(), args.data());
        throw std::logic_error("execvp() failed");
    }
    default: {
        close(inputfd[0]);
        close(stdoutfd[1]);
        for (const auto& buf : buffer) {
            const auto& str = buf.str();
            std::cout << str;
            if (write(inputfd[1], str.c_str(), str.size()) == -1) {
                throw std::logic_error("write() failed");
            }
        }
        std::cout << std::endl;
        close(inputfd[1]);
        wait(NULL);
        return stdoutfd[0];
    }
    }
}

// Rational Chro::getRealFromModel(const z3::model &model, const z3::expr &symbol) {
//     Rational numerator {Chro_get_numeral_string(
//         model.ctx(),
//         Chro_get_numerator(
//             model.ctx(),
//             model.eval(symbol, true)))};
//     Rational denominator {Chro_get_numeral_string(
//         model.ctx(),
//         Chro_get_denominator(
//             model.ctx(),
//             model.eval(symbol, true)))};
//     return numerator / denominator;
// }
