/*
 * NTAlgorithm.cpp
 *
 *  Created on: May 6, 2015
 *      Author: Yi-Hsiu Chen
 */

#include <iostream>
#include <cstdio>
using namespace std;

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
using namespace NTL;
#include "NTAlgorithm.h"

struct Gaussian_ZZ {
    ZZ real;
    ZZ img;
    Gaussian_ZZ(ZZ r, ZZ i) : real(r), img(i) {};
    // Operator overloading
    friend ostream &operator<<(ostream &out, Gaussian_ZZ c);
    Gaussian_ZZ operator+ (const Gaussian_ZZ& c) {
        return Gaussian_ZZ(this->real + c.real, this->img + c.img);
    }
    Gaussian_ZZ operator- (const Gaussian_ZZ& c) {
        return Gaussian_ZZ(this->real - c.real, this->img - c.img);
    }
    Gaussian_ZZ operator* (const Gaussian_ZZ& c) {
        return Gaussian_ZZ(c.real * this->real - c.img * this->img,
                           c.real * this->img + c.img * this->real);
    }
    Gaussian_ZZ operator/ (const Gaussian_ZZ& c) {
        Gaussian_ZZ numerator = (*this) * Gaussian_ZZ(c.real, -c.img);
        ZZ N = c.real * c.real + c.img * c.img;
        return Gaussian_ZZ((numerator.real + N/2) / N, (numerator.img + N/2) / N);
    }
    Gaussian_ZZ operator% (const Gaussian_ZZ& c) {
        return (*this) - ((*this)/c) * c;
    }
    Gaussian_ZZ conjugate() {
        return Gaussian_ZZ(this->real, -(this->img));
    }
    ZZ len() {
        return (this->real * this->real + this->img * this->img);
    }
    static Gaussian_ZZ GCD(Gaussian_ZZ a, Gaussian_ZZ b) {
        Gaussian_ZZ remainder = a % b;
        if (remainder.real == 0 && remainder.img == 0) {
            return b;
        } else {
            return GCD(b, remainder);
        }
    }
};
ostream &operator<<(ostream &out, Gaussian_ZZ c) {
    if (c.img >= 0)
        out << c.real << " + " << c.img << "i";
    else
        out << c.real << " - " << -c.img << "i";
    return out;
}

struct Quaternion_ZZ {
    ZZ r, i, j, k;
    Quaternion_ZZ() : r(0), i(0), j(0), k(0) {};
    Quaternion_ZZ(ZZ rr, ZZ ii, ZZ jj, ZZ kk) : r(rr), i(ii), j(jj), k(kk) {};
    // Operator overloading
    friend ostream &operator<<(ostream &out, Quaternion_ZZ c);
    Quaternion_ZZ operator+ (const Quaternion_ZZ& c) {
        return Quaternion_ZZ(this->r + c.r, this->i + c.i, this->j + c.j, this->k + c.k);
    }
    Quaternion_ZZ operator- (const Quaternion_ZZ& c) {
        return Quaternion_ZZ(this->r - c.r, this->i - c.i, this->j - c.j, this->k - c.k);
    }
    Quaternion_ZZ operator* (const Quaternion_ZZ& c) {
        return Quaternion_ZZ(
                this->r * c.r - this->i * c.i - this->j * c.j - this->k * c.k,
                this->r * c.i + this->i * c.r + this->j * c.k - this->k * c.j,
                this->r * c.j - this->i * c.k + this->j * c.r + this->k * c.i,
                this->r * c.k + this->i * c.j - this->j * c.i + this->k * c.r);
    }
    Quaternion_ZZ operator/ (const Quaternion_ZZ& c) {
        Quaternion_ZZ numerator = (*this) * Quaternion_ZZ(c.r, -c.i, -c.j, -c.k);
        ZZ N = c.r * c.r + c.i * c.i + c.j * c.j + c.k * c.k;
        return Quaternion_ZZ((numerator.r + N/2) / N, (numerator.i + N/2) / N,
                          (numerator.j + N/2) / N, (numerator.k + N/2) / N);
    }
    Quaternion_ZZ operator% (const Quaternion_ZZ& c) {
        return (*this) - (((*this)/c) * c);
    }
    Quaternion_ZZ conjugate() {
        return Quaternion_ZZ(this->r, -(this->i), -(this->j), -(this->k));
    }
    ZZ len() {
        return (this->r * this->r + this->i * this->i
              + this->j * this->j + this->k * this->k);
    }
    static Quaternion_ZZ GCD(Quaternion_ZZ a, Quaternion_ZZ b) {
        Quaternion_ZZ remainder = a % b;
        if (remainder.r == 0 && remainder.i == 0 && remainder.j == 0 && remainder.k == 0) {
            return b;
        } else {
            return GCD(b, remainder);
        }
    }
};

ostream &operator<<(ostream &out, Quaternion_ZZ c) {
    out << "(" << c.r << "  " << c.i << "i  " << c.j << "j  " << c.k << "k)";
    return out;
    return out;
}

static ZZ_pX FastPower(ZZ_pX f, ZZ exp, ZZ_pX mod) {
    if (exp == 1) {
        return f;
    }
    else {
        if (exp % 2 == 0) {
            ZZ_pX tmp = FastPower(f, exp/2, mod);
            return (tmp * tmp) % mod;
        } else {
            ZZ_pX tmp = FastPower(f, exp/2, mod);
            return (tmp * tmp * f) % mod;
        }
    }
}

static Quaternion_ZZ Q_FourSquare_odd(ZZ n) {
    //cout << "n = " << n << "\n";
    // find prime q
    ZZ k, m, q;
    while (1) {
        k = RandomBnd((n*n*n-2)/4);
        m = 4 * k + 2;
        q = m * n - 1;
        if (ProbPrime(q, 20) == 1) {
            break;
        }
    }
    ZZ u, v;
    NTAlgorithm::TwoSquare(q, u, v);
    u = u % n;
    v = v % n;
    if (u > n/2) {
        u = u - n;
    }
    if (v > n/2) {
        v = v - n;
    }
    Quaternion_ZZ g = Quaternion_ZZ::GCD(
            Quaternion_ZZ(conv<ZZ>(u), conv<ZZ>(v), conv<ZZ>(1), conv<ZZ>(0)),
            Quaternion_ZZ(conv<ZZ>(n), conv<ZZ>(0), conv<ZZ>(0), conv<ZZ>(0)));
    //cout << "g = " << g << "\n";
    return g;
}

void NTAlgorithm::TwoSquare(ZZ p, ZZ &x, ZZ &y) {
    //cout << "p = " << p << endl;
    // Define field Z_p
    ZZ_p::init(ZZ(p));
    while (1) {
        // Choose b randomly from Z_p
        ZZ_p b = random_ZZ_p();
        //cout << "b = " << b << endl;

        // Generate f_b(t)
        ZZ_pX fb;
        fb.SetLength(3);
        fb[0] = b * b + 1; fb[1] = -2 * b; fb[2] = 1;
        //cout << "fb = " << fb << endl;

        ZZ_pX g;
        g.SetLength(2);
        g[0] = 0; g[1] = 1;

        ZZ_pX h;
        h = FastPower(g, (p-1)/2, fb);
        //cout << "h = " << h << endl;

        ZZ_pX gcd;
        gcd = GCD(fb, h-1);
        ZZ_p u1;
        if (deg(gcd) >= 1 && gcd[1] == 1) {
            u1 = -gcd[0] - b;
            ZZ u = conv<ZZ>(u1);
            //cout << "u = " << u << endl;
            Gaussian_ZZ u_i = Gaussian_ZZ(u, conv<ZZ>(1));
            Gaussian_ZZ x_yi = Gaussian_ZZ::GCD(u_i, Gaussian_ZZ(p, conv<ZZ>(0)));
            x = abs(x_yi.real);
            y = abs(x_yi.img);
            if (x*x + y*y == p) {
                return;
            } else {
                continue;
            }
        } else {
            continue;
        }
    }
    return;
}

void NTAlgorithm::FourSquare(ZZ n, ZZ &x, ZZ &y, ZZ &z, ZZ &w) {
    long twos = MakeOdd(n);
    Quaternion_ZZ g;
    if (n > 1) {
        g = Q_FourSquare_odd(n);
    } else if (n == 1) {
        g = Quaternion_ZZ(conv<ZZ>(1), conv<ZZ>(0), conv<ZZ>(0), conv<ZZ>(0));
    } else {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
        return;
    }
    Quaternion_ZZ g2;
    if (twos % 2 == 0) {
        g2 = Quaternion_ZZ(conv<ZZ>(1) << (twos/2), conv<ZZ>(0), conv<ZZ>(0), conv<ZZ>(0));
    } else {
        g2 = Quaternion_ZZ(conv<ZZ>(1) << (twos/2), conv<ZZ>(1) << (twos/2), conv<ZZ>(0), conv<ZZ>(0));
    }
    g = g * g2;
    x = abs(g.r);
    y = abs(g.i);
    z = abs(g.j);
    w = abs(g.k);
    return;
}

