clear; clc;

t = [0, 2, 4, 6, 8, 10];
F = [0, 2.90, 14.8, 39.6, 74.3, 119];

A = [ones(size(t)) t t.^2 t.^3];
x = A \ F;

t_test = 7.5;
F_est = x(1) + x(2)*t_test + x(3)*t_test^2 + x(4)*t_test^3;

fprintf('a0 = %.4f\n', x(1));
fprintf('a1 = %.4f\n', x(2));
fprintf('a2 = %.4f\n', x(3));
fprintf('a3 = %.4f\n', x(4));
fprintf('t=7.5 时阻力 = %.4f (100 lb)\n', F_est);