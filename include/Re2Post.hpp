#include "Visitor.hpp"
#include <string>

class   Re2Post: public Visitor {
public:
    virtual ~Re2Post() = default;

    void    run(Expr* expr);
    virtual void visitAltExpr(const Alt& expr) override;
    virtual void visitConcatExpr(const Concat& expr) override;
    virtual void visitReptExpr(const Rept& expr) override;
    virtual void visitAtomExpr(const Atom& expr) override;
    virtual void visitSymbolExpr(const Symbol& expr) override;

    std::string   result() noexcept;

private:
    std::string _result;
};
