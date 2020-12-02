#pragma once

#include <cmath>

namespace jw {

	template <class T>
	class Complex
	{
	protected:

		T real;
		T imaginary;

	public:

		Complex(T r, T i) : real(r), imaginary(i) {}

		T Modulus() {
			return (T)sqrt(real*real + imaginary * imaginary);
		}

		Complex<T>* Squared() {
			double nr = real * real - imaginary * imaginary;
			double ni = 2 * real*imaginary;

			this->real = nr;
			this->imaginary = ni;

			return this;
		}

		Complex<T>* Sum(const Complex<T> *c) {
			this->real += c->real;
			this->imaginary += c->imaginary;
			return this;
		}

		const T Real() {
			return real;
		}

		const T Imaginary() {
			return imaginary;
		}

	};

}