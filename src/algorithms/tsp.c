#include "../../include/tsp.h"
#include <stdio.h>
#include <limits.h>

typedef struct {
    int (*distances)[MAX_LOCATIONS];
    int n;
    int best_distance;
    int best_route[MAX_LOCATIONS + 1];
} TSPContext;

static int calculate_distance(TSPContext *ctx, int order[]) {

    int total = 0;
    int current = 0;

    for (int i = 1; i < ctx->n; i++) {

        total += ctx->distances[current][order[i - 1]];

        current = order[i - 1];
    }

    total += ctx->distances[current][0];

    return total;
}

static void generate_routes(TSPContext *ctx, int order[],
                            int position) {

    if (position == ctx->n - 1) {

        int distance = calculate_distance(ctx, order);

        if (distance < ctx->best_distance) {

            ctx->best_distance = distance;

            ctx->best_route[0] = 0;

            for (int i = 1; i < ctx->n; i++) {
                ctx->best_route[i] = order[i - 1];
            }

            ctx->best_route[ctx->n] = 0;
        }

        return;
    }

    for (int i = position; i < ctx->n - 1; i++) {

        int temp = order[position];
        order[position] = order[i];
        order[i] = temp;

        generate_routes(ctx, order, position + 1);

        temp = order[position];
        order[position] = order[i];
        order[i] = temp;
    }
}

int solve_tsp(int distances[MAX_LOCATIONS][MAX_LOCATIONS],
              int n, int route[]) {

    if (n < 1 || n > MAX_LOCATIONS) {
        return -1;
    }

    TSPContext ctx;

    ctx.distances = distances;
    ctx.n = n;
    ctx.best_distance = INT_MAX;

    if (n == 1) {
        route[0] = 0;
        route[1] = 0;
        return 0;
    }

    int order[MAX_LOCATIONS];

    for (int i = 0; i < n - 1; i++) {
        order[i] = i + 1;
    }

    generate_routes(&ctx, order, 0);

    for (int i = 0; i <= n; i++) {
        route[i] = ctx.best_route[i];
    }

    return ctx.best_distance;
}