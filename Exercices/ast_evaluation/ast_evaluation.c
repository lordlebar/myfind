#include <stdio.h>
#include <stdlib.h>

#include "expression.h"

int eval_expr(struct my_expr *expr)
{
    if (expr->type == EXPR_NUMBER)
        return expr->data.value;
    else if (expr->type == EXPR_ADDITION)
    {
        int add = (eval_expr(expr->data.children.left)+ eval_expr(expr->data.children.right));
        return add;
    }
    else if (expr->type == EXPR_SUBTRACTION)
    {
        int sub = (eval_expr(expr->data.children.left) - eval_expr(expr->data.children.right));
        return sub;
    }
    else if (expr->type == EXPR_MULTIPLICATION)
    {
        int mult = (eval_expr(expr->data.children.left) * eval_expr(expr->data.children.right));
        return mult;
    }
    else if (expr->type == EXPR_DIVISION)
    {
        if (expr->data.children.right->data.value == 0)
        {
            fprintf(stderr, "Divided by 0");
            exit(1);
        }
        int div = (eval_expr(expr->data.children.left) / eval_expr(expr->data.children.right));
        return div;
    }
    else if (expr->type == EXPR_NEGATION)
    {
        int neg = -(eval_expr(expr->data.children.left));
        return neg;
    }
    return 1;
}
