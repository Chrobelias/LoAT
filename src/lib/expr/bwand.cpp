#include "arithexpr.hpp"

ConsHash<ArithExpr, ArithBWAnd, ArithBWAnd::CacheHash, ArithBWAnd::CacheEqual, ArithExprPtr, ArithExprPtr> ArithBWAnd::cache;

ArithBWAnd::ArithBWAnd(const ArithExprPtr lhs, ArithExprPtr rhs): ArithExpr(arith::Kind::BWAnd), lhs(lhs), rhs(rhs) {}

ArithBWAnd::~ArithBWAnd() {
    cache.erase(lhs, rhs);
}

bool ArithBWAnd::CacheEqual::operator()(const std::tuple<ArithExprPtr, ArithExprPtr> &args1, const std::tuple<ArithExprPtr, ArithExprPtr> &args2) const noexcept {
    return args1 == args2;
}

size_t ArithBWAnd::CacheHash::operator()(const std::tuple<ArithExprPtr, ArithExprPtr> &args) const noexcept {
    size_t hash {23};
    const auto lhs {std::get<0>(args)};
    const auto rhs {std::get<1>(args)};
    boost::hash_combine(hash, lhs);
    boost::hash_combine(hash, rhs);
    return hash;
}

ArithExprPtr arith::mkBWAnd(ArithExprPtr lhs, ArithExprPtr rhs) {
    return ArithBWAnd::cache.from_cache(lhs, rhs);
}

const ArithExprPtr ArithBWAnd::getLhs() const {
    return lhs;
}

const ArithExprPtr ArithBWAnd::getRhs() const {
    return rhs;
}
